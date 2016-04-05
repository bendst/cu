#ifndef CU_LIST_H_
#define  CU_LIST_H_
#include <stdbool.h>
#include <stdlib.h>

/**
 * @file list.h
 * Interface of a dopply linked list
 */

/**
 * node of the dopply linked list
 */
typedef struct listnode_t {
    /** data a node**/
    void *data;
    /** reference to the next node **/
    struct listnode_t *next;
    /** reference to the previous node **/
    struct listnode_t *prev;
} listnode_t;

/**
 * @brief Holds the reference to the head and tail of the list
 */
typedef struct {
    /** head of the list_t **/
    listnode_t *head;
    /** tail of the list_t**/
    listnode_t *tail;
    /** counts the node within the list_t **/
    size_t size;
} list_t;

/**
 * @brief Iterate over the content of the list_t
 * @param  IT name of the temporary variable
 * @param  L  list_t to iterate over
 * @return    yields a element of the list_t, will be accesable through IT->data
 */
#define LIST_FOR(IT, L) struct listnode_t *IT = NULL; for (IT = L->head; \
                                                           IT != NULL; \
                                                           IT = IT->next)

/**
 * create a list_t on the stack
 */
#define LIST_INIT {.head = NULL, \
                   .tail = NULL, \
                   .size = 0}

/**
 * @brief Clear and delete a list_t,
 * which was created on the stack
 * @param  L  list_t to delete
 * @param  FN function with which the content of the list can be deleted
 */
#define LIST_DEL(L, FN) list_clear(&L, FN); struct listnode_t *IT = NULL; \
    for (IT = L.head; IT != NULL; IT = IT->next) { \
        free(IT->prev); \
    } \
    free(L.tail);


/**
 * @brief Create a new list
 * @return a new list_t
 */
extern list_t *list_new();


/**
 * @brief Clone given list
 * @param  li list to clone
 * @param clone function for given element. In case of NULL it is ignored
 * @return    a new list_t
 */
extern void *list_clone(const list_t *li, void *(*clone)(void *));


/**
 * @brief Remove all elements from the list.
 * @param li list to clear
 * @param df deleting function, in case of NULL the argument is ignored
 */
extern void list_clear(const list_t *li, void (*df)(void *));


/**
 * @brief Free the memory allocated
 * @param li list to delete
 */
extern void list_del(list_t *li);


/**
 * @brief Remove all elements from the list and free it.
 * @param li List to clear and delete
 * @param df Deleting function, in case of NULL the argument is ignored
 */
extern void list_clear_del(list_t *li, void (*df)(void *));


/**
 * @brief Append an element to the list
 * @param li   list to append to
 * @param data data to append
 */
extern void list_push_back(list_t *li, void *data);

/**
 * @brief Prepend an element to the list
 * @param li   list to prepend to
 * @param data data to prepend
 */
extern void list_push_front(list_t *li, void *data);

/**
 * Insert data into the list at given position
 * @param li    list to insert data to
 * @param index target index
 * @param data  data to insert
 */
extern void list_insert(list_t *li, const size_t index, void *data);

/**
 * @brief Append another list_t to the current one.
 * @param li    list to append to
 * @param other other list
 */
extern void list_append(list_t *li, list_t *other);

/**
 * @brief Check whether the list is empty
 * @param  li list to check
 * @return    returns true on success and false on failure
 */
extern bool list_is_empty(const list_t *li);


/**
 * @brief Retrieve the length of a list
 * @param  li list to check
 * @return    returns the list length
 */
extern size_t list_len(const list_t *li);


/**
 * @brief Apply a function to every element of the list
 * @param li list
 * @param f  function to apply
 */
extern void list_foreach(const list_t *li, void (*f)(void *));


/**
 * @brief Filter elements by given predicate
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
 * @brief Find a element in the list
 * @param  li   list to search
 * @param key key to find
 * @param  pred predicate function
 * @return      returns a pointer to the element
 */
extern void *list_find(const list_t *li,
                       const void *key,
                       bool (*pred)(const void *,
                                    const void *));
/**
 * Check whether the list contains given key
 * @param  li   list to search
 * @param  key  key to check
 * @param  pred predicate function
 * @return      returns true if the value is in the list, false otherwise
 */
extern bool list_contains(list_t *li,
                          const void *key,
                          bool (*pred)(const void *, const void *));

#endif /* CU_LIST_H_ */
