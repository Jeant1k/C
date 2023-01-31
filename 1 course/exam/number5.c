#include <stdio.h>

int main() {
    printf("Введите первое число и второе через пробел:\n");
    int space = 0;
    int first_dig = 0;
    int second_dig = 0;
    int c = 0;
    while ((c = getchar()) != '\n') {
        if (space == 0 && c == 124) {
            first_dig++;
        } else if (space == 0 && c == 32) {
            space = 1;
        } else if (space == 1 && c == 124) {
            second_dig++;
        }
    }
    printf("Ответ: ");
    int res = (first_dig - 1) / (second_dig - 1);
    for (int i = 0; i <= res; i++) {
        printf("|");
    }
}
