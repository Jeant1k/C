#include <stdio.h>
#include <math.h>

int get_byte(int input, int num) {
    return (input >> (num * 8)) & 255;
}

int main() {
    int n, input;
    scanf("%d %d", &input, &n);
    printf("%d\n", get_byte(input, n));
}
