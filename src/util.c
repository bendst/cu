#include "util.h"
#include "sync.h"

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
