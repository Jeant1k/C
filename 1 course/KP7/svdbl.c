#include "svdbl.h"

static const int K_SIZE = 2;

static bool grow_buffer(svector_dbl *v);
static void shift_front(svector_dbl *v);
static void shift_back(svector_dbl *v, size_t shift, size_t count);
static void shrink_buffer(svector_dbl *v);

void svdbl_init(svector_dbl *v) {
    v->size = 0;
    v->pool_size = 0;
    v->buf = NULL;
    v->first = 0;
}

void svdbl_destroy(svector_dbl *v) {
    v->size = 0;
    v->pool_size = 0;
    free(v->buf);
    v->buf = NULL;
    v->first = 0;
}

size_t svdbl_get_size(svector_dbl *v) {
    return v->size;
}

bool svdbl_set_size(svector_dbl *v, size_t new_size) {
    if (new_size < v->size) {
        v->size = new_size;
        if (v->size * 4 <= v->pool_size) {
            shrink_buffer(v);
        }
    }
    else if (new_size > v->size) {
        while (new_size > v->pool_size) {
            if (!grow_buffer(v)) return false;
        }
        for (size_t i = v->size; i < new_size; i++) {
            v->buf[(v->first + i) % v->pool_size] = 0;
        }
        v->size = new_size;
    }
    return true;
}

bool svdbl_push_front(svector_dbl *v, double val) {
    if (!svdbl_set_size(v, v->size+1)) return false;
    v->first = (v->first - v->pool_size-1) % v->pool_size;
    v->buf[v->first] = val;
    return true;
}

bool svdbl_push_back(svector_dbl *v, double val) {
    if (!svdbl_set_size(v, v->size+1)) return false;
    v->buf[(v->first + v->size-1) % v->pool_size] = val;
    return true;
}

double svdbl_pop_front(svector_dbl *v) {
    double res = svdbl_get_front(v);
    v->first = (v->first+1) % v->pool_size;
    svdbl_set_size(v, v->size-1);
    return res;
}

double svdbl_pop_back(svector_dbl *v) {
    double res = svdbl_get_back(v);
    svdbl_set_size(v, v->size-1);
    return res;
}

double svdbl_get(svector_dbl *v, size_t i) {
    return v->buf[(v->first + i) % v->pool_size];
}
void svdbl_set(svector_dbl *v, size_t i, double val) {
    v->buf[(v->first + i) % v->pool_size] = val;
}

double svdbl_get_front(svector_dbl *v) {
    return v->buf[v->first];
}

double svdbl_get_back(svector_dbl *v) {
    return v->buf[(v->first + v->size-1) % v->pool_size];
}

bool svdbl_is_empty(svector_dbl *v) {
    return v->size == 0;
}

static bool grow_buffer(svector_dbl *v) {
    size_t new_size = v->pool_size * K_SIZE;
    if (v->pool_size == 0) new_size = 2 * K_SIZE;
    double *new_buf = realloc(v->buf, new_size * sizeof(double));
    if (new_buf == NULL) return false;
    v->buf = new_buf;
    v->pool_size = new_size;
    if (v->pool_size != 0 && (v->first + v->size) % v->pool_size <= v->first) shift_front(v);
    return true;
}

static void shift_front(svector_dbl *v) {
    for (size_t i = v->first; i < v->size; i++) {
        v->buf[v->size * (K_SIZE - 1) + i] = v->buf[i];
    }
    v->first = v->first + v->size;
}

static void shift_back(svector_dbl *v, size_t shift, size_t count) {
    for (size_t i = v->first; i < v->first + count; i++) {
        v->buf[i - shift] = v->buf[i];
    }
    v->first = v->first - shift;
}

static void shrink_buffer(svector_dbl *v) {
    size_t new_pool_size = v->pool_size / K_SIZE;
    if ((v->first + v->size) % v->pool_size > new_pool_size) {
        shift_back(v, v->first, v->size);
    }
    else if (v->first > new_pool_size) {
        shift_back(v, v->pool_size - new_pool_size, v->pool_size - v->first);
    }
    v->pool_size = new_pool_size;
    v->buf = realloc(v->buf, v->pool_size * sizeof(double));
}
