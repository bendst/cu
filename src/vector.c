#include "cu.h"
#include <stdlib.h>
#include <string.h>

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


inline void vector_append(vector_t *v, void *data) {
    if (v->memsize == 0 || !v) {
        v = vector_with_cap(10);
    } else if (v->memsize == v->count) {
        v->memsize *= 2;
        v->data = realloc(v->data, sizeof (void *) * v->memsize);

    }
    v->data[v->count++] = data;
}


inline void vector_del_at(vector_t *v, uint32_t index, void df(void *)) {
    uint32_t i = index;
    if (v->count <= index) {
        i = v->count - 1;
    }
    void *to_delete = v->data[i];
    df(to_delete);
    uint32_t diff = v->count - i + 1;
    memmove(v->data + i, v->data + i + 1, sizeof(void *) * diff);
    v->count--;
}


inline void *vector_get(vector_t *v, uint32_t index) {
    if (index >= v->count) {
        index = v->count - 1;
    }
    return index < v->count ? v->data[index] : NULL;
}


inline void vector_foreach(vector_t *v, void (*f)(void *)) {
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
    vector_foreach(v, df);
    v->count = 0;
}


inline void vector_clear_del(vector_t *v, void (*df)(void *)) {
    vector_clear(v, df);
    vector_del(v);
}
