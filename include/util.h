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

#endif /* CU_UTIL_H_ */
