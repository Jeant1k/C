#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include "svint.h"
// #include "sarr.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"

typedef enum {
    STATE_NOT_A_DIGIT, // 0
    STATE_FIRST_DIGIT, // 1
    STATE_NON_DECREASING_SEQUENCE, // 2
    STATE_ADDITION_TO_MINRUN_1, // 4
    STATE_DESCENT_SEQUENCE, // 3
    STATE_ADDITION_TO_MINRUN_2 // 5
} state;

void print_arr_with_INT_MAX(svector_int arr) {
    for (int i = 0; i < svint_get_size(&arr); i++) {
        int el = svint_get(&arr, i);
        if (el == INT_MAX) {
            printf("%s%d%s ", RED, el, RESET);
        } else {
            printf("%d ", el);
        }
    }
    printf("\n\n");
}

int get_minrun(int n) {
    // Функция, ищущая minrun
    int r = 0;
    while (n >= 64) {
        r = r | (n & 1);
        n = n >> 1;
    }
    return n + r;
}

svector_int reverse_vec(svector_int arr) {
    // Функция реверса вектора
    int tmp;
    int size = svint_get_size(&arr);
    for (int i = 0; i < size / 2; i++) {
        tmp = svint_get(&arr, i);
        svint_set(&arr, i, svint_get(&arr, size - i - 1));
        svint_set(&arr, size - 1 - i, tmp);
    }
    return arr;
}

svector_int merger(svector_int arr1, svector_int arr2) {
    // Функция слияния двух отсортированных массивов
    svector_int resarr;
    svint_init(&resarr);
    int n = 0, m = 0;
    if (svint_is_empty(&arr1)) {
        return arr2;
    }
    if (svint_is_empty(&arr2)) {
        return arr1;
    }
    while ((n < svint_get_size(&arr1)) && (m < svint_get_size(&arr2))) {
        if (svint_get(&arr1, n) <= svint_get(&arr2, m)) {
            svint_push_back(&resarr, svint_get(&arr1, n));
            n++;
        } else {
            svint_push_back(&resarr, svint_get(&arr2, m));
            m++;
        }
    }
    while (n < svint_get_size(&arr1)) {
        svint_push_back(&resarr, svint_get(&arr1, n));
        n++;
    }
    while (m < svint_get_size(&arr2)) {
        svint_push_back(&resarr, svint_get(&arr2, m));
        m++;
    }
    return resarr;
}

svector_int spec_merger(svector_int arr) {
    // Функция, сливающая подмассивы в один
    // print_arr_with_INT_MAX(arr);
    svector_int resarr;
    svint_init(&resarr);
    svector_int subarr;
    svint_init(&subarr);
    int k = 0;
    for (int i = 0; i < svint_get_size(&arr); i++) {
        int el = svint_get(&arr, i);
        if (el != INT_MAX) {
            svint_push_back(&subarr, svint_get(&arr, i));
        } else {
            resarr = merger(subarr, resarr);
            svint_init(&subarr);
        }
    }
    return resarr;
}

svector_int insertion_sort(svector_int arr) {
    // Функция сортировки встваками
    for (int i = 1; i < svint_get_size(&arr); i++) {
        for (int j = i; j > 0 && svint_get(&arr, j - 1) > svint_get(&arr, j); j--) {
            int tmp = svint_get(&arr, j - 1);
            svint_set(&arr, j - 1, svint_get(&arr, j));
            svint_set(&arr, j, tmp);
        }
    }
    return arr;
}

svector_int arr_rand_dig() {
    // Функция, заполняющая массив рандомными числами
    int i, n;
    printf("Введите размер вектора: ");
    scanf("%d", &n);
    srand(time(0));
    svector_int v;
    svint_init(&v);
    svint_set_size(&v, n);
    // printf("\nСгенерированный вектор:\n");
    for (i = 0; i < n; i++) {
        svint_set(&v, i, rand() % n);
        // printf("%d ", svint_get(&v, i));
    }
    // putchar('\n');
    return v;
}

