#include "util.h"


typedef struct {
    FILE *target;
    enum log current;
    size_t count;
} log_intern_t;

log_intern_t intern = {};

mutex_t log_intern_mut;

const char *const name[] = {
    "ALL",
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL",
};


static void (*deconstructor)() = NULL;
static void _cu_del();


inline void cu_init(void (*delfn)()) {
    log_intern_mut = cu_mutex_new(&intern);
    deconstructor = delfn;
    atexit(_cu_del);
}


static inline void _cu_del() {
    if (deconstructor != NULL) {
        deconstructor();
    }
    cu_mutex_del(&log_intern_mut, NULL);
}


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


inline void thread(pthread_t *thread, const pthread_attr_t *attr, void *(*handle)(void *), void *arg) {
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


inline void cu_log_target(FILE *fd) {
    log_intern_t *target = cu_lock(&log_intern_mut);
    if (fd == NULL) {
        target->target = stdout;
    } else {
        target->target = fd;
    }
    cu_unlock(&log_intern_mut);
}


inline void cu_log_level(enum log level) {
    log_intern_t *target = cu_lock(&log_intern_mut);
    target->current = level;
    cu_unlock(&log_intern_mut);
}


inline void cu_log(enum log level, const char *msg) {
    log_intern_t *target = cu_lock(&log_intern_mut);
    if (target->current <= level) {
        if (target->target == NULL) {
            target->target = stdout;
        }
        fprintf(target->target, "%ld: %s %s\n", target->count, name[level], msg);
        target->count += 1;
    }
    cu_unlock(&log_intern_mut);
}
