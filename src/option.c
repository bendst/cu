#include <stdio.h>
#include <stdlib.h>

#include "option.h"

static void *option_unwrap(const option_t *option) {
    if (option->_options) {
        return option->data;
    } else {
        fprintf(stderr, "unwrap failed\n");
        abort();
    }
}

static void *option_unwrap_or(const option_t *option, void *alt) {
    if (option->_options) {
        return option->data;
    } else {
        return alt;
    }
}

static void *option_expect(const option_t *option, const char *msg) {
    if (option->_options) {
        return option->data;
    } else {
        fprintf(stderr, "%s\n", msg);
        abort();
    }
}

static bool option_is_some(const option_t *option) {
    return option->_options == some;
}

static bool option_is_none(const option_t *option) {
    return option->_options == none;
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
