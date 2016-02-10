#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cu.h"

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


int main(int argc, char const *argv[]) {
    vector_t *v1 = vector_new();
    vector_t v2 = VECTOR_INIT(20);
    int32_t array[40] = {
        0
    };
    for (size_t i = 0; i < 40; i++) {
        array[i] = i;
    }
    for (size_t i = 0; i < 20; i++) {
        vector_push(v1, &array[i]);
        vector_push(&v2, &array[i]);
    }

    //vector_foreach(v1, print);
    vector_foreach(&v2, print);

    VECTOR_DEL(v2, NULL);

    int key = 21;
    int result = vector_contains(v1, &key, has_int);
    printf("HAS %d %d\n", key, result);


    key = 5;
    result = vector_contains(v1, &key, has_int);
    printf("HAS %d %d\n", key, result);


    vector_sort(v1, reverse_order);
    printf("sort\n");
    vector_remove(v1, 2, NULL);
    vector_foreach(v1, print);


    vector_del(v1);


    list_t l2 = LIST_INIT;
    printf("%p %p %p\n", &l2, l2.head, l2.tail);
    printf("list size: %ld\n", l2.size);
    for (size_t i = 21; i < 40; i++) {
        list_push_back(&l2, &array[i]);
    }
    printf("list size: %ld\n", l2.size);


    list_foreach(&l2, print);
    LIST_DEL(l2, NULL);
    /* printf("%p %p %p\n",&l2, l2.head, l2.tail ); */
    exit(0);

    list_t *l1 = list_new();
    printf("list size: %ld\n", l1->size);
    for (size_t i = 0; i < 20; i++) {
        list_push_back(l1, &array[i]);
    }
    printf("list size: %ld\n", l1->size);


    list_foreach(l1, print);
    list_del(l1);
    /*
     * list_filter(l1, NULL, NULL);
     * list_find(NULL, NULL, NULL);
     */
    return 0;
}
