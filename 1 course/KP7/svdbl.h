#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    double *buf;
    size_t pool_size;
    size_t first;
    size_t size;
} svector_dbl;

void svdbl_init(svector_dbl *v);
void svdbl_destroy(svector_dbl *v);

size_t svdbl_get_size(svector_dbl *v);
bool svdbl_set_size(svector_dbl *v, size_t new_size);

bool svdbl_push_front(svector_dbl *v, double val);
bool svdbl_push_back(svector_dbl *v, double val);
double svdbl_pop_front(svector_dbl *v);
double svdbl_pop_back(svector_dbl *v);

double svdbl_get(svector_dbl *v, size_t i);
void svdbl_set(svector_dbl *v, size_t i, double val);

double svdbl_get_front(svector_dbl *v);
double svdbl_get_back(svector_dbl *v);

bool svdbl_is_empty(svector_dbl *v);
