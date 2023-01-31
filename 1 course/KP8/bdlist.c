#include "bdlist.h"

void list_init(list *l) {
    l -> first = NULL;
    l -> last = NULL;
}

bool list_is_empty(list *l) {
    return l -> first == NULL;
}

void list_destroy(list *l) {
    while (!list_is_empty(l)) {
        struct listel *tmp = l -> first;
        l -> first = l -> first -> next;
        free(tmp);
    }
    l -> first = NULL;
    l -> last = NULL;
}

list_iter list_iter_begin(list *l) {
    list_iter it;
    it.lst = l;
    it.cur = l -> first;
    return it;
}

list_iter list_iter_end(list *l) {
    list_iter it;
    it.lst = l;
    it.cur = NULL;
    return it;
}

bool list_iter_equal(list_iter it1, list_iter it2) {
    return it1.cur == it2.cur && it1.lst == it2.lst;
}

void list_iter_move_next(list_iter *it) {
    it -> cur = it -> cur -> next;
}

void list_iter_move_prev(list_iter *it) {
    it -> cur = it -> cur -> prev;
}

double list_iter_get(list_iter *it) {
    return it -> cur -> val;
}

void list_iter_set(list_iter *it, double val) {
    it -> cur -> val = val;
}

bool list_iter_insert_before(list_iter *it, double val) {
    struct listel *new_el = malloc(sizeof(struct listel));
    if (new_el == NULL) {
        return false;
    }
    new_el -> val = val;
    if (it -> lst -> first == NULL || it -> lst -> last == NULL) {
        new_el -> next = NULL;
        new_el -> prev = NULL;
        it -> lst -> first = new_el;
        it -> lst -> last = new_el;
        it -> cur = NULL;
    } else {
        if (it -> cur == NULL) {
            new_el -> prev = it -> lst -> last;
            new_el -> next = NULL;
            it -> lst -> last -> next = new_el;
            it -> lst -> last = new_el;
        } else if (it -> cur -> prev == NULL) { // эту ветку нужно проверить
            new_el -> next = it -> lst -> first;
            new_el -> prev = NULL;
            it -> cur -> prev = new_el;
            it -> lst -> first = new_el;
        } else { // эту ветку нужно проверить
            new_el -> next = it -> cur;
            new_el -> prev = it -> cur -> prev;
            it -> cur -> prev -> next = new_el; // Странная комбинация (prev -> next)
            it -> cur -> prev = new_el;
        }
    }
    return true;
}

bool list_iter_remove(list_iter *it) {
    if (it -> cur == NULL) {
        return false;
    }
    if (it -> cur -> prev == NULL && it -> cur -> next == NULL) {
        free(it -> cur);
        it -> cur = NULL;
        it -> lst -> first = NULL;
        it -> lst -> last = NULL;
        return true;
    }
    if (it -> cur -> prev == NULL && it -> cur -> next != NULL) {
        struct listel *tmp = it -> cur;
        it -> cur = it -> cur -> next;
        it -> cur -> prev = NULL;
        it -> lst -> first = it -> cur;
        free(tmp);
        return true;
    }
    if (it -> cur -> prev != NULL && it -> cur -> next == NULL) {
        struct listel *tmp = it -> cur;
        it -> cur -> prev -> next = NULL;
        it -> lst -> last = it -> cur -> prev;
        it -> cur = NULL;
        free(tmp);
        return true;
    }
    if (it -> cur -> prev != NULL && it -> cur -> next != NULL) {
        struct listel *tmp = it -> cur;
        it -> cur -> prev -> next = it -> cur -> next;
        it -> cur -> next -> prev = it -> cur -> prev;
        it -> cur = it -> cur -> next;
        free(tmp);
        return true;
    }
}
