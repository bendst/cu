#include "cu.h"
#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_ERR(L) if (L == \
                             NULL) {fprintf(stderr, "list not initalized"); \
                                    return; }

inline list_t *list_new() {
    return calloc(1, sizeof(list_t));
}


inline list_t *list_clone(list_t *li) {
    return NULL;
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
        void *current = i;
        i = i->next;
        free(current);
    }
}


inline void list_clear_del(list_t *li, void df(void *)) {
}


inline void list_append(list_t *li, void *data) {
}


inline bool list_is_empty(list_t *li) {
    return false;
}


inline uint64_t list_len(list_t *li) {
    return 0;
}


inline void list_foreach(list_t *li, void f(void *)) {
}


inline list_t *list_filter(list_t *li, void pred(void *, void *), void *arg) {
    return NULL;
}


inline void *list_find(list_t *li, void pred(void *, void *), void *arg) {
    return NULL;
}
