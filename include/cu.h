#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define UNIMPLEMENTED fprintf(stderr, "%s not implemented %s@%d\n", __func__, __FILE__, \
                               __LINE__); abort();

//#include "vector.h"

/** @brief vector
 *
 */
typedef struct  {
    /** data **/
    void **data;
    /** allocated memory **/
    uint32_t memsize;
    /** member counter **/
    uint32_t count;
} vector_t;

/** creates a new empty vector of the size 10
 *  @result a new vector
 **/
extern vector_t *vector_new();


/** creates a empty vector of the size n
 *  @param n size of the empty array
 *  @param returns a new vector
 *  @result a new vector
 **/
extern vector_t *vector_with_cap(uint32_t n);


/** appends a element to the vector
 *  @param list arrayList to which the data should be added
 *  @param data pointer to add
 **/
extern void vector_append(vector_t *v, void *data);


/**
 * delete a element from the vector
 * @param v     vector
 * @param index of the element to remove
 * @param df    deleting function for the given element. df is ignored if NULL
 */
extern void vector_del_at(vector_t *v, uint32_t index, void (*df)(void *));


/** returns the data of the index
 *  @param list fetch the data of this arrayList
 *  @param i index to fetch
 *  @result returns the pointer to the data
 **/
extern void *vector_get(const vector_t *v, uint32_t index);


/** apply the funtion f to every element in the vector
 *  @param list vector to operate on
 *  @param f function to apply
 **/
extern void vector_foreach(const vector_t *v, void (*f)(void *));


/** delete the  vector no element in the structure is deleted
 *  @param list to delete
 **/
extern void vector_del(vector_t *v);


extern void vector_clear(vector_t *v, void (*df)(void *));


/** delete the vector and its content
 *
 *  @param list to delete
 *  @param df function with which the data should be deleted
 **/
extern void vector_clear_del(vector_t *v, void (*df)(void *));


/**
 * Check whether a element is in the vector.
 * Example for predicate functions:
 *      for Integer on stack:
 *          return memcmp(a, *(void **)b, sizeof(int32_t))
 *
 * @param  v    vector to search
 * @param  key  item to find
 * @param  pred predicate function
 * @return      returns true on succuss and false on failure
 */
extern bool vector_contains(const vector_t *v, const void *key, int (*pred)(
                                const void *,
                                const void *));


/**
 * Sort the vector with quicksort
 * @param v    vector to sort
 * @param pred predicate function
 */
extern void vector_sort(vector_t *v, int (*pred)(const void *, const void *));

//#include "list.h"

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
 * @param  pred predicate function
 * @return      returns a new list_t which contains all elements that returned true
 */
extern void *list_filter(const list_t *li,
                         void (*pred)(const void *,
                                      const void *),
                         void *arg);


/**
 * find a element in the list
 * @param  li   list to search
 * @param  pred predicate function
 * @return      returns a pointer to the element
 */
extern void *list_find(const list_t *li,
                       const void *key,
                       void (*pred)(const void *,
                                    const void *),
                       void *arg);


/*
 *---------------------------------------------------------------------------
 * Helper macros
 *---------------------------------------------------------------------------
 */

 #define LIST_FOR(IT, L) struct listnode_t *IT = NULL; for (IT = L->head; \
                                                            IT != NULL; \
                                                            IT = IT->next)
