#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define UNIMPLEMENTED fprintf(stderr, "%s not implemented %s@%d\n", __func__, __FILE__, \
                               __LINE__); abort();

#include "vector.h"
#include "list.h"
