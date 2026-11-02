#include <mem.h>

void    list_add(page_t *head, page_t *new) {
    if (!new || !head)
        return ;
    new->next = head->next;
    new->prev = head;
    head->next->prev = new;
    head->next = new;
}

void    list_del(page_t *to_del) {
    if (!to_del)
        return ;
    if (to_del->next == to_del)
        return ;
    to_del->prev->next = to_del->next;
    to_del->next->prev = to_del->prev;
    to_del->next = (NULL);
    to_del->prev = (NULL);
}

int list_empty(page_t *lst) {
    if (!lst)
        return (-1);
    if (lst->next == lst)
        return (1);
    return (0);
}

int list_count(page_t *lst) {
    page_t      *start;
    int         c = 0;

    start = lst;
    if (lst->next == lst)
        return (0);
    lst = lst->next;
    while (lst != start) {
        lst = lst->next;
        c++;
    }
    return (c);
}
