#ifndef CUVECTOR_H_
#define CUVECTOR_H_

typedef struct {
    unsigned long used;
    unsigned long size;
    void **data;
}cuvector_t;

extern cuvector_t cuvec_new();
extern void cuvec_clear(cuvector_t *cv, void df(void *));
extern void cuvec_del(cuvector_t *cv);
extern void cuvec_clear_del(cuvector_t *cv, void df(void *));
extern void cuvec_push(cuvector_t *cv, void *data);
extern void cuvec_len(cuvector_t *cv);

#endif
