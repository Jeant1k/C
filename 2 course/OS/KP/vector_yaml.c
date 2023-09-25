#include "vector_yaml.h"

bool vyaml_init(vector_yaml *v, size_t size) {
    
    v -> size = size;
    v -> buf = malloc(size * sizeof(job));
    if (v -> buf == NULL) {
        v -> size = 0;
        return false;
    }
    for (size_t i = 0; i < size; i++) {
        v -> buf[i].id = -1;
        for (int j = 0; j < NUMBER_CHILDS; j++) {
            v -> buf[i].child_ids[j] = -1;
        }
        for (int j = 0; j < LENGTH_PATH; j++) {
            v -> buf[i].path[j] = '\0';
        }
        v -> buf[i].num_parents = 0;
        v -> buf[i].num_completed_parents = 0;
        v -> buf[i].barrier = false;
        v -> buf[i].barrier_name = -1;
        v -> buf[i].num_barriers = 0;
        v -> buf[i].num_completed_barriers = 0;
    }
    
    return true;
    
}

void vyaml_destroy(vector_yaml *v) {
    free(v -> buf);
    v -> buf = NULL;
    v -> size = 0;
}

size_t vyaml_get_size(vector_yaml *v) {
    return v -> size;
}

bool vyaml_set_size(vector_yaml *v, size_t new_size) {
    
    size_t size = v -> size;
    v -> size = new_size;
    if (v -> size != new_size) {
        return false;
    }
    v -> buf = realloc(v -> buf, v -> size);
    
    for (size_t i = size; i < new_size; i++) {
        v -> buf[i].id = -1;
        for (int j = 0; j < NUMBER_CHILDS; j++) {
            v -> buf[i].child_ids[j] = -1;
        }
        for (int j = 0; j < LENGTH_PATH; j++) {
            v -> buf[i].path[j] = '\0';
        }
        v -> buf[i].num_parents = 0;
        v -> buf[i].num_completed_parents = 0;
        v -> buf[i].barrier = false;
        v -> buf[i].barrier_name = -1;
        v -> buf[i].num_barriers = 0;
        v -> buf[i].num_completed_barriers = 0;
    }
    
    return true;
    
}

job vyaml_get(vector_yaml *v, size_t i) {
    return v -> buf[i];
} 

void vyaml_set(vector_yaml *v, size_t i, job new_val) {
    v -> buf[i] = new_val;
}