svector_int split_subarr_sort(svector_int arr, int minrun) {
    // Функция, разбивающая на подмассивы и их сортирующая
    svector_int resarr;
    svint_init(&resarr);
    svector_int subarr;
    svint_init(&subarr);
    state s = STATE_NOT_A_DIGIT;
    int l = 0;
    for (int i = 0; i < svint_get_size(&arr); i++) {
        if (s == STATE_NOT_A_DIGIT) {
            svint_push_back(&subarr, svint_get(&arr, i));
            l++;
            s = STATE_FIRST_DIGIT;
        } else if (s == STATE_FIRST_DIGIT && svint_get(&arr, i - 1) <= svint_get(&arr, i)) {
            svint_push_back(&subarr, svint_get(&arr, i));
            l++;
            s = STATE_NON_DECREASING_SEQUENCE;
        } else if (s == STATE_FIRST_DIGIT && svint_get(&arr, i - 1) > svint_get(&arr, i)) {
            svint_push_back(&subarr, svint_get(&arr, i));
            l++;
            s = STATE_DESCENT_SEQUENCE;
        } else if (s == STATE_NON_DECREASING_SEQUENCE && svint_get(&arr, i - 1) <= svint_get(&arr, i)) {
            svint_push_back(&subarr, svint_get(&arr, i));
            l++;
        } else if (s == STATE_NON_DECREASING_SEQUENCE && svint_get(&arr, i - 1) > svint_get(&arr, i) && l >= minrun) {
            subarr = insertion_sort(subarr);
            while (!svint_is_empty(&subarr)) {
                svint_push_back(&resarr, svint_pop_front(&subarr));
            }
            svint_push_back(&resarr, INT_MAX);
            l = 1;
            svint_push_back(&subarr, svint_get(&arr, i));
            s = STATE_FIRST_DIGIT;
        } else if (s == STATE_NON_DECREASING_SEQUENCE && svint_get(&arr, i - 1) > svint_get(&arr, i) && l < minrun) {
            svint_push_back(&subarr, svint_get(&arr, i));
            l++;
            s = STATE_ADDITION_TO_MINRUN_1;
        } else if (s == STATE_ADDITION_TO_MINRUN_1 && l < minrun) {
            svint_push_back(&subarr, svint_get(&arr, i));
            l++;
        } else if (s == STATE_ADDITION_TO_MINRUN_1 && l >= minrun) {
            subarr = insertion_sort(subarr);
            while (!svint_is_empty(&subarr)) {
                svint_push_back(&resarr, svint_pop_front(&subarr));
            }
            svint_push_back(&resarr, INT_MAX);
            l = 1;
            svint_push_back(&subarr, svint_get(&arr, i));
            s = STATE_FIRST_DIGIT;
        } else if (s == STATE_DESCENT_SEQUENCE && svint_get(&arr, i - 1) > svint_get(&arr, i)) {
            svint_push_back(&subarr, svint_get(&arr, i));
            l++;
        } else if (s == STATE_DESCENT_SEQUENCE && svint_get(&arr, i - 1) <= svint_get(&arr, i) && l >= minrun) {
            subarr = reverse_vec(subarr);
            subarr = insertion_sort(subarr);
            while (!svint_is_empty(&subarr)) {
                svint_push_back(&resarr, svint_pop_front(&subarr));
            }
            svint_push_back(&resarr, INT_MAX);
            l = 1;
            svint_push_back(&subarr, svint_get(&arr, i));
            s = STATE_FIRST_DIGIT;
        } else if (s == STATE_DESCENT_SEQUENCE && svint_get(&arr, i - 1) <= svint_get(&arr, i) && l < minrun) {
            subarr = reverse_vec(subarr);
            subarr = insertion_sort(subarr);
            svint_push_back(&subarr, svint_get(&arr, i));
            l++;
            s = STATE_ADDITION_TO_MINRUN_2;
        } else if (s == STATE_ADDITION_TO_MINRUN_2 && l < minrun) {
            svint_push_back(&subarr, svint_get(&arr, i));
            l++;
        } else if (s == STATE_ADDITION_TO_MINRUN_2 && l >= minrun) {
            subarr = insertion_sort(subarr);
            while (!svint_is_empty(&subarr)) {
                svint_push_back(&resarr, svint_pop_front(&subarr));
            }
            svint_push_back(&resarr, INT_MAX);
            l = 1;
            svint_push_back(&subarr, svint_get(&arr, i));
            s = STATE_FIRST_DIGIT;
        }
    }
    subarr = insertion_sort(subarr);
    while (!svint_is_empty(&subarr)) {
        svint_push_back(&resarr, svint_pop_front(&subarr));
    }
    svint_push_back(&resarr, INT_MAX);
    return resarr;
}

