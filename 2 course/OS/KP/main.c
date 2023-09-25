#define _DEFAULT_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include "vector_yaml.h"
#include "parser_yaml.h"
#include "check_dag.h"

#define RESET "\033[0m"
#define UNDERLINED_RED "\033[4;31m"
#define RED "\033[0;31m"
#define UNDERLINED_YELLOW "\033[4;33m"
#define YELLOW "\033[0;33m"

#define MAX_LENGTH_PID 4

typedef struct {
    vector_yaml *v;
    int cur_id;
} pthread_struct;

static void print_vector(vector_yaml *v, int size_DAG) {
    
    for (int i = 0; i < size_DAG; i++) {
        printf("%d ", v -> buf[i].id);
        for (int j = 0; j < NUMBER_CHILDS; j++) {
            if (v -> buf[i].child_ids[j] == -1) {
                break;
            }
            printf("%d ", v -> buf[i].child_ids[j]);
        }
        for (int j = 0; j < LENGTH_PATH; j++) {
            if (v -> buf[i].path[j] == '\0') {
                break;
            }
            printf("%c", v -> buf[i].path[j]);
        }
        printf(" ");
        printf("%d ", v -> buf[i].num_completed_parents);
        printf("%d ", v -> buf[i].num_parents);
        if (v -> buf[i].barrier) {
            printf("Имя барьера: ");
            printf("%d ", v -> buf[i].barrier_name);
            printf("%d ", v -> buf[i].num_completed_barriers);
            printf("%d ", v -> buf[i].num_barriers);
        }
        printf("\n");
    }
    
}

static int len_list_start_job(int list[]) {
    
    int count = 0;
    for (int i = 0; i < NUMBER_START_JOBS; i++) {
        if (list[i] >= 0) {
            count++;
        }
    }
    
    return count;
    
}

static bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

