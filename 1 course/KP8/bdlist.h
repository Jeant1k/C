#include <stdlib.h>
#include <stdbool.h>

typedef struct listel lestel;
struct listel {
    double val;
    struct listel *next;
    struct listel *prev;
};

typedef struct {
    struct listel *first;
    struct listel *last;
} list;

void list_init(list *l);
void list_destroy(list *l);
bool list_is_empty(list *l);

typedef struct {
    list *lst;
    struct listel *cur;
} list_iter;

list_iter list_iter_begin(list *l);
list_iter list_iter_end(list *l);
bool list_iter_equal(list_iter it1, list_iter it2);
void list_iter_move_next(list_iter *it);
void list_iter_move_prev(list_iter *it);
double list_iter_get(list_iter *it);

void list_iter_set(list_iter *it, double val);
bool list_iter_insert_before(list_iter *it, double val);
bool list_iter_remove(list_iter *it);
