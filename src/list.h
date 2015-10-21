#ifndef CULIST_H_
#define CULIST_H_

#include <stdbool.h>

typedef struct listnode_t {
    void *data;
    struct listnode_t *prev;
    struct listnode_t *next;
} listnode_t;

typedef struct {
    listnode_t *head;
    listnode_t *tail;
    unsigned long size;
} culist_t;

extern culist_t culist_new();
extern culist_t culist_clone(culist_t *li, );
extern void culist_clear(culist_t *li, void df(void *));
extern void culist_del(culist_t *li);
extern void culist_clear_del(culist_t *li, void df(void *));
extern void culist_append(culist_t *li, void *data);
extern bool culist_is_empty(culist_t *li);
extern unsigned long culist_len(culist_t *li);
extern void culist_foreach(culist_t *li, void f(void *));
extern culist_t culist_filter(culist_t *li, void pred(void *, void *), void *arg);
extern void *culist_find(culist_t *li, void pred(void *, void *), void *arg);


/*
 *---------------------------------------------------------------------------
 * Helper macros
 *---------------------------------------------------------------------------
 */

 #define cu_list_for(IT, L) listnode_t *IT = NULL; for(IT = L->head; IT != NULL; IT=IT->next)

#endif /* CULIST_H_ */
