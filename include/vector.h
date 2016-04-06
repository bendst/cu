#ifndef CU_VECTOR_H_
#define CU_VECTOR_H_

#include <stdlib.h>
#include <stdbool.h>

/**
 * @file vector.h
 */

/** @brief vector
 * dynamically growing array
 */
typedef struct  {
    /** data **/
    void **data;
    /** allocated memory **/
    size_t memsize;
    /** element counter **/
    size_t count;
} vector_t;


/**
 * @brief Initialize a vector_t on the stack
 *
 * ~~~{.c}
 * vector_t v = VECTOR_INIT(8);
 * ~~~
 *
 * @param  N size of the vector
 * @internal
 */
#define VECTOR_INIT(N) {.data = calloc(N, sizeof(void *)), .memsize = N, \
                        .count = 0 }

/**
 * @brief Delete a on stack allocated vector_t
 *
 * ~~~{.c}
 * vector_t v = VECTOR_INIT(8);
 * VECTOR_DEL(v, NULL);
 * ~~~
 *
 * @param  V  vector_t to delete
 * @param  FN function to delete the content of the vector_t
 */
#define VECTOR_DEL(V, FN) vector_clear(&V, FN); free(V.data);

/** @brief Creates a new empty vector of the size 8
 *
 * ~~~{.c}
 * vector_t *v = vector_new();
 * ~~~
 *
 *  @return a new vector
 **/
extern vector_t *vector_new();


/** @brief Creates a empty vector of the size n
 *
 * ~~~{.c}
 * vector_t *v = vector_with_cap(8);
 * ~~~
 *
 *  @param n size of the empty array
 *  @param returns a new vector
 *  @return a new vector
 **/
extern vector_t *vector_with_cap(size_t n);


/**
 * @brief Insert an element at given position,
 * should the index be greater than the current vector size then
 * the data is pushed to the end.
 * The vector avoids any fragmentation
 *
 * ~~~{.c}
 * vector_t *v = vector_new();
 * for(size_t i=0; i<10, i++){
 *     vector_insert(v, 0, &i);
 * }
 * ~~~
 *
 * @param v     vector
 * @param index position to insert
 * @param data  data to insert
 */
extern void vector_insert(vector_t *v, size_t index, void *data);


/** @brief Appends a element to the vector
 *
 * ~~~{.c}
 * vector_t v = VECTOR_INIT(8);
 * int a = 42;
 * int b = 24;
 * vector_push(&v, &a);
 * vector_push(&v, &b);
 * // v = [42, 24]
 * ~~~
 *
 *  @param v arrayList to which the data should be appended
 *  @param Data to add
 **/
extern void vector_push(vector_t *v, void *data);

/**
 * Get the size of the vector_t
 * @param  v vector
 * @return Current size of the vector
 */
extern size_t vector_len(const vector_t *v);

/**
 * Check whether the vector is empty
 * @param  v vector
 * @return  Returns true if the vector is not empty, false otherwise
 */
extern bool vector_is_empty(const vector_t *v);

/**
 * @brief Remove the last element from the vector
 *
 * ~~~{.c}
 * vector_t v = VECTOR_INIT(8);
 * int a = 42;
 * int b = 24;
 * vector_push(&v, &a);
 * vector_push(&v, &b);
 * vector_pop(&v, NULL);
 * // v = [42]
 * ~~~
 *
 * @param v vector to remove the element from
 * @param df function to free the data, if NULL is passed it is ignored
 */
extern void vector_pop(vector_t *v, void (*df)(void *));


/**
 * @brief Delete a element from the vector
 *
 * ~~~{.c}
 * vector_t v = VECTOR_INIT(8);
 * int a = 42;
 * int b = 24;
 * vector_push(&v, &a);
 * vector_remove(&v, 0, NULL);
 * // v = [24]
 * ~~~
 *
 * @param v     vector
 * @param index of the element to remove
 * @param df    deleting function for the given element. df is ignored if NULL
 */
extern void vector_remove(vector_t *v, size_t index, void (*df)(void *));


/** @brief Retrieve the data at given index.
 *
 * ~~~{.c}
 * vector_t v = VECTOR_INIT(8);
 * int a = 42;
 * vector_push(&v, &a);
 * int a = vector_get(&v, 0);
 * print("%d", a); // 42
 * ~~~
 *
 *  @param list fetch the data of this arrayList
 *  @param i index to fetch
 *  @return returns the pointer to the data
 **/
extern void *vector_get(const vector_t *v, size_t index);


/** @brief Apply the funtion f to every element in the vector
 *
 * ~~~{.c}
 * vector_t v = VECTOR_INIT(8);
 * int a = 42;
 * vector_push(&v, &a);
 * vector_foreach(&v, addTwo);
 * // v = [44]
 * ~~~
 *
 *  @param list vector to operate on
 *  @param f function to apply
 **/
extern void vector_foreach(const vector_t *v, void (*f)(void *));


/** @brief Delete the vector and free allocated memory.
 *  The elements of the vector will not be freed.
 *
 *  ~~~{.c}
 *  vector_t *v = vector_new();
 *  vector_del(v);
 *  ~~~
 *
 *  @param v vector to delete
 **/
extern void vector_del(vector_t *v);


/**
 * @brief Remove all elements from the vector, in case that df is NULL every entry is set to 0
 *
 * ~~~{.c}
 * vector_t *v = vector_new();
 * int a = 42;
 * vector_push(v, &a);
 * vector_clear(v, NULL);
 * // v= []
 * ~~~
 *
 * @param v  vector to clear
 * @param df deleting function for heap allocated data
 */
extern void vector_clear(vector_t *v, void (*df)(void *));


/** @brief Remove all elements and free the vector_t
 *
 * ~~~{.c}
 * vector_t *v = vector_new();
 * int a = 42;
 * vector_push(v, &a);
 * vector_clear_del(v, NULL);
 * // v = NULL
 * ~~~
 *  @param v vector_t to delete
 *  @param df function with which the data should be deleted
 **/
extern void vector_clear_del(vector_t *v, void (*df)(void *));


/**
 * @brief Check whether a element is in the vector.
 * for an int created on the stack:
 *      return memcmp(a, *(void **)b, sizeof(int32_t))
 *
 * @param  v    vector to search
 * @param  key  item to find
 * @param  pred predicate function
 * @return      returns true on succuss and false on failure
 */
extern bool vector_contains(const vector_t *v,
                            const void *key,
                            int (*pred)(const void *, const void *));


/**
 * @brief Find an element in given vector
 * @param  v    vector to search
 * @param  key  key property
 * @param  pred predicate function
 * @return      returns the item found, NULL is returned in case of an error
 */
extern void *vector_find(const vector_t *v,
                         const void *key,
                         bool (*pred)(const void *, const void *));


/**
 * @brief Sort the vector with quicksort
 * @param v    vector to sort
 * @param pred predicate function
 */
extern void vector_sort(vector_t *v, int (*pred)(const void *, const void *));


#endif /*CUVECTOR_H_ */
