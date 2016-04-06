#ifndef CU_UTIL_H_
#define CU_UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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
        exit(EXIT_FAILURE); \
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
            exit(EXIT_FAILURE); \
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

/**
 * @brief Levels of Logging
 */
enum Log {
    ALL,
    INFO,
    WARNING,
    ERROR,
    FATAL
};


/** 
 * @brief Set the logging target.
 * @param fd Target File Descriptor
 */
extern void cu_log_target(FILE *fd);


/**
 * @brief Set the logging Level.
 * @param level Desired logging level
 */
extern void cu_log_level(enum Log level);


/**
 * @brief Print a log to target.
 * @param level Level of the Message
 * @param msg Message to print 
 */
extern void cu_log(enum Log level, const char *msg);


/**
 * @brief Wrapper around pthread_mutex_init() with error handling.
 * @param mutex Mutex
 * @param attr Attribute
 */
extern void cu_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);


/**
 * @brief Wrapper around pthread_mutex_lock() with error handling.
 * @param mutex Mutex
 */
extern void cu_mutex_lock(pthread_mutex_t *mutex);


/**
 * @brief Wrapper around pthread_mutex_unlock() with error handling.
 * @param mutex Mutex
 */
extern void cu_mutex_unlock(pthread_mutex_t *mutex);


/**
 * @brief Wrapper around pthread_mutex_destroy() with error handling.
 * @param mutex Mutex
 */
extern void cu_mutex_destroy(pthread_mutex_t *mutex);


/**
 * @brief Wrapper around pthread_thread_create() with error handling.
 * @param thread Thread
 * @param attr Attribute
 * @param handle Handle Function
 * @param arg Argument
 */
extern void cu_thread(pthread_t *thread, const pthread_attr_t *attr, void *(*handle)(void *), void *arg);


/**
 * @brief Wrapper around pthread_exit()
 * @param retval Return value
 */
extern void cu_thread_exit(void *retval);


/**
 * @brief Wrapper around pthread_join() with error handling.
 * @param thread Thread
 * @param retval Return Value
 */
extern void cu_thread_join(pthread_t thread, void **retval);


/** 
 * @brief Wrapper around pthread_cancel() with error handling.
 * @param thread Thread
 */
extern void cu_thread_cancel(pthread_t thread);


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

#define is_empty(x) _Generic((x), \
                             vector_t * : vector_is_empty((vector_t *)x), \
                             list_t * : list_is_empty((list_t *)x) \
                             )

#define find(x, key, pred) _Generic((x), \
                                    vector_t * : vector_find((vector_t *)x, key, pred), \
                                    list_t * : list_find((list_t *)x, key, pred) \
                                    )

#define insert(x, index, data) _Generic((x), \
                                        vector_t * : vector_insert((vector_t *)x, index, data), \
                                        list_t * : list_insert((list_t *) x, index, data) \
                                        )

#define contains(x, key, pred) _Generic((x), \
                                        vector_t * : vector_contains((vector_t *)x, key, pred), \
                                        list_t * : list_contains((list_t *)x, key, pred) \
                                        )

#endif /* CU_UTIL_H_ */
