#include <config.h>
#include <mem.h>
#include <lists.h>
#include <soc.h>

page_t      memmap[RAM_SIZE >> PAGE_SHIFT];
page_t      free_area[MAX_ORDER + 1];
uint32_t    nbr_pages;

int check_buddy(uint32_t buddy_idx, uint8_t order) {
    if (buddy_idx >= nbr_pages)
        return 0;
    if (memmap[buddy_idx].is_free == 0)
        return 0;
    if (memmap[buddy_idx].order != order)
        return 0;
    return 1;
}

void    free_pages(page_t *page, uint32_t order) {
    uint32_t        idx = page->index;
    uint32_t        buddy_idx;

    while (order < MAX_ORDER) {
        buddy_idx = idx ^ (1u << order);
        if (check_buddy(buddy_idx, order)) {
            list_del(&memmap[buddy_idx]);
            memmap[buddy_idx].is_free = 0;
            idx &= ~(1u << order);
            order++;
        }
        else
            break ;
    }
    memmap[idx].order = order;
    memmap[idx].is_free = 1;
    list_add(&free_area[order], &memmap[idx]);
}

uint32_t    divide_page(page_t *page, int pow) {

    uint32_t    idx = page->next->index;
    uint32_t    buddy_idx;
    int8_t      order = page->order;

    while (order >= 0) {
        if (order == pow) {
            list_del(&memmap[idx]);
            memmap[idx].is_free = 0;
            memmap[idx].order = order;
            return (idx);
        }
        order--;
        idx &= ~(1u << order);
        buddy_idx = idx ^ (1u << order);
        memmap[buddy_idx].is_free = 1;
        memmap[buddy_idx].order = order;
        // list_del(&memmap[buddy_idx]); // not necessary
        list_add(&free_area[order], &memmap[buddy_idx]);
    }
    return (0xffffffff);
}

page_t  *alloc_pages(uint32_t order) {
    uint32_t    res;
    uint32_t    k = order;

    while (k <= MAX_ORDER) {
        if (list_empty(&free_area[k]))
            k++;
        else {
            res = divide_page(&free_area[k], order);
            if (res != 0xffffffff)
                return (&memmap[res]);
            return (NULL);
        }
    }
    return (NULL);
}

void    init_mem(void) {
    uint32_t    heap_end;
    uint32_t    heap_start;
    page_t      *test[4];

    __asm__ __volatile__("la %0, __heap_end":"=r" (heap_end));
    __asm__ __volatile__("la %0, __heap_start":"=r" (heap_start));
    nbr_pages = (heap_end - heap_start) >> PAGE_SHIFT;
    for (uint32_t i = 0; i <= MAX_ORDER; i++) {
        free_area[i].next = &free_area[i];
        free_area[i].prev = &free_area[i];
        free_area[i].order = i;
        free_area[i].index = -1;
    }
    for (uint32_t i = 0; i < nbr_pages; i++) {
        memmap[i].is_free = 0;
        memmap[i].index = i;
        free_pages(&memmap[i], 0);
    }
    test[0] = alloc_pages(1);
    test[1] = alloc_pages(2);
    test[2] = alloc_pages(3);
    test[3] = alloc_pages(4);
    for (int i = 0; i < 4; i++) {
        free_pages(test[i], test[i]->order);
    }
    int     total = 0;
    int     local = 0;
    for (int i = 0; i <= MAX_ORDER; i++) {
        uprintf("size %d free blocks %d  mem %d\n",
            (1<<i) * 1024,
            local = list_count(&free_area[i]),
            (free_area[i].next->index));
        total += (local * (1 << i));
    }
        uprintf("pages %d\n", nbr_pages);
        uprintf("total %d\n", total);
}




















