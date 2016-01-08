#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "vector.h"

void print(void *ptr){
    int32_t data = *(int32_t*)ptr;
    printf("%d\n", data );
}

int main(int argc, char const *argv[]) {
    vector_t *v1 = vector_new();

    int32_t array[20] = {0};
    for (size_t i = 0; i < 20; i++) {
        array[i] = i;
    }
    for (size_t i = 0; i < 20; i++) {
        void *data = &array[i];
        vector_append(v1, data);
    }

    vector_foreach(v1, print);
    vector_del(v1);
    return 0;
}
