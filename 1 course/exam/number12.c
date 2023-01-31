#include <stdio.h>

int get_byte(int input, int num) {
    return (input >> (num * 8)) & 255;
}

int main(void) {
    int a, n;
    scanf("%d %d", &a, &n);
    a = a >> 8 * n;
    printf("%d", a);
}
