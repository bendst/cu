#pragma once
#include <stdint.h>

/** @brief dynamic Array
 *
 */
typedef struct  {
    /** data **/
    void **data;
    /** allokierter memory **/
    uint32_t memsize;
    /** member counter **/
    uint32_t count;
} vector_t;

/** creates a new empty array
 *  @result returns a new arrayList
 **/
extern vector_t *vector_new();


/** creates a empty array of the size n
 *  @param n size of the empty array
 *  @param returns a new vector
 **/
extern vector_t *vector_with_cap(uint32_t n);


/** appends a element to the vector
 *  @param list arrayList to which the data should be added
 *  @param data pointer to add
 **/
extern void vector_append(vector_t *v, void *data);


/****/
extern void vector_del_at(vector_t *v, uint32_t index, void df(void *));


/** returns the data of the index
 *  @param list fetch the data of this arrayList
 *  @param i index to fetch
 *  @result returns the pointer to the data
 **/
extern void *vector_get(vector_t *v, uint32_t index);


/** apply the funtion f to every element in the vector
 *  @param list vector to operate on
 *  @param f function to apply
 **/
extern void vector_foreach(vector_t *v, void (*f)(void *));


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