svector_int return_part(svector_int arr, int part) {
    int count = 0;
    for (int i = 0; i < svint_get_size(&arr); i++) {
        if (svint_get(&arr, i) == INT_MAX) {
            count++;
        }
    }

    int first_idx;
    int second_idx;
    if (count >= 3) {
        if (part == 0) {
            first_idx = 0;
            second_idx = count / 3;
        } else if (part == 1) {
            first_idx = count / 3 + 1;
            second_idx = count * 2 / 3;
        } else {
            first_idx = count * 2 / 3 + 1;
            second_idx = count;
        }
    }
    
    // else {
    //     // Дописать эту ветку
    // }
    int count_INT_MAX = 0;
    svector_int res_arr;
    svint_init(&res_arr);
    // printf("Левая граница - %d, правая - %d\n", first_idx, second_idx);
    for (int i = 0; i < svint_get_size(&arr); i++) {
        if (first_idx <= count_INT_MAX && count_INT_MAX <= second_idx) {
            svint_push_back(&res_arr, svint_get(&arr, i));
        }
        if (svint_get(&arr, i) == INT_MAX) {
            count_INT_MAX++;
        }
    }
    return res_arr;
}

void* thread_merger(void* arr) {
    // printf("Я зашел в функцию слияния\n");
    svector_int *data = (svector_int*)arr;
    svector_int resarr;
    svint_init(&resarr);
    svector_int subarr;
    svint_init(&subarr);
    int k = 0;
    for (int i = 0; i < svint_get_size(arr); i++) {
        int el = svint_get(arr, i);
        if (el != INT_MAX) {
            svint_push_back(&subarr, svint_get(arr, i));
        } else {
            resarr = merger(subarr, resarr);
            svint_init(&subarr);
        }
    }
    *data = resarr;
	return NULL;
}

int main(void) {
    svector_int arr = arr_rand_dig();
    svector_int res_arr_1;
    svector_int res_arr_2;
    printf("\n");
    int minrun = get_minrun(svint_get_size(&arr));
    printf("minrun = %d\n\n", minrun);
    double time_0 = clock();
    arr = split_subarr_sort(arr, minrun);
    double time_1 = clock();
    printf("split_subarr_sort работал %lf секунд\n\n", (time_1 - time_0) / CLOCKS_PER_SEC);
    time_0 = clock();
    res_arr_1 = spec_merger(arr);
    time_1 = clock();
    printf("spec_merger работал %lf секунд\n", (time_1 - time_0) / CLOCKS_PER_SEC);

    // printf("\nОтсортированный вектор:\n");
    // print_arr_with_INT_MAX(res_arr_1);

    time_0 = clock();
    
    int thread_count = 3;
    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));

    svector_int my_parts[thread_count];
    for (int i = 0; i < thread_count; i++) {
        my_parts[i] = return_part(arr, i);
    }

    // for (int i = 0; i < sizeof(my_parts) / sizeof(svector_int); i++) {
    //     print_arr_with_INT_MAX(my_parts[i]);
    // }

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], NULL, thread_merger, &my_parts[i]);
    }

    for(int i = 0; i < thread_count; i++)
		pthread_join(threads[i], NULL);

    // for (int i = 0; i < sizeof(my_parts) / sizeof(svector_int); i++) {
    //     print_arr_with_INT_MAX(my_parts[i]);
    // }

    svector_int arr1;
    svint_init(&arr1);
    for (int i = 0; i < sizeof(my_parts) / sizeof(svector_int); i++) {
        for (int j = 0; j < svint_get_size(&my_parts[i]); j++) {
            svint_push_back(&arr1, svint_get(&my_parts[i], j));
        }
        svint_push_back(&arr1, INT_MAX);
    }

    // print_arr_with_INT_MAX(arr1);

    arr1 = spec_merger(arr1);

    time_1 = clock();

    printf("\nthread_merger работал %lf секунд\n", (time_1 - time_0) / CLOCKS_PER_SEC);
    
    // printf("Отсортированный вектор:\n");
    // print_arr_with_INT_MAX(arr1);
    
    return 0;
}
