#include <stdio.h>

int main(void) {
    int a[100];
    int power;
    scanf("%d", &power);
    for (int i = 0; i <= power; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= power; i++) {
        printf("%d ", a[i] * i);
    }
}
