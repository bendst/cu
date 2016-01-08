#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct listnode_t {
    void *data;
    struct listnode_t *next;
} listnode_t;

typedef struct {
    listnode_t *head;
    listnode_t *tail;
    uint64_t size;
} list_t;

extern list_t *list_new();

extern list_t *list_clone(list_t *li);
extern void list_clear(list_t *li, void df(void *));
extern void list_del(list_t *li);
extern void list_clear_del(list_t *li, void df(void *));
extern void list_append(list_t *li, void *data);
extern bool list_is_empty(list_t *li);
extern uint64_t list_len(list_t *li);
extern void list_foreach(list_t *li, void f(void *));
extern list_t *list_filter(list_t *li, void pred(void *, void *), void *arg);
extern void *list_find(list_t *li, void pred(void *, void *), void *arg);


/*
 *---------------------------------------------------------------------------
 * Helper macros
 *---------------------------------------------------------------------------
 */

 #define LIST_FOR(IT, L) listnode_t * IT = NULL; for (IT = L->head; IT != NULL; \
                                                      IT = IT->next)
