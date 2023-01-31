#include <stdio.h>
#include <math.h>

double func(double x) {
    return cos(x);
}

int main() {
    for (int i = 10; i >= -10; i--) {
        for (int j = -25; j <= 25; j++) {
            if (fabs(round(func(j) - i)) == 0) {
                printf("*");
            } else {
                if (i == 0) {
                    printf("-");
                } else if (j == 0) {
                    printf("|");
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}
