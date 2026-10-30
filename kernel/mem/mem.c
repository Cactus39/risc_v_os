#include <config.h>

extern int max_order;

typedef struct page_s {
    unsigned int    *page;
    int             is_free;
    struct page_s   *next;
    struct page_s   *prev;
} page_t;

void    list_add(page_t *old, page_t *new) {
    if (!old || !new)
        return ;
    while (old->next)
        old = old->next;
    old->next = new;
    new->prev = old;
    new->next = (void *)0;
}

page_t  *list_head(page_t *new) {
    if (!new)
        return ((void *)0);
    new->page = (void *)0;
    new->is_free = 1;
    new->prev = (void *)0;
    new->next = (void *)0;
    return (new);
}

void    list_del(page_t *to_del) {
    page_t *temp;

    if (!to_del)
        return ;
    temp = to_del->prev;
    temp->next = to_del->next;
    temp = to_del->next;
    temp->prev = to_del->prev;
    to_del->next = (void *)0;
    to_del->prev = (void *)0;
}
// page_t memmap[MAX_ORDER];