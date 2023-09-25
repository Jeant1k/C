#include <stdio.h>
#include <time.h>
#include "lib.h"

void help() {
    printf("Приветствую в программе, которая умеет находить количество простых чисел и переводить число из десятичной системы счисления в двоичную. Введите:\n\n\t1 A B - посчитать количество простых чисел от числа A до числа B включительно\n\t2 n - перевести число n в двоичную систему счисления\n\nдля того, чтобы воспользоваться программой.\n\n");
}

int main(void) {
    int arg;
    help();
    while(scanf("%d ", &arg) != EOF) {
        if (arg == 1) {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("Между числами %d и %d находится %d простых чисел.\n\n", a, b, prime_count(a, b));
        } else if (arg == 2) {
            long n;
            scanf("%ld", &n);
            printf("Число %ld в двоичной системе счисления: %s\n\n", n, translate(n));
        } else {
            help();
            return -1;
        }
    }
}
