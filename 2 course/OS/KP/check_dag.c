#include "check_dag.h"

int count_childs(int child_ids[]) {
    
    int count = 0;
    for (int i = 0; i < NUMBER_CHILDS; i++) {
        if (child_ids[i] >= 0) {
            count++;
        }
    }
    
    return count;
    
}

bool cycle_found = false;

void dfs_check_cycle(int start, int color[], vector_yaml *v) {
    
    color[start] = 1;
    
    int child_ids[NUMBER_CHILDS];
    for (int i = 0; i < NUMBER_CHILDS; i++) {
        child_ids[i] = v -> buf[start].child_ids[i];
    }
    int cnt_childs = count_childs(child_ids);   
    
    for (int i = 0; i < cnt_childs; i++) {
        if (child_ids[i] > vyaml_get_size(v)) {
            continue;
        }
        if (color[child_ids[i] - 1] == 0) {
            dfs_check_cycle(child_ids[i] - 1, color, v);
        } else if (color[child_ids[i] - 1] == 1) {
            cycle_found = true;
        }
    }
    
    color[start] = 2;
    
}

bool check_cycle(vector_yaml *v) {
    
    int size = vyaml_get_size(v);
    int color[size];
    for (int i = 0; i < size; i++) {
        color[i] = 0;
    }
    
    for (int i = 1; i < size + 1; i++) {
        if (color[i - 1] == 0) {
            dfs_check_cycle(i - 1, color, v);
        }
    }
    
    return cycle_found;
    
}

static int count_vertex(int vertex_queue[], int n) {
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (vertex_queue[i] >= 0) {
            count++;
        }
    }
    
    return count;
    
}

static int max_vertex_num(vector_yaml *v) {
    
    int max = -1;
    int id = 0;
    int child_id = 0;
    for (int i = 0; i < vyaml_get_size(v); i++) {
        id = v -> buf[i].id;
        if (id > max)
            max = id;
        for (int j = 0; j < NUMBER_CHILDS; j++) {
            if (v -> buf[i].child_ids[j] >= 0) {
                child_id = v -> buf[i].child_ids[j];
                if (child_id > max)
                    max = child_id;
            }
        }
    }
    
    return max;
    
}

static void get_all_edges_undirected_graph(vector_yaml *v, int start, int vertex_queue[]) {
    
    int i_vertex_queue = 0;
    
    for (int i = 0; i < NUMBER_CHILDS; i++) {
        if (start + 1 > vyaml_get_size(v))
            break;
        if (v -> buf[start].child_ids[i] >= 0) {
            vertex_queue[i_vertex_queue] = v -> buf[start].child_ids[i];
            i_vertex_queue++;
        }
    }
    
    for (int i = 0; i < vyaml_get_size(v); i++) {
        for (int j = 0; j < NUMBER_CHILDS; j++) {
            if (v -> buf[i].child_ids[j] == (start + 1)) {
                vertex_queue[i_vertex_queue] = v -> buf[i].id;
                i_vertex_queue++;
            }
        }
    }
    
}

void dfs_check_num_connectivity_components(int start, bool visited[], vector_yaml *v) {
    
    visited[start] = true;
    
    int n = max_vertex_num(v);
    int size_vertex_queue = (n * (n - 1)) / 2;
    int vertex_queue[size_vertex_queue];
    for (int i = 0; i < size_vertex_queue; i++) {
        vertex_queue[i] = -1;
    }
    get_all_edges_undirected_graph(v, start, vertex_queue);
    int cnt_vertex = count_vertex(vertex_queue, size_vertex_queue);
    
    for (int i = 0; i < cnt_vertex; i++) {
        if (!visited[vertex_queue[i] - 1]) {
            dfs_check_num_connectivity_components(vertex_queue[i] - 1, visited, v);
        }
    }
    
}

int check_num_connectivity_components(vector_yaml *v) {
    
    int size = max_vertex_num(v);
    bool visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }
    
    int num_comp = 0;
    for (int i = 1; i < size + 1; i++) {
        if (!visited[i - 1]) {
            num_comp++;
            dfs_check_num_connectivity_components(i - 1, visited, v);
        }
    }
    
    return num_comp;
    
}

void dfs_get_list_start_jobs(int start, bool visited[], vector_yaml *v) {
    
    visited[start] = true;
    
    int child_ids[NUMBER_CHILDS];
    for (int i = 0; i < NUMBER_CHILDS; i++) {
        child_ids[i] = v -> buf[start].child_ids[i];
    }
    int cnt_childs = count_childs(child_ids);
    
    for (int i = 0; i < cnt_childs; i++) {
        if (child_ids[i] - 1 > vyaml_get_size(v)) {
            return;
        }
        if (!visited[child_ids[i] - 1]) {
            dfs_get_list_start_jobs(child_ids[i] - 1, visited, v);
        }
    }
    
}

void get_list_start_jobs(vector_yaml *v, int list[]) {
    
    int size = vyaml_get_size(v);
    bool visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }

    int i_list = 0;
    for (int i = 1; i < size + 1; i++) {
        if (!visited[i - 1]) {
            list[i_list] = v -> buf[i - 1].id;
            i_list++;
            dfs_get_list_start_jobs(i - 1, visited, v);
        }
    }
        
}

void count_parents(vector_yaml *v) {
    
    int size = vyaml_get_size(v);
    int cur_id;
    int count_parents = 0;
    for (int i = 0; i < size; i++) {
        cur_id = v -> buf[i].id;
        count_parents = 0;
        for (int j = 0; j < size; j++) {
            int child_ids[NUMBER_CHILDS];
            for (int i = 0; i < NUMBER_CHILDS; i++) {
                child_ids[i] = v -> buf[j].child_ids[i];
            }
            int cnt_childs = count_childs(child_ids);
            for (int k = 0; k < cnt_childs; k++) {
                if (child_ids[k] == cur_id) {
                    count_parents++;
                }
            }
        }
        v -> buf[i].num_parents = count_parents;
    }
    
}

static int count_jobs_parents(vector_yaml *v, int id) {
    
    int res = 0;
    int size = vyaml_get_size(v);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < NUMBER_CHILDS; j++) {
            if (v -> buf[i].child_ids[j] == -1) {
                break;
            }
            if (id == v -> buf[i].child_ids[j]) {
                res++;
            }
        }
    }

    return res;
    
}

void count_barriers(vector_yaml *v) {

    int size = vyaml_get_size(v);
    int barrier_count[NUM_BARRIERS] = {0};
    int num_parents = 0;
    for (int i = 0; i < size; i++) {
        if (v -> buf[i].barrier) {
            num_parents = count_jobs_parents(v, v -> buf[i].id);
            barrier_count[v -> buf[i].barrier_name - 1] += num_parents;
        }
    }
    
    for (int i = 0; i < size; i++) {
        if (v -> buf[i].barrier) {
            v -> buf[i].num_barriers = barrier_count[v -> buf[i].barrier_name - 1];
        }
    }
    
}
