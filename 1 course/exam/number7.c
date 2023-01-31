#include <stdio.h>

int main(void) {
    double dig;
    scanf("%lf", &dig);
    int chisl = 0;
    int znam = 0;
    for (int i = 1; i < 100000; i++) {
        for (int j = 1; j < 100000; j++) {
            if ((double)i / (double)j == dig) {
                chisl = i;
                znam = j;
                printf("%d / %d\n", chisl, znam);
                break;
            }
        }
        if (chisl != 0 && znam != 0) {
            break;
        }
    }
}
