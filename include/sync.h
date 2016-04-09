#ifndef CU_SYNC
#define CU_SYNC
#include<pthread.h>

/**
 *  @file sync.h
 *  @brief Structure for wrapping a generic object with a mutex
 *
 * The module contains functions with dealing with thread and syncronization.
 * 
 * Pthread wrapper function do not have the prefix cu, they can directly be 
 * transferred to pthread calls with error checking.
 *
 *
 */
typedef struct {
    pthread_mutex_t mutex;
    void *inner;
} mutex_t;


/**
 * @brief Initialize a CU mutex
 *
 * ~~~{.c}
 * struct complex_object {...};
 *
 *
 * ~~~
 *
 * @param mutex pthread mutex
 * @param inner data to surround with a mutex
 * @result a mutex_t obj
 */
extern mutex_t cu_mutex_new(void *inner);


/** @brief Destroy a cu mutex_t object and the data
 *  @param mutex to destroy
 *
 */
extern void cu_mutex_del(mutex_t *mutex, void (*del)(void *));

/**
 * @brief lock the mutex and get access to the data
 * @param mutex mutex to lock
 * @result locked data
 */
extern void *cu_lock(mutex_t *mutex);


/**
 * @brief Unlock a mutex_t object
 * @param mutex to lock
 */
extern void cu_unlock(mutex_t *mutex);


typedef struct {
    pthread_t thread;
    pthread_attr_t attr;
    void *(*handle)();
    void *args;
} thread_t;


/**
 * @brief Create a thread_t structur
 * @param handle handle function
 * @param arguments of the handle function
 * @result new thread_t
 */
extern thread_t cu_thread_new(void *(*handle)(), void *args);


/**
 * @brief Spawn a new thread
 * @param thread thread to spawn
 */
extern void cu_spawn(thread_t *thread);


/**
 * @brief Join a thread
 * @param thread to join
 * @result returns the result of joined thread
 */
extern void *cu_join(thread_t *thread);

/**
 * @brief Wrapper around pthread_mutex_init() with error handling.
 * @param mutex Mutex
 * @param attr Attribute
 */
extern void mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);


/**
 * @brief Wrapper around pthread_mutex_lock() with error handling.
 * @param mutex Mutex
 */
extern void mutex_lock(pthread_mutex_t *mutex);


/**
 * @brief Wrapper around pthread_mutex_unlock() with error handling.
 * @param mutex Mutex
 */
extern void mutex_unlock(pthread_mutex_t *mutex);


/**
 * @brief Wrapper around pthread_mutex_destroy() with error handling.
 * @param mutex Mutex
 */
extern void mutex_destroy(pthread_mutex_t *mutex);


/**
 * @brief Wrapper around pthread_thread_create() with error handling.
 * @param thread Thread
 * @param attr Attribute
 * @param handle Handle Function
 * @param arg Argument
 */
extern void thread_new(pthread_t *thread, const pthread_attr_t *attr, void *(*handle)(void *), void *arg);


/**
 * @brief Wrapper around pthread_exit()
 * @param retval Return value
 */
extern void thread_exit(void *retval);


/**
 * @brief Wrapper around pthread_join() with error handling.
 * @param thread Thread
 * @param retval Return Value
 */
extern void thread_join(pthread_t thread, void **retval);


/**
 * @brief Wrapper around pthread_cancel() with error handling.
 * @param thread Thread
 */
extern void thread_cancel(pthread_t thread);


extern void attr_init(pthread_attr_t *attr);
extern void attr_destory(pthread_attr_t *attr);

#endif /* ifndef CU_SYNC */
