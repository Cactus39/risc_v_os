#ifndef MEM_H
# define MEM_H

typedef struct page_s {
    struct page_s   *prev;
    struct page_s   *next;
    int             index;
    uint8_t         order;
    uint8_t         is_free;
} page_t;


void    init_mem(void);
page_t  *alloc_page(uint32_t pow);
void    free_pages(page_t *page, uint32_t order);

#endif