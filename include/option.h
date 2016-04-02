#ifndef CU_OPTION_H_
#define  CU_OPTION_H_
#include <stdbool.h>

typedef struct option_t {
    enum  {
        none,
        some,
    } _options;
    void *data;
    void *(*unwrap)(const struct option_t *);
    void *(*expect)(const struct option_t *, const char *msg);
    void *(*unwrap_or)(const struct option_t *, void *);
    bool (*is_some)(const struct option_t *);
    bool (*is_none)(const struct option_t *);
} option_t;

option_t option(void *data);

#endif // CU_OPTION_H_
