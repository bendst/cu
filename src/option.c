#include <stdio.h>
#include <stdlib.h>

#include "option.h"

static void *option_unwrap(const option_t *self) {
    if (self->_options) {
        return self->data;
    } else {
        fprintf(stderr, "unwrap failed\n");
        exit(EXIT_FAILURE);
    }
}

static void *option_unwrap_or(const option_t *self, void *alt) {
    if (self->_options) {
        return self->data;
    } else {
        option_t opt = option(alt);
        return opt.unwrap(&opt);
    }
}

static void *option_expect(const option_t *self, const char *msg) {
    if (self->_options) {
        return self->data;
    } else {
        fprintf(stderr, "%s\n", msg);
        exit(EXIT_FAILURE);
    }
}

static bool option_is_some(const option_t *self) {
    return self->_options == some;
}

static bool option_is_none(const option_t *self) {
    return self->_options == none;
}

option_t option(void *data) {
    option_t opt;
    if (data != NULL) {
        opt._options = some;
    } else {
        opt._options = none;
    }
    opt.expect = option_expect;
    opt.unwrap = option_unwrap;
    opt.unwrap_or = option_unwrap_or;
    opt.is_none = option_is_none;
    opt.is_some = option_is_some;
    opt.data = data;
    return opt;
}
