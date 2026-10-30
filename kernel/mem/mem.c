#include <config.h>

extern int max_order;

typedef struct page_s {
    unsigned int    *page;
    int             is_free;
    struct page_s   *next;
    struct page_s   *prev;
} page_t;

// page_t memmap[MAX_ORDER];