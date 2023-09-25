// Гарантируется, что граф описан вершинами, с натуральными номерами в строго возрастающей последовательности без пропусков чисел (например, описание графа: вершина 1: ..., вершина 3: ..., вершина 4: ... - не подойдет). Все стартовые джобы должны быть в начале без пропусков. Имена барьеров должны представлять из себя натуральные числа без пропусков.

#ifndef _CHECK_DAG_H_
#define _CHECK_DAG_H_

#include <stdbool.h>
#include <stdio.h>
#include "vector_yaml.h"

void dfs_check_cycle(int start, int color[], vector_yaml *v);
bool check_cycle(vector_yaml *v);
void dfs_check_num_connectivity_components(int start, bool visited[], vector_yaml *v);
int check_num_connectivity_components(vector_yaml *v);
void get_list_start_jobs(vector_yaml *v, int list[]);
int count_childs(int child_ids[]);
void count_parents(vector_yaml *v);
void count_barriers(vector_yaml *v);

#endif
