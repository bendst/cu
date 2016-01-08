#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define UNIMPLEMENTED (fprintf(stderr, "not implemented %s@%d\n", __FILE__, \
                               __LINE__); exit(EXIT_FAILURE))

#include "vector.h"
#include "list.h"
