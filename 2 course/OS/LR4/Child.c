#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "qdbl.h"
#include <float.h>
#include <fcntl.h>
#include <math.h>
#include <semaphore.h>
#include <signal.h>


char *n = NULL;

int main(int argc, char *argv[]) {

    // raise(SIGINT);
    sem_t *sem;
    if ((sem = sem_open("/my_name", O_CREAT, 0777, 0)) == SEM_FAILED ) {
        perror("sem_open");
        return 1;
    }

    if (sem_wait(sem) < 0 )
        perror("sem_wait");
    
    if (sem_close(sem) < 0 )
        perror("sem_close");

    
    FILE *my_file = fopen(argv[1], "w");

    int fd_for_input = open("back1.txt", O_RDWR | O_CREAT, 0777);
    struct stat sb;
	if (fstat(fd_for_input, &sb) ==  -1) {
		perror ("Не удалось узнать длину файла (из дочернего файла)\n");
	}
	char *file_mem = mmap(NULL, 5000 * sizeof(char), PROT_WRITE | PROT_READ, MAP_SHARED, fd_for_input, 0);
    if (file_mem == NULL) {
		perror ("Ошибка mmap\n");
	}
    n = file_mem;
    
    // int c = 0;
    // for (int i = 0; i < 50 * sizeof(int); i++) {
    //     c = n[i];
    //     fprintf(my_file, "%c", c);
    // }
    
    // for (int i = 0; i < sb.st_size; i++) {
    //     printf("%c", n[i]);
    // }    
    
    queue_dbl q;
    qdbl_init(&q);
    double el = 0;
    double last_el = 0;
    int flag_dot = 0;
    int k = 1;
    for (int i = 0; i < sb.st_size; i++) {
        if (n[i] != ' ') {
            if (n[i] != '.') {
                if (flag_dot == 0) {
                    el = el * 10 + (n[i] - 48);
                } else {
                    el = el + (double)(n[i] - 48) / (int)pow(10, k);
                    k++;
                }
            } else {
                flag_dot = 1;
            }
        } else {
            qdbl_push_back(&q, el);
            last_el = el;
            el = 0;
            flag_dot = 0;
            k = 1;
        }
    }

    
    if (last_el != DBL_MAX) {
        qdbl_push_back(&q, DBL_MAX);
    }

    // Сделать проверку на последний элемент. Если он макс дабл, то ничего, если нет, то добавить в конец макс дабл
    // int size = qdbl_get_size(&q);
    // for (int i = 0; i < size; i++) {
    //     printf("%lf\n", qdbl_pop_front(&q));
    // }
    
    double res;
    int first_dig = 1;
    int size = qdbl_get_size(&q);
    printf("Размер очереди равен %d\n", size);
    for (int i = 0; i < size; i++) {
        el = qdbl_pop_front(&q);
        printf("Попнули элемент %lf\n", el);
        if (el == DBL_MAX) {
            fprintf(my_file, "%lf\n", res);
            printf("Записали элемент %lf\n", res);
            first_dig = 1;
        } else {
            if (first_dig == 1) {
                res = el;
                first_dig = 0;
            } else {
                if (el == 0) {
                    _Exit(0);
                }
                res /= el;
                printf("Частичный результат равен %lf\n", res);
            }
        }
    }
}
