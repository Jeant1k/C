#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    double *buf;
    int pool_size;
    int size;
    int first;
} queue_dbl;

void qdbl_init(queue_dbl *q);
void qdbl_destroy(queue_dbl *q);

int qdbl_get_size(queue_dbl *q);

double qdbl_pop_front(queue_dbl *q);
bool qdbl_push_back(queue_dbl *q, double val);

bool qdbl_is_empty(queue_dbl *q);

