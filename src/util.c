#include <string.h>
#include "util.h"
#include "list.h"
#include "vector.h"
#include "sync.h"
#include "generic.h"

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

struct _dbg_struct {
    char *name;
    vector_t fields;
};


dbg_struct_t *debug_name(char *name) {
    dbg_struct_t *dbg = calloc(1, sizeof(dbg_struct_t));
    dbg->fields = cu_new(&dbg->fields);
    size_t len = strlen(name);
    dbg->name = strndup(name, len);
    return dbg;
}

void debug_field(dbg_struct_t *self, char *name, void *content, enum type type) {
    size_t len = strlen(name);
    char *from_input;
    size_t len_content = 0;

    switch (type) {
    case str_type:
        len_content = strlen((char *) content);
        from_input = strndup((char *)content, len_content);
        break;
    case int_type:
        from_input = calloc(64, sizeof(char));
        len_content = snprintf(from_input, 64, "%d", *(int *)content);
        break;
    case float_type:
        from_input = calloc(64, sizeof(char));
        len_content = snprintf(from_input, 64, "%f", *(float *)content);
        break;
    case double_type:
        from_input = calloc(64, sizeof(char));
        len_content = snprintf(from_input, 64, "%f", *(double *)content);
        break;
    default:
        break;
    }
    // name: conten t
    char *field = calloc(len + 15 + len_content + 1, sizeof(char));
    snprintf(field, len + 15 + len_content + 1, "    %s: %s,\n", name, from_input);
    free(from_input);
    cu_push(&self->fields, field);
}



char *debug_finish(dbg_struct_t *self) {
    char *result = NULL;
    size_t total_len = 0;
    for (size_t i = 0; i < cu_len(&self->fields); i++) {
        total_len += strlen((char *) vector_get(&self->fields, i));
    }
    total_len += strlen(self->name) + 20;
    result = calloc(total_len + 1, sizeof(char));
    result = strncat(result, self->name, strlen(self->name));
    result = strncat(result, " {\n", total_len);

    for (size_t i = 0; i < cu_len(&self->fields); i++) {
        result = strncat(result, (char *)vector_get(&self->fields, i), total_len);
    }
    result = strncat(result, "}", total_len);
    return result;
}


void debug_clean(dbg_struct_t *self) {
    free(self->name);
    cu_clear_del(&self->fields, free);
    free(self);
}
