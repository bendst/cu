#include <string.h>
#include <stdio.h>
#include "vector.h"
#include "util.h"

#define VECTOR_NOT_INIT(V) if (V == NULL) { \
        fprintf(stderr, "vector not initialized\n"); \
        abort(); }

static inline void vector_push_front(vector_t *v, void *data) {
    VECTOR_NOT_INIT(v);
    if (v->memsize - 1 >= v->count) {
        memmove(v->data + 1, v->data, sizeof(void *) * v->count);
    } else {
        v->memsize *= 2;
        v->data = realloc(v->data, sizeof(void *) * v->memsize);
        memmove(v->data + 1, v->data, sizeof(void *) * v->count);
    }
    v->data[0] = data;
    v->count++;
}


inline vector_t *vector_new() {
    return vector_with_cap(8);
}

inline size_t vector_len(vector_t *v) {
    VECTOR_NOT_INIT(v);
    return v->count;
}

inline vector_t *vector_with_cap(size_t n) {
    vector_t *v = calloc(1, sizeof(vector_t));
    v->data = calloc(n, sizeof(void *));
    v->memsize = n;
    v->count = 0;
    return v;
}


inline void vector_insert(vector_t *v, size_t index, void *data) {
    VECTOR_NOT_INIT(v);

    if (index == 0) {
        vector_push_front(v, data);
    } else if (index > v->count) {
        vector_push(v, data);
    } else {
        size_t diff = v->count - index;
        if (v->memsize == v->count) {
            v->memsize *= 2;
            v->data = realloc(v->data, v->memsize * sizeof(void *));
        }
        memmove(v->data + index + 1, v->data + index, sizeof(void *) * diff);
        v->data[index] = data;
        v->count++;
    }

}


inline void vector_push(vector_t *v, void *data) {
    VECTOR_NOT_INIT(v);
    if (v->memsize == v->count) {
        v->memsize *= 2;
        v->data = realloc(v->data, sizeof(void *) * v->memsize);
    }
    v->data[v->count++] = data;
}


inline void vector_pop(vector_t *v, void (*df)(void *)) {
    vector_remove(v, v->count, df);
}


inline void vector_remove(vector_t *v, size_t index, void df(void *)) {
    VECTOR_NOT_INIT(v);
    size_t i = index;
    if (v->count <= index) {
        i = v->count - 1;
    }
    void *to_delete = v->data[i];
    if (df != NULL) {
        df(to_delete);
    }
    size_t diff = v->count - i + 1;
    memmove(v->data + i, v->data + i + 1, sizeof(void *) * diff);
    v->count--;
}


inline void *vector_get(const vector_t *v, size_t index) {
    VECTOR_NOT_INIT(v);
    if (index >= v->count) {
        index = v->count - 1;
    }
    return index < v->count ? v->data[index] : NULL;
}


inline void vector_foreach(const vector_t *v, void (*f)(void *)) {
    VECTOR_NOT_INIT(v);
    size_t i;
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
    for (size_t i = 0; i < v->count; i++) {
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