static void* dfs_start_job(void *pthread_data) {
    
    pthread_struct *data = (pthread_struct*)pthread_data;

    bool return_flag = false;
    bool last_barrier_job = false;
    
    if (data -> v -> buf[data -> cur_id - 1].num_completed_parents + 1 < data -> v -> buf[data -> cur_id - 1].num_parents) {
        data -> v -> buf[data -> cur_id - 1].num_completed_parents++;
        printf("%sid = %d. Ждем остальных родителей. %s%d/%d%s.%s\n", YELLOW, data -> cur_id, UNDERLINED_YELLOW, data -> v -> buf[data -> cur_id - 1].num_completed_parents, data -> v -> buf[data -> cur_id - 1].num_parents, YELLOW, RESET);
        return_flag = true;
    }

    if (data -> v -> buf[data -> cur_id - 1].barrier) {
        if (data -> v -> buf[data -> cur_id - 1].num_completed_barriers + 1 < data -> v -> buf[data -> cur_id - 1].num_barriers) {
            for (int i = 0; i < vyaml_get_size(data -> v); i++) {
                if (data -> v -> buf[data -> cur_id - 1].barrier && data -> v -> buf[data -> cur_id - 1].barrier_name == data -> v -> buf[i].barrier_name) {
                    data -> v -> buf[i].num_completed_barriers++;
                }
            }
            printf("%sid = %d. Сработал барьер. %s%d/%d%s.%s\n", RED, data -> cur_id, UNDERLINED_RED, data -> v -> buf[data -> cur_id - 1].num_completed_barriers, data -> v -> buf[data -> cur_id - 1].num_barriers, RED, RESET);
            return_flag = true;
        } else if (data -> v -> buf[data -> cur_id - 1].num_completed_barriers + 1 == data -> v -> buf[data -> cur_id - 1].num_barriers) {
            for (int i = 0; i < vyaml_get_size(data -> v); i++) {
                if (data -> v -> buf[data -> cur_id - 1].barrier && data -> v -> buf[data -> cur_id - 1].barrier_name == data -> v -> buf[i].barrier_name) {
                    data -> v -> buf[i].num_completed_barriers++;
                }
            }
            last_barrier_job = true;
        }
    }

    if (return_flag)
        return NULL;
    
    int id = fork();
    
    if (id == -1) {
        printf("Произошла ошибка с fork\n");
        exit(1);
    }
    
    if (id == 0) {
        
        int id_job = data -> v -> buf[data -> cur_id - 1].id;
        char id_job_str[10];
        sprintf(id_job_str, "%d", id_job);
        if (execl(data -> v -> buf[(data -> cur_id) - 1].path, data -> v -> buf[(data -> cur_id) - 1].path, id_job_str, NULL) == -1) {
            printf("Произошла ошибка с exec. Код ошибки = %d.\n", errno);
            exit(1);
        }
        
    } else {
        
        int status;
        printf("Запустил джобу с id = %d.\n", data -> v -> buf[data -> cur_id - 1].id);
        wait(&status);
        
        if (WIFSIGNALED(status)) {
            printf("%sДжоба с id = %d завершилась с ошибкой.%s\n", RED, data -> cur_id, RESET);          
            FILE *file_pid;
            if ((file_pid = popen("pidof timer.out", "r")) == NULL) {  // Сделать по нормальному
                printf("popen завершилась с ошибкой.\n");
            }
            int size = (MAX_LENGTH_PID + 1) * NUMBER_CHILDS * NUMBER_CHILDS;
            char line[size];
            while (true) {
                if (fgets(line, size, file_pid) == NULL) {
                    break;
                }
            }
            char pid_str[MAX_LENGTH_PID];
            int i_pid_str = 0;
            for (int i = 0; i < size; i++) {
                if (!is_digit(line[i]) && !is_digit(line[i - 1])) {
                    break;
                }
                if (!is_digit(line[i])) {
                    int pid = strtol(pid_str, (char **)NULL, 10);
                    printf("Убил сына с PID = %d\n", pid);
                    kill(pid, SIGTERM);
                    i_pid_str = 0;
                    continue;
                }
                pid_str[i_pid_str] = line[i];
                i_pid_str++;
            }
            pclose(file_pid);
            printf("\n");
            exit(1);
        }
        
        if (WIFEXITED(status)) {
            int cnt_childs = count_childs(data -> v -> buf[data -> cur_id - 1].child_ids);
            if (cnt_childs == 0) {
                return NULL;
            }
            int cnt_barriers = 0;
            if (last_barrier_job) {
                cnt_barriers = 0;
                for (int i = 0; i < vyaml_get_size(data -> v); i++) {
                    if (data -> v -> buf[data -> cur_id - 1].barrier && data -> v -> buf[data -> cur_id - 1].barrier_name == data -> v -> buf[i].barrier_name) {
                        cnt_barriers++;
                    }
                }
                cnt_barriers--;
                cnt_childs += cnt_barriers;
            }
            int childs[cnt_childs];
            for (int i = 0; i < cnt_childs; i++) {
                childs[i] = data -> v -> buf[data -> cur_id - 1].child_ids[i];
            }
            int i_childs = cnt_childs - cnt_barriers;
            if (last_barrier_job) {
                for (int i = 0; i < vyaml_get_size(data -> v); i++) {
                    if (data -> v -> buf[i].barrier && data -> v -> buf[i].barrier_name == data -> v -> buf[data -> cur_id - 1].barrier_name && data -> v -> buf[i].id != data -> v -> buf[data -> cur_id - 1].id) {
                        childs[i_childs] = data -> v -> buf[i].id;
                        i_childs++;
                    }
                }
            }
            int thread_count = cnt_childs;
            pthread_t *threads = malloc(thread_count * sizeof(pthread_t));
            pthread_struct cur_data[thread_count];
            for (int i = 0; i < thread_count; i++) {
                cur_data[i].cur_id = childs[i];
                cur_data[i].v = data -> v;
            }
            for (int i = 0; i < thread_count; i++) {
                pthread_create(&threads[i], NULL, dfs_start_job, &cur_data[i]);
            }
            for (int i = 0; i < thread_count; i++) {
                pthread_join(threads[i], NULL);
            }
        }
        
    }
    
    return NULL;
    
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Введено неверное количество аргументов программе.\n");
        return 1;
    }

    int len_file_name = strlen(argv[1]);
    if (len_file_name > 255) {
        printf("Длина файла задана неверно!\n");
		return 2;
    }

    // print_file(argv[1]);
    
    int size_dag = get_size_dag(argv[1]);
    
    vector_yaml v;
    if (!vyaml_init(&v, size_dag)) {
        printf("Не удалось создать вектор.\n");
        return 3;
    }
    
    if (!parsing_file_writing_to_vector(&v, argv[1])) {
        printf("Не удалось считать данные из файла и записать в вектор.\n");
        return 4;
    }

    if (check_num_connectivity_components(&v) != 1) {
        printf("Граф имеет более одной компоненты связности.\n");
        return 6;
    }
    printf("\nГраф имеет одну компоненту связности.\n\n");

    
    if (check_cycle(&v)) {
        printf("Граф имеет циклы.\n");
        return 7;
    }
    printf("Граф не имеет циклы.\n\n");

    count_parents(&v);

    count_barriers(&v);

    print_vector(&v, size_dag);
    printf("\n");
    
    int list_start_jobs[NUMBER_START_JOBS];
    for (int i = 0; i < NUMBER_START_JOBS; i++) {
        list_start_jobs[i] = -1;
    }
    get_list_start_jobs(&v, list_start_jobs);
    int num_start_jobs = len_list_start_job(list_start_jobs);
    
    int thread_count = num_start_jobs;
    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));

    pthread_struct data[thread_count];
    for (int i = 0; i < thread_count; i++) {
        data[i].cur_id = i + 1;
        data[i].v = &v;
    }
    
    for (int i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], NULL, dfs_start_job, &data[i]);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n");

    vyaml_destroy(&v);
    free(threads);
    
    return 0;
    
}
