#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define VECTOR_NOT_INIT(V) if (V == NULL) {fprintf(stderr, \
                                                   "vector not initialized\n"); \
                                           exit(EXIT_FAILURE); }


inline vector_t *vector_new() {
    return vector_with_cap(10);
}


inline vector_t *vector_with_cap(uint32_t n) {
    vector_t *v = calloc(1, sizeof(vector_t));
    v->data = calloc(n, sizeof(void *));
    v->memsize = n;
    v->count = 0;
    return v;
}


inline void vector_push(vector_t *v, void *data) {
    VECTOR_NOT_INIT(v);
    if (v->memsize == 0 || !v) {
        v = vector_with_cap(10);
    } else if (v->memsize == v->count) {
        v->memsize *= 2;
        v->data = realloc(v->data, sizeof (void *) * v->memsize);
    }
    v->data[v->count++] = data;
}


inline void vector_del_at(vector_t *v, uint32_t index, void df(void *)) {
    VECTOR_NOT_INIT(v);
    uint32_t i = index;
    if (v->count <= index) {
        i = v->count - 1;
    }
    void *to_delete = v->data[i];
    if (df != NULL) {
        df(to_delete);
    }
    uint32_t diff = v->count - i + 1;
    void *err = memmove(v->data + i, v->data + i + 1, sizeof(void *) * diff);
    if (err != v->data + i) {
        fprintf(stderr, "deleting failed for %d\n", index);
        return;
    }
    v->count--;
}


inline void *vector_get(const vector_t *v, uint32_t index) {
    VECTOR_NOT_INIT(v);
    if (index >= v->count) {
        index = v->count - 1;
    }
    return index < v->count ? v->data[index] : NULL;
}


inline void vector_foreach(const vector_t *v, void (*f)(void *)) {
    VECTOR_NOT_INIT(v);
    uint32_t i;
    for (i = 0; i < v->count; i++) {
        f(v->data[i]);
    }
}


inline void vector_del(vector_t *v) {
    free(v->data);
    free(v);
}


inline void vector_clear(vector_t *v, void (*df)(void *)) {
    if (df == NULL) {
        memset(v->data, 0, sizeof(void *) * v->count);
    } else {
        vector_foreach(v, df);
    }
    v->count = 0;
}


inline void vector_clear_del(vector_t *v, void (*df)(void *)) {
    vector_clear(v, df);
    vector_del(v);
}


inline bool vector_contains(const vector_t *v, const void *key, int (*pred)(
                                const void *,
                                const void *)) {
    VECTOR_NOT_INIT(v);
    return bsearch(key, v->data, v->count, sizeof(void *), pred) != NULL;
}


inline void *vector_find(const vector_t *v, const void *key, bool (*pred)(
                             const void *,
                             const void *)) {
    VECTOR_NOT_INIT(v);
    void *item = NULL;
    for (uint32_t i = 0; i < v->count; i++) {
        item = vector_get(v, i);
        if (pred(key, item)) {
            return item;
        }
    }
    return NULL;
}


inline void vector_sort(vector_t *v, int (*pred)(const void *, const void *)) {
    VECTOR_NOT_INIT(v);
    qsort(v->data, v->count, sizeof(void *), pred);
}
