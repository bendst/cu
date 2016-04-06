#include "util.h"


pthread_mutex_t mut_log = PTHREAD_MUTEX_INITIALIZER;

static FILE *target = NULL;
static enum Log current = ALL;
const char *const name[] = {
    "ALL",
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL",
};
static size_t count = 0;


inline void cu_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr) {
    int err = pthread_mutex_init(mutex, attr);
    if (err != 0) {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }
}


inline void cu_mutex_lock(pthread_mutex_t *mutex) {
    int err = pthread_mutex_lock(mutex);
    if (err != 0) {
        perror("pthread_mutex_lock");
        exit(EXIT_FAILURE);
    }
}


inline void cu_mutex_unlock(pthread_mutex_t *mutex) {
    int err = pthread_mutex_unlock(mutex);
    if (err != 0) {
        perror("pthread_mutex_unlock");
        exit(EXIT_FAILURE);
    }
}


inline void cu_mutex_destroy(pthread_mutex_t *mutex) {
    int err = pthread_mutex_destroy(mutex);
    if (err != 0) {
        perror("pthread_mutex_destroy");
        exit(EXIT_FAILURE);
    }
}


inline void cu_thread(pthread_t *thread, const pthread_attr_t *attr, void *(*handle)(void *), void *arg) {
    int err = pthread_create(thread, attr, handle, arg);
    if (err != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
}

inline void cu_thread_exit(void *retval) {
    pthread_exit(retval);    
}


inline void cu_thread_join(pthread_t thread, void **retval) {
    int err = pthread_join(thread, retval);
    if (err != 0) {
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }
}


inline extern void cu_thread_cancel(pthread_t thread) {
    int err = pthread_cancel(thread);
    if (err != 0) {
        perror("pthread_cancel");
        exit(EXIT_FAILURE);
    }
}


inline void cu_log_target(FILE *fd) {
    cu_mutex_lock(&mut_log);
    if (fd == NULL) {
        target = stdout;
    } else {
        target = fd;
    }
    cu_mutex_unlock(&mut_log);
}


inline void cu_log_level(enum Log level) {
    cu_mutex_lock(&mut_log);
    current = level;
    cu_mutex_unlock(&mut_log);
}


inline void cu_log(enum Log level, const char *msg) {
    cu_mutex_lock(&mut_log);
    if (current <= level) {
        if (target == NULL) {
            target = stdout;
        }
        fprintf(target, "%ld: %s %s\n", count, name[level], msg);
        count += 1;
    }
    cu_mutex_unlock(&mut_log);
}
