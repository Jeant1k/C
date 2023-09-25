#include "qdbl.h"

#define POOL_SIZE 64
#define K_SIZE 2

void qdbl_init(queue_dbl *q) {
    q -> buf = malloc(POOL_SIZE * sizeof(double));
    q -> pool_size = POOL_SIZE;
    q -> size = 0;
    q -> first = 0;
}
void qdbl_destroy(queue_dbl *q) {
    free(q -> buf);
    q -> buf = NULL;
    q -> pool_size = 0;
    q -> size = 0;
    q -> first = 0;
}

int qdbl_get_size(queue_dbl *q) {
    return q -> size;
}

double qdbl_pop_front(queue_dbl *q) {
    double val = q -> buf[q -> first];
    q -> buf[q -> first] = 0;
    q -> first++;
    q -> size--;
    return val;
}

bool qdbl_push_back(queue_dbl *q, double val) {
    if (q -> size >= q -> pool_size) {
        double *new_buf = realloc(q -> buf, sizeof(double) * q -> pool_size * K_SIZE);
        if (new_buf == NULL) {
            return false;
        }
        q -> buf = new_buf;
        q -> pool_size = q -> pool_size * K_SIZE;
    }
    q -> buf[q -> size] = val;
    q -> size++;
    return true;
}

bool qdbl_is_empty(queue_dbl *q) {
    return q -> size == 0;
}
