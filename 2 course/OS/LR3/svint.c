#include "svint.h"

static const int K_SIZE = 2;

static bool grow_buffer(svector_int *v);
static void shift_front(svector_int *v);
static void shift_back(svector_int *v, int shift, int count);
static void shrink_buffer(svector_int *v);

void svint_init(svector_int *v) {
    v->size = 0;
    v->pool_size = 0;
    v->buf = NULL;
    v->first = 0;
}

void svint_destroy(svector_int *v) {
    v->size = 0;
    v->pool_size = 0;
    free(v->buf);
    v->buf = NULL;
    v->first = 0;
}

int svint_get_size(svector_int *v) {
    return v->size;
}

bool svint_set_size(svector_int *v, int new_size) {
    if (new_size < v->size) {
        v->size = new_size;
        if (v->size * 4 <= v->pool_size) {
            shrink_buffer(v);
        }
        if (v->size == 0)
            v->first = 0;
    }
    else if (new_size > v->size) {
        while (new_size > v->pool_size) {
            if (!grow_buffer(v)) return false;
        }
        for (int i = v->size; i < new_size; i++) {
            v->buf[(v->first + i) % v->pool_size] = 0;
        }
        v->size = new_size;
    }
    return true;
}

bool svint_push_front(svector_int *v, int val) {
    if (!svint_set_size(v, v->size+1)) return false;
    v->first = (v->first - v->pool_size-1) % v->pool_size;
    v->buf[v->first] = val;
    return true;
}

bool svint_push_back(svector_int *v, int val) {
    if (!svint_set_size(v, v->size+1)) return false;
    v->buf[(v->first + v->size-1) % v->pool_size] = val;
    return true;
}

int svint_pop_front(svector_int *v) {
    int res = svint_get_front(v);
    v->first = (v->first+1) % v->pool_size;
    svint_set_size(v, v->size-1);
    return res;
}

int svint_pop_back(svector_int *v) {
    int res = svint_get_back(v);
    svint_set_size(v, v->size-1);
    return res;
}

int svint_get(svector_int *v, int i) {
    return v->buf[(v->first + i) % v->pool_size];
}
void svint_set(svector_int *v, int i, int val) {
    v->buf[(v->first + i) % v->pool_size] = val;
}

int svint_get_front(svector_int *v) {
    return v->buf[v->first];
}

int svint_get_back(svector_int *v) {
    return v->buf[(v->first + v->size-1) % v->pool_size];
}

bool svint_is_empty(svector_int *v) {
    return v->size == 0;
}

static bool grow_buffer(svector_int *v) {
    int new_size = v->pool_size * K_SIZE;
    if (v->pool_size == 0) new_size = 2 * K_SIZE;
    int *new_buf = realloc(v->buf, new_size * sizeof(int));
    if (new_buf == NULL) return false;
    v->buf = new_buf;
    v->pool_size = new_size;
    if (v->pool_size != 0 && (v->first + v->size) % v->pool_size <= v->first) shift_front(v);
    return true;
}

static void shift_front(svector_int *v) {
    for (int i = v->first; i < v->size; i++) {
        v->buf[v->size * (K_SIZE - 1) + i] = v->buf[i];
    }
    v->first = v->first + v->size;
}

static void shift_back(svector_int *v, int shift, int count) {
    for (int i = v->first; i < v->first + count; i++) {
        v->buf[i - shift] = v->buf[i];
    }
    v->first = v->first - shift;
}

static void shrink_buffer(svector_int *v) {
    int new_pool_size = v->pool_size / K_SIZE;
    if ((v->first + v->size) % v->pool_size > new_pool_size) {
        shift_back(v, v->first, v->size);
    }
    else if (v->first > new_pool_size) {
        shift_back(v, v->pool_size - new_pool_size, v->pool_size - v->first);
    }
    v->pool_size = new_pool_size;
    v->buf = realloc(v->buf, v->pool_size * sizeof(int));
}
