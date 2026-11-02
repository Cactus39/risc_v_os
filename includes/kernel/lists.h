#ifndef LISTS_H
# define LISTS_H
typedef struct page_s page_t;
// page_t  *list_init(page_t *new);
void    list_add(page_t *head, page_t *new);
void    list_del(page_t *to_del);
int list_empty(page_t *lst);
int list_count(page_t *lst);

#endif
