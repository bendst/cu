#ifndef CU_UTIL_H_
#define CU_UTIL_H_

/**
 * @file util.h
 * @brief Contains various helper functions
 */

/**
 * @brief wraper for memmove
 * @param  D destination
 * @param  S source
 * @param  N size
 */
#define memmove(D, S, N) void *err = memmove(D, S, N); \
    if (err != D) { \
        perror("memmove"); \
        abort(); \
    }

/**
 * @brief wrapper for calloc
 * @param  NM object count
 * @param  S  size
 * @return    pointer to allocated memory
 */
#define calloc(NM, S) ({ \
        void *ptr = calloc(NM, S); \
        if (ptr == NULL) { \
            perror("calloc"); \
            abort(); \
        } \
        ptr; \
    })
/**
 * @brief wrapper for malloc
 * @param  S size
 * @return    pointer to allocated memory
 */
#define malloc(S) ( \
        {calloc(1, S); } \
        )


#define push(x, y) _Generic((x), \
                            vector_t * : vector_push((vector_t *)x, y), \
                            list_t * : list_push_back((list_t *)x, y) \
                            )

#define new(x) _Generic((x), \
                        vector_t * : vector_new(), \
                        list_t * : list_new() \
                        )

#define clear(x, fn) _Generic((x), \
                              vector_t * : vector_clear((vector_t *)x, fn), \
                              list_t * : list_clear((list_t *)x, fn) \
                              )

#define del(x) _Generic((x), \
                        vector_t * : vector_del((vector_t *)x), \
                        list_t * : list_del((list_t *)x) \
                        )

#define clear_del(x, fn) _Generic((x), \
                                  vector_t * : vector_clear_del((vector_t *)x, fn), \
                                  list_t * : list_clear_del((list_t *)x, fn) \
                                  )
#define len(x) _Generic((x), \
                        vector_t * : vector_len((vector_t *)x), \
                        list_t * : list_len((list_t *)x) \
                        )

#define foreach(x, fn) _Generic((x), \
                                vector_t * : vector_foreach((vector_t *)x, fn), \
                                list_t * : list_foreach((list_t *)x, fn) \
                                )

#endif /* CU_UTIL_H_ */
