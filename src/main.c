#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cu.h"


struct Test {
    float a;
    int b;
    char *c;
};

void print(void *ptr) {
    int32_t data = *(int32_t *)ptr;
    printf("%d\n", data);
}

int reverse_order(const void *a, const void *b) {
    int aint = *(int *)a;
    int bint = *(int *)b;
    return bint - aint;
}

int has_int(const void *a, const void *b) {
    return memcmp(a, *(void **)b, sizeof(int32_t));
}

int main() {
    vector_t v = vector_new();
    int a = 42;
    vector_push(&v, &a);
    return 0;
}
