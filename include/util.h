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
 * @brief initializing function for cu internals
 * @param delfn function which shall be called by atexit()
 */
extern void cu_init(void (*delfn)());


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

#endif /* CU_UTIL_H_ */
