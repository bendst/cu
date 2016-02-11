#ifndef CUUTIL_H_
#define CUUTIL_H_

/**
 * @file util.h
 * @brief Contains various helper functions
 */

#define memmove(D, S, N) void *err = memmove(D, S, N); \
    if (err != D) { \
        perror("memmove"); \
        abort(); \
    }


#define calloc(NM, S) ({ \
        void *ptr = calloc(NM, S); \
        if (ptr == NULL) { \
            perror("calloc"); \
            abort(); \
        } \
        ptr; \
    })

#define malloc(S) (\
    {calloc(1, S);}\
)

#endif /* CUUTIL_H_ */
