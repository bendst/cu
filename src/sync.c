#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sync.h"

/* ####################################### */
// Cu Mutex
/* ####################################### */
inline mutex_t cu_mutex_new(void *inner) {
    mutex_t _mutex;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    _mutex.mutex = mutex;
    _mutex.inner = inner;
    return _mutex;
}


inline void *cu_lock(mutex_t *mutex) {
    mutex_lock(&mutex->mutex);
    return mutex->inner;
}


inline void cu_unlock(mutex_t *mutex) {
    mutex_unlock(&mutex->mutex);
}


inline void cu_mutex_del(mutex_t *mutex, void (*del)(void *)) {
    mutex_destroy(&mutex->mutex);
    if (del != NULL) {
        del(mutex->inner);
    }
}

/* ####################################### */
// CU THREAD
/* ####################################### */
inline thread_t cu_thread_new(void *(*handle)(), void *args) {
    thread_t thread;
    if (handle == NULL) {
        fprintf(stderr, "handle is not a valid function\n");
        exit(EXIT_FAILURE);
    }
    thread.handle = handle;
    thread.args = args;
    attr_init(&thread.attr);
    memset(&thread.thread, 0, sizeof(pthread_t));
    return thread;
}

inline void cu_spawn(thread_t *_thread) {
    thread_new(&_thread->thread, &_thread->attr, _thread->handle, _thread->args);
}

inline void *cu_join(thread_t *_thread) {
    void *retval = NULL;
    thread_join(_thread->thread, &retval);
    return retval;
}

/* ######################################## */
// Pthread Wrapper
/* ####################################### */
inline void mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr) {
    int err = pthread_mutex_init(mutex, attr);
    if (err != 0) {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }
}


inline void mutex_lock(pthread_mutex_t *mutex) {
    int err = pthread_mutex_lock(mutex);
    if (err != 0) {
        perror("pthread_mutex_lock");
        exit(EXIT_FAILURE);
    }
}


inline void mutex_unlock(pthread_mutex_t *mutex) {
    int err = pthread_mutex_unlock(mutex);
    if (err != 0) {
        perror("pthread_mutex_unlock");
        exit(EXIT_FAILURE);
    }
}


inline void mutex_destroy(pthread_mutex_t *mutex) {
    int err = pthread_mutex_destroy(mutex);
    if (err != 0) {
        perror("pthread_mutex_destroy");
        exit(EXIT_FAILURE);
    }
}


inline void thread_new(pthread_t *thread, const pthread_attr_t *attr, void *(*handle)(void *), void *arg) {
    int err = pthread_create(thread, attr, handle, arg);
    if (err != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
}

inline void thread_exit(void *retval) {
    pthread_exit(retval);
}


inline void thread_join(pthread_t thread, void **retval) {
    int err = pthread_join(thread, retval);
    if (err != 0) {
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }
}


inline extern void thread_cancel(pthread_t thread) {
    int err = pthread_cancel(thread);
    if (err != 0) {
        perror("pthread_cancel");
        exit(EXIT_FAILURE);
    }
}

inline void attr_init(pthread_attr_t *attr) {
    int err = pthread_attr_init(attr);
    if (err != 0) {
        perror("pthread_attr_init");
        exit(EXIT_FAILURE);
    }
}

inline void attr_destroy(pthread_attr_t *attr) {
    int err = pthread_attr_destroy(attr);
    if (err != 0) {
        perror("pthread_attr_destroy");
        exit(EXIT_FAILURE);
    }
}

