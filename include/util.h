#ifndef CU_UTIL_H_
#define CU_UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * @file util.h
 * @brief Contains various helper functions
 */



#define switch_ptr(D, S) void *tmp = dst; \
    D = S; \
    S = tmp; \

#define new(name, ty) ty name = 0;

#define is_null(P) (P == NULL)

#define null_err(P, MSG) if is_null(P) { \
        fprintf(stderr, MSG); \
        abort(); \
    }

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

/**
 * @brief Levels of Logging
 */
enum log {
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
extern void cu_log_level(enum log level);


/**
 * @brief Print a log to target.
 * @param level Level of the Message
 * @param msg Message to print
 */
extern void cu_log(enum log level, const char *msg);

/**
 * @brief initializing function for cu internals
 * @param delfn function which shall be called by atexit()
 */
extern void cu_init(void (*delfn)());

typedef struct _dbg_struct dbg_struct_t;

enum type {
    str_type,
    int_type,
    float_type,
    double_type,
};


extern dbg_struct_t *debug_name(char *name);

extern void debug_field(dbg_struct_t *self, char *name, void *content, enum type type);

extern char *debug_finish(dbg_struct_t *self);

extern void debug_clean(dbg_struct_t *self);

#endif /* CU_UTIL_H_ */
