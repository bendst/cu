#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct listnode_t {
    void *data;
    struct listnode_t *next;
    struct listnode_t *prev;
} listnode_t;

typedef struct {
    listnode_t *head;
    listnode_t *tail;
    uint64_t size;
} list_t;

/**
 * create a new list
 * @return a new list_t
 */
extern void *list_new();


/**
 * clone given list
 * @param  li list to clone
 * @param clone function for given element. In case of NULL it is ignored
 * @return    a new list_t
 */
extern void *list_clone(const list_t *li, void *(*clone)(void *));


/**
 * clear a list of every entry
 * @param li list to clear
 * @param df deleting function, in case of NULL the argument is ignored
 */
extern void list_clear(const list_t *li, void (*df)(void *));


/**
 * delete a list
 * @param li list to delete
 */
extern void list_del(list_t *li);


/**
 * clear and delete a list
 * @param li list to clear and delete
 * @param df deleting function, in case of NULL the argument is ignored
 */
extern void list_clear_del(list_t *li, void (*df)(void *));


/**
 * append an element to the list
 * @param li   list to append to
 * @param data data to append
 */
extern void list_append(list_t *li, void *data);


/**
 * check whether the list is empty
 * @param  li list to check
 * @return    returns true on success and false on failure
 */
extern bool list_is_empty(const list_t *li);


/**
 * retrieve the length of a list
 * @param  li list to check
 * @return    returns the list length
 */
extern uint64_t list_len(const list_t *li);


/**
 * apply a function to every element of the list
 * @param li list
 * @param f  function to apply
 */
extern void list_foreach(const list_t *li, void (*f)(void *));


/**
 * filter elements by given predicate
 * @param  li   list to filter
 * @param key key to find
 * @param  pred predicate function
 * @return      returns a new list_t which contains all elements that returned true
 */
extern void *list_filter(const list_t *li,
                         const void *key,
                         bool (*pred)(const void *,
                                      const void *));


/**
 * find a element in the list
 * @param  li   list to search
 * @param key key to find
 * @param  pred predicate function
 * @return      returns a pointer to the element
 */
extern void *list_find(const list_t *li,
                       const void *key,
                       bool (*pred)(const void *,
                                    const void *));


/*
 *---------------------------------------------------------------------------
 * Helper macros
 *---------------------------------------------------------------------------
 */

 #define LIST_FOR(IT, L) struct listnode_t *IT = NULL; for (IT = L->head; \
                                                            IT != NULL; \
                                                            IT = IT->next)
