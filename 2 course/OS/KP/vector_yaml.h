#ifndef _VECTOR_YAML_H_
#define _VECTOR_YAML_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Представление данных в файле формата yaml:
// job_id_1:
//     id: 1
//     chiild: 4
//     path: "./timer.out"
//     barrier: "1"
// Последний пункт опционально

#define LENGTH_PATH 65
#define NUMBER_CHILDS 16
#define NUMBER_START_JOBS 16
#define LENGTH_BARRIER_NAME 10
#define NUM_BARRIERS 3
#define ALL_PATHES "timer.out"

typedef struct {
    int id;
    int child_ids[NUMBER_CHILDS];
    char path[LENGTH_PATH];
    int num_completed_parents;
    int num_parents;
    bool barrier;
    int barrier_name;
    int num_completed_barriers;
    int num_barriers;
} job;

typedef struct {
    size_t size;
    job *buf;
} vector_yaml;

bool vyaml_init(vector_yaml *v, size_t size);
void vyaml_destroy(vector_yaml *v);
size_t vyaml_get_size(vector_yaml *v);
bool vyaml_set_size(vector_yaml *v, size_t new_size);
job vyaml_get(vector_yaml *v, size_t i);
void vyaml_set(vector_yaml *v, size_t i, job new_val);

#endif
