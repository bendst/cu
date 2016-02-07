#ifndef CUVECTOR_H_
#define CUVECTOR_H_
#include <stdint.h>
#include <stdbool.h>

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
extern void vector_push(vector_t *v, void *data);


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

/**
 * clearing a vector, in case that df is NULL every entry is set to 0
 * @param v  vector to clear
 * @param df deleting function for heap allocated data
 */
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
 * find an element in given vector
 * @param  v    vector to search
 * @param  key  key property
 * @param  pred predicate function
 * @return      returns the item found, NULL is returned in case of an error
 */
extern void *vector_find(const vector_t *v,
                         const void *key,
                         bool (*pred)(const void *,
                                      const void *));


/**
 * Sort the vector with quicksort
 * @param v    vector to sort
 * @param pred predicate function
 */
extern void vector_sort(vector_t *v, int (*pred)(const void *, const void *));


#endif /*CUVECTOR_H_ */
