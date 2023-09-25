#ifndef MY_DYNAMIC_VECTOR_SVINT_H
#define MY_DYNAMIC_VECTOR_SVINT_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *buf;
    int pool_size;
    int first;
    int size;
} svector_int;

void svint_init(svector_int *v);
void svint_destroy(svector_int *v);

int svint_get_size(svector_int *v);
bool svint_set_size(svector_int *v, int new_size);

bool svint_push_front(svector_int *v, int val);
bool svint_push_back(svector_int *v, int val);
int svint_pop_front(svector_int *v);
int svint_pop_back(svector_int *v);

int svint_get(svector_int *v, int i);
void svint_set(svector_int *v, int i, int val);

int svint_get_front(svector_int *v);
int svint_get_back(svector_int *v);

bool svint_is_empty(svector_int *v);

#endif
