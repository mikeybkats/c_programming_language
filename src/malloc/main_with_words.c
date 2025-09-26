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

/* free - put block ap in free list.
- adjusts the size of the block in the header
- maintains circular relationship between base and current pointer
- loops through the free list until it finds
*/
void free(void *ap) {
  Header *block_p, *cur_p;

  block_p = (Header *)ap - 1; /* pointer to the block we want free */

  // check to see if the target block falls between the beginning and end of the
  // free list loop through the free list until
  // (block_p) is not between the cur_p and the next cur_p:
  /*
  |99    |100       |200               |300      |400       |
  |..    |          |free_p / cur_p    |block_p  |          |
  |..    |          |                  |         |          |
  |..    |next->200  |next->300          |next->400 |next->100  |

  |                                            | 0   | 1   | 2   | 3   |
  | free_p                                     | 200 | 200 | 200 | 200 |
  | cur_p                                      | 200 | 300 | 400 | 100 |
  | cur_p->s.next                               | 300 | 400 | 100 | 200 |
  | block_p                                    | 300 | 300 | 300 | 300 |
  | block_p > cur_p                            | T   | F   | F   | T   |
  | block_p < cur_p->s.next                     | F   | F   | F   | F   |
  | block_p > cur_p || block_p < cur_p->s.next  | T   | F   | F   | T   |

  |99    |100              |200        |300        |400        |
  |..    |free_p           |           |block_p    |cur_p      |
  |..    |                 |           |           |           |
  |..    |next->200         |next->300   |next->400   |next->100   |

  |99    |100              |200        |300        |400        |
  |..    |block_p          |           |freep      |           |
  |..    |                 |           |           |           |
  |..    |next->200        |next->300  |next->400  |next->100  |

  */

  // traverse the list until the current node is the last node in the lis
  // and
  for (cur_p = freep; !(block_p > cur_p && block_p < cur_p->s.next);
       cur_p = cur_p->s.next) {
    // is the next block pointing back to the start of the circlular list?
    // is block we want to free greater than the current or less than the next?
    // cur_p >= cur_p->s.next - last node in circular list
    // block_p > cur_p - to the right of the current (end of address order)
    // block_p < cur_p->s.next - to the left of the current (start of address
    // order)
    if (cur_p >= cur_p->s.next &&
        (block_p > cur_p || block_p < cur_p->s.next)) {
      break; /* reached wrap-around point in free list, insert block here */
    }
  }

  /*
  scenario 1: block being freed is between two existing blocks:
  |99    |100       |200          |300      |400       |
  |..    |free_p    |block_p      |cur_p    |          |
  |..    |          |size=100     |         |          |
  |..    |next->300  |next->400     |next->100 |next->200  |

  scenario 2: block being freed is not adjacent to any existing block:
  |99    |100       |200          |300           |400       |500      |
  |..    |          |cur_p        |block_p       |          |         |
  |..    |          |             |size (100)    |          |         |
  |..    |next->200  |next->600     |next->500      |          |next->200 |

  scenario 3: block being freed is adjacent to next block:
  |99    |100       |200          |300           |400       |500      |
  |..    |          |cur_p        |block_p       |          |         |
  |..    |          |             |size (100)    |          |         |
  |..    |next->200  |next->400     |next->500      |next->600  |next->100 |

  is the block being freed adjacent to the next block?
  */
  if (block_p + block_p->s.size == cur_p->s.next) { /* join upper nbr */
    block_p->s.size +=
        cur_p->s.next->s.size;  // increase the size of the block so that it
                                // overlaps the adjacent block
    block_p->s.next =
        cur_p->s.next->s.next;  // set the next pointer after the target block
                                // to the one after current next pointer
  } else {
    // the blocks are not adjacent
    block_p->s.next =
        cur_p->s.next;  // set the free block to the next free block
  }

  /* is the current block adjacent to the block being freed? */
  if (cur_p + cur_p->s.size == block_p) {
    cur_p->s.size += block_p->s.size;
    cur_p->s.next = block_p->s.next;
  } else {
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
    if (cur_p->s.size >= n_units) {   /* big enough */
      if (cur_p->s.size == n_units) { /* exact fit */
        prev_p->s.next = cur_p->s.next;
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
      cur_p = morecore(n_units);  // get units from OS. First pass of
                                  // i_malloc returns the list.
      if (cur_p == NULL) {
        return NULL; /* none left*/
      }
    }
  }
}