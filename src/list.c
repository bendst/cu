#include <string.h>
#include <stdio.h>
#include "list.h"
#include "util.h"

#define LIST_INIT_ERR(L) if (L == NULL) { \
        fprintf(stderr, "list not initalized"); \
        abort(); }

inline list_t *list_new() {
    return calloc(1, sizeof(list_t));
}


inline void *list_clone(const list_t *li, void *(*clonef)(void *)) {
    list_t *clone = list_new();
    if (clonef == NULL) {
        LIST_FOR(i, li)
        {
            list_push_back(clone, i->data);
        }
    } else {
        LIST_FOR(i, li)
        {
            list_push_back(clone, clonef(i->data));
        }
    }

    return clone;
}


inline void list_clear(const list_t *li, void (*df)(void *)) {
    LIST_INIT_ERR(li);

    if (df == NULL) {
        LIST_FOR(i, li)
        {
            memset(i->data, 0, sizeof(void *));
        }
    } else {
        LIST_FOR(i, li)
        {
            df(i->data);
        }
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


inline void list_push_back(list_t *li, void *data) {
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


inline void list_push_front(list_t *li, void *data) {
    LIST_INIT_ERR(li);

    struct listnode_t *head = calloc(1, sizeof(struct listnode_t));
    head->data = data;
    head->next = li->head;
    head->prev = NULL;

    if (list_is_empty(li)) {
        li->head = head;
        li->tail = head;
    } else {
        li->head->prev = head;
        li->head = head;
    }
    li->size = li->size + 1;
}


inline void list_append(list_t *li, list_t *other) {
    LIST_INIT_ERR(li);
    LIST_INIT_ERR(other);

    li->tail->next = other->head;
    other->head->prev = li->tail;
    li->tail = other->head;
    li->size = li->size + other->size;
}


inline bool list_is_empty(const list_t *li) {
    return list_len(li) == 0;
}


inline size_t list_len(const list_t *li) {
    if (li == NULL) {
        fprintf(stderr, "list not initialized\n");
        return 0;
    }
    return li->size;
}


inline void list_foreach(const list_t *li, void f(void *)) {
    LIST_INIT_ERR(li);
    LIST_FOR(i, li)
    {
        f(i->data);
    }
}


inline void *list_filter(const list_t *li,
                         const void *key,
                         bool (*pred)(const void *, const void *)) {
    LIST_INIT_ERR(li);
    list_t *filter_copy = list_new();
    LIST_FOR(i, li)
    {
        if (pred(key, i->data)) {
            list_push_back(filter_copy, i->data);
        }
    }
    return filter_copy;

}


inline void *list_find(const list_t *li,
                       const void *key,
                       bool pred(const void *, const void *)) {
    LIST_INIT_ERR(li);
    LIST_FOR(i, li)
    {
        if (pred(key, i->data)) {
            return i->data;
        }
    }
    return NULL;
}
