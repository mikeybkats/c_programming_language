#include <stddef.h>

typedef long Align; /* for aligning the headers to size long*/

union header { /* the memory block */
  struct
  {
    union header *ptr;  /* the next block of memory */
    unsigned      size; /* size of this block */
  } s;
  Align x; /* tells c compiler to force the size of the header to long */
};

typedef union header Header;

static Header base; /* empty list to get started. OS allocates memory at a fixed
                       memory address with the program's data segment */
static Header *freep = NULL; /* the start of the free list */

/* free - put block ap in free list.

- maintains circular relationship between base and current pointer
*/
void free(void *ap) {
  Header *block_p, *cur_p;

  block_p = (Header *)ap - 1; /* point to block header */

  // check to see if the target block falls between the beginning and end of the
  // free list loop through the free list until the break pointer header
  // (block_p) is not:
  // 1. greater than the freep
  // 2. less than the next Header pointer
  for (cur_p = freep; !(block_p > cur_p && block_p < cur_p->s.ptr);
       cur_p = cur_p->s.ptr) {
    if (cur_p >= cur_p->s.ptr && (block_p > cur_p || block_p < cur_p->s.ptr)) {
      break; /* freed block at start or end of arena*/
    }
  }

  if (block_p + block_p->s.size == cur_p->s.ptr) { /* join upper nbr */
    block_p->s.size += cur_p->s.ptr->s.size;
    block_p->s.ptr = cur_p->s.ptr->s.ptr;
  } else {
    block_p->s.ptr = cur_p->s.ptr;
  }

  if (cur_p + cur_p->s.size == block_p) {
    cur_p->s.size += block_p->s.size;
    cur_p->s.ptr = block_p->s.ptr;
  } else {
    cur_p->s.ptr = block_p;
  }
  freep = cur_p;
}

#define NALLOC 1024 /* minimum #units to request */

/* morecore: ask system for more memory*/
static Header *morecore(unsigned n_units) {
  char   *core_p, *sbrk(int);  // core_p - core memory
  Header *unit_p;

  if (n_units < NALLOC) {
    n_units = NALLOC;
  }
  core_p = sbrk((int)(n_units * sizeof(Header)));
  if (core_p == (char *)-1) { /* no space at all*/
    /* sbrk returns (void*)-1 on failure */
    return NULL;
  }
  unit_p         = (Header *)core_p;
  unit_p->s.size = n_units;
  free((void *)unit_p + 1);

  return freep;
};

/* malloc: general purpose storage allocator */
void *i_malloc(unsigned n_bytes) {
  Header  *cur_p, *prev_p;
  Header  *morecore(unsigned);  // function prototype declaration
  unsigned n_units;

  n_units =
      (n_bytes + sizeof(Header) - 1) / sizeof(Header) + 1; /* needed units */

  prev_p = freep;  // init prev_p to current free pointer (NULL at first pass)
  if (prev_p == NULL) {                   /* no free list yet */
    base.s.ptr = freep = prev_p = &base;  // base points to itself
    base.s.size                 = 0;
  }

  // prev_p starts freep which points to &base initially
  // cur_p is initialized as &base
  for (cur_p = prev_p->s.ptr;; prev_p = cur_p, cur_p = cur_p->s.ptr) {
    if (cur_p->s.size >= n_units) {   /* big enough */
      if (cur_p->s.size == n_units) { /* exact fit */
        prev_p->s.ptr = cur_p->s.ptr;
      } else {                     /* allocate tail end when block is too big */
        cur_p->s.size -= n_units;  // subtract the needed blocks from next
        cur_p +=
            cur_p->s.size;  // pointer arithmetic: increment location of Header
                            // to the start of the difference of the available
                            // block and the required size |1|2|3|4|5|6|7|8|
                            // |_|_|_|_|_|_|_|_|  cur_p->s.size // 8
                            // |x|x|              n_units // 2
                            // |_|_|_|_|_|_|      cur_p->s.size -= n_units
                            // |_|_|_|_|_|_|x|x|  cur_p += cur_p->s.size
        cur_p->s.size =
            n_units;  // after moving the pointer set the size of next
      }
      freep = prev_p;  // set global free pointer to previous pointer
      return (void *)(cur_p + 1);
    }
    if (cur_p == freep) {         /* wrapped around free list*/
      cur_p = morecore(n_units);  // get units from OS. First pass of i_malloc
      if (cur_p == NULL) {
        return NULL; /* none left*/
      }
    }
  }
}