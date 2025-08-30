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

#define NALLOC 1024 /* minimum #units to request */

/* free: put block ap in free list */
void free(void *ap) {
}

/* morecore: ask system for more memory*/
static Header *morecore(unsigned nu) {
  return freep;
};

/* malloc: general purpose storage allocator */
void *i_malloc(unsigned nbytes) {
  Header  *p, *prevp;
  Header  *morecore(unsigned);  // function prototype declaration
  unsigned nunits;

  nunits =
      (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1; /* needed units */

  prevp = freep;  // init prevp to current free pointer (NULL at first pass)
  if (prevp == NULL) { /* no free list yet */
    base.s.ptr = freep = prevp = &base;
    base.s.size                = 0;
  }

  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {   /* big enough */
      if (p->s.size == nunits) { /* exact fit */
        prevp->s.ptr = p->s.ptr;
      }
    } else {                /* allocate tail end when block is too big */
      p->s.size -= nunits;  // subtract the needed blocks from next
      p += p->s.size;  // pointer arithmetic: increment location of Header to
                       // the start of the difference of the available block and
                       // the required size
                       // |1|2|3|4|5|6|7|8|
                       // |_|_|_|_|_|_|_|_|  p->s.size // 8
                       // |x|x|              nunits // 2
                       // |_|_|_|_|_|_|      p->s.size -= nunits
                       // |_|_|_|_|_|_|x|x|  p += p->s.size
      p->s.size = nunits;  // after moving the pointer set the size of next
    }
    freep = prevp;  // set global free pointer to previous pointer
    return (void *)(p + 1);
    if (p == freep) {        /* wrapped around free list*/
      p = morecore(nunits);  // get units from OS
      if (p == NULL) {
        return NULL; /* none left*/
      }
    }
  }
}