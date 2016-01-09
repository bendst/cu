#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_ERR(L) if (L == \
                             NULL) {fprintf(stderr, "list not initalized"); \
                                    return; }

inline list_t *list_new() {
    return calloc(1, sizeof(list_t));
}


inline list_t *list_clone(list_t *li) {
    list_t *clone = list_new();
    LIST_FOR(i, li)
    {
        list_append(clone, i->data);
    }
    return clone;
}


inline void list_clear(list_t *li, void df(void *)) {
    LIST_INIT_ERR(li);
    LIST_FOR(i, li)
    {
        free(i->data);
    }
}


inline void list_del(list_t *li) {
    LIST_INIT_ERR(li);
    LIST_FOR(i, li)
    {
        free(i->prev);
    }
    free(li->tail);
    free(li);
}


inline void list_clear_del(list_t *li, void df(void *)) {
    list_clear(li, df);
    list_del(li);
}


inline void list_append(list_t *li, void *data) {
    LIST_INIT_ERR(li);

    struct listnode_t *tail = calloc(1, sizeof(struct listnode_t));
    tail->data = data;
    tail->prev = li->tail;
    tail->next = NULL;

    if (list_is_empty(li)) {
        li->head = tail;
        li->tail = tail;
    } else {
        li->tail->next = tail;
        li->tail = tail;
    }

    li->size = li->size + 1;
}


inline bool list_is_empty(list_t *li) {
    return list_len(li) == 0;
}


inline uint64_t list_len(list_t *li) {
    if (li == NULL) {
        fprintf(stderr, "list not initialized\n");
        return 0;
    }
    return li->size;
}


inline void list_foreach(list_t *li, void f(void *)) {
    LIST_FOR(i, li)
    {
        f(i->data);
    }
}


inline list_t *list_filter(list_t *li, void pred(void *, void *), void *arg) {
    return NULL;
}


inline void *list_find(list_t *li, void pred(void *, void *), void *arg) {
    return NULL;
}
