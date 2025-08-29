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

static Header  base;         /* empty list to get started */
static Header *freep = NULL; /* the start of the free list */

/* malloc: general purpose storage allocator */
void *i_malloc(unsigned nbytes) {
  return NULL;
}

#define NALLOC 1024 /* minimum #units to request */

/* morecore: ask system for more memory*/
static Header *morecore(unsigned nu) {
  return freep;
};

/* free: put block ap in free list */
void free(void *ap) {
}
