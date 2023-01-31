#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"
#include <limits.h>

#define MAX_LEN_FILENAME 255
#define MIN_LEN_FILENAME 16

typedef struct {
    char *name;
    int size;
} filename;

filename get_filename() {
    filename f;
    printf("Введите название файла: ");
    int pool_size = MIN_LEN_FILENAME;
    f.name = malloc(sizeof(char) * MIN_LEN_FILENAME);
    char c = getchar();
    int name_size = 0;
    while (c != '\n') {
        if (name_size < pool_size) {
            f.name[name_size] = c;
            name_size++;
        } else {
            if (name_size < MAX_LEN_FILENAME) {
                pool_size *= 2;
                f.name = realloc(f.name, sizeof(char) * pool_size);
                f.name[name_size] = c;
                name_size++;
            } else {
                printf("Имена файлов длинной больше 255 символов в Ubuntu не поддерживаются!\n");
                _Exit(0);
            }
        }
        c = getchar();
    }
    f.name[name_size] = '\0';
    f.size = name_size;
    return f;
}

int main(void) {
    int fd[2];
    // fd[0] - read
    // fd[1] - write
    if (pipe(fd) == -1) {
        printf("Произошла ошибка при открытии pipe\n");
        return 1;
    }
    int id = fork();
    if (id == -1) {
        printf("Произошла ошибка с fork\n");
        return 2;
    }
    if (id == 0) {
        dup2(fd[0], fileno(stdin));
        execl("./Child.out", "./Child.out", NULL);
    } else {
        close(fd[0]);
        filename filename = get_filename();
        int namesize = filename.size;
        if (write(fd[1], &namesize, sizeof(int)) == -1) {
            printf("Произошла ошибка при письме в pipe\n");
            return 3;
        }
        for (int i = 0; i < namesize; i++) {
            if (write(fd[1], &filename.name[i], sizeof(char)) == -1) {
                printf("Произошла ошибка при писмье в pipe\n");
                return 4;
            }
        }
        queue_dbl q;
        qdbl_init(&q);
        char dig = 0;
        printf("Введите массив чисел: ");
        q = parser();
        int size = qdbl_get_size(&q);
        if (write(fd[1], &size, sizeof(int)) == -1) {
            printf("Произошла ошибка при письме в pipe\n");
            return 5;
        }
        while (qdbl_get_size(&q) > 0) {
            double el = qdbl_pop_front(&q);
            if (write(fd[1], &el, sizeof(double)) == -1) {
                printf("Произошла ошибка при письме в pipe\n");
                return 6;
            }
        }
        wait(NULL);
        close(fd[1]);
    }
}
