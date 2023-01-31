#include <stdio.h>

int main(void) {
    int c = 0;
    int s = 0;
    int a = -1, b = -1;
    while ((c = getchar()) != '\n') {
        if (s == 0 && c == '|') {
            a ++;
        } else if (s == 0 && c == ' ') {
            s = 1;
        } else if (s == 1 && c == '|') {
            b ++;
        }
    }
    int res = a / b;
    for (int i = 0; i <= res; i++) {
        printf("|");
    }
    printf("\n");
}
