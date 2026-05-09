#include <stddef.h>

typedef long Align; /* for aligning the headers to size long*/

union header { /* the memory block */
  struct
  {
    union header *next; /* the next block of memory */
    unsigned      size; /* size of this block */
  } s;
  Align x; /* tells c compiler to force the size of the header to long */
};

typedef union header Header;

static Header base; /* empty list to get started. OS allocates memory at a fixed
                       memory address with the program's data segment */
static Header *freep = NULL; /* the start of the free list */

/* free - put block ap in free list.  */
void free(void *ap) {
  Header *block_p, *cur_p;

  block_p = (Header *)ap - 1; /* pointer to the block we want free */

  // traverse the list until the current node is the circular node in the list
  for (cur_p = freep; !(block_p > cur_p && block_p < cur_p->s.next);
       cur_p = cur_p->s.next) {
    // is block we want to free outside of the bounds of the list?
    if (cur_p >= cur_p->s.next &&
        (block_p > cur_p || block_p < cur_p->s.next)) {
      break;
    }
  }

  /*
  coalescing free blocks - merge adjacent free blocks into those being freed
  is the block being freed adjacent to the next block?
  is the block being freed adjacent to the start of the list */
  if (block_p + block_p->s.size == cur_p->s.next) {
    // merge the starting node and block to free
    block_p->s.size +=
        cur_p->s.next->s.size;  // increase the size of the block so that it
                                // overlaps/merges the adjacent block
    block_p->s.next =
        cur_p->s.next->s.next;  // set the next pointer after the target block
                                // to the one after current next pointer to
                                // complete the merge
  } else {
    // the blocks are not adjacent
    // assign the node that the freed node points to next
    block_p->s.next =
        cur_p->s.next;  // set the free block to the next free block
  }

  /* is the current block adjacent to the block being freed? */
  /* is the block being freed adjacent to the end of the list?  */
  if (cur_p + cur_p->s.size == block_p) {
    cur_p->s.size += block_p->s.size;
    cur_p->s.next = block_p->s.next;
  } else {
    // assign the pointer to the next node
    cur_p->s.next = block_p;
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
  core_p = sbrk(
      (int)(n_units * sizeof(Header)));  // sbrk returns a chunk of memory that
                                         // is guarenteed to be sequential

  /* if no space at all*/
  if (core_p == (char *)-1) {
    /* sbrk returns (void*)-1 on failure */
    return NULL;
  }
  unit_p =
      (Header *)core_p;  // at this point all Headers are identical in the list
  unit_p->s.size = n_units;
  free((void *)unit_p + 1);  // free the pointer to core_p

  return freep;
};

/* malloc: general purpose storage allocator */
void *i_malloc(unsigned n_bytes) {
  Header  *cur_p, *prev_p;
  unsigned n_units;

  n_units =
      (n_bytes + sizeof(Header) - 1) / sizeof(Header) + 1; /* needed units */

  prev_p = freep;  // init prev_p to current free pointer (NULL at first pass)
  if (prev_p == NULL) {                    /* no free list yet */
    base.s.next = freep = prev_p = &base;  // base points to itself
    base.s.size                  = 0;
  }

  // prev_p starts freep which points to &base initially
  // cur_p is initialized as &base
  for (cur_p = prev_p->s.next;; prev_p = cur_p, cur_p = cur_p->s.next) {
    if (cur_p->s.size >= n_units) {      // big enough
      if (cur_p->s.size == n_units) {    // exact fit
        prev_p->s.next = cur_p->s.next;  // setting the prev next to the current
                                         // next removes the node from the list
      } else {                           // block is too big
        // allocate tail end of block
        cur_p->s.size -= n_units;  // reduce the block size
        cur_p += cur_p->s.size;    // move the pointer to the end of the block
        cur_p->s.size = n_units;   // set the size of the allocated portion

        // pointer arithmetic: increment location of
        // Header to the start of the difference of the
        // available block and the required size
      }
      freep = prev_p;  // set global free pointer to previous pointer
      return (void *)(cur_p + 1);
    }

    // freep has not been redefined (wrapped around free list)
    if (cur_p == freep) {
      // get units from OS. First pass of i_malloc returns the list.
      cur_p = morecore(n_units);
      if (cur_p == NULL) {
        return NULL; /* none left*/
      }
    }
  }
}