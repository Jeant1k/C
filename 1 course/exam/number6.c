#include <stdio.h>

int main(void) {
    int k = 0;
    int iter = 1;

    for (int i = 2; i <= 100000; i++) {
        k = 0;
        for (int j = 1; j <= i; j++) {
            if (i % j == 0) {
                k += 1;
            }
        }
        if (k == 2) {
            printf("%d число: %d\n", iter, i);
            iter++;
        }
        if (iter == 500 + 1) {
                break;
            }
    }

}
