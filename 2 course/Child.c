#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "qdbl.h"
#include <float.h>

int main() {
    
    int namesize;
    if (read(fileno(stdin), &namesize, sizeof(int)) == -1) {
        printf("Произошла ошибка при чтении из pipe\n");
        return 9;
    }
    char filename[namesize];
    for (int i = 0; i < namesize; i++) {
        if (read(fileno(stdin), &filename[i], sizeof(char)) == -1) {
            printf("Произошла ошибка при чтении из pipe\n");
            return 10;
        }
    }

    FILE *file = fopen(filename, "a+");

    int size;
    if (read(fileno(stdin), &size, sizeof(int)) == -1) {
        printf("Произошла ошибка при чтении из pipe\n");
        return 11;
    }
    
    queue_dbl q;
    qdbl_init(&q);
    double el;
    for (int i = 0; i < size; i++) {
        if (read(fileno(stdin), &el, sizeof(double)) == -1) {
            printf("Произошла ошибка при чтении из pipe\n");
            return 12;
        }
        qdbl_push_back(&q, el);
    }

    double res;
    int first_dig = 1;
    for (int i = 0; i < size; i++) {
        el = qdbl_pop_front(&q);
        if (el == DBL_MAX) {
            fprintf(file, "%lf\n", res);
            printf("%lf\n", res);
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
            }
        }
    }
    // Почему-то fwrite не хотел корректно работать. Спросить почему.
}
