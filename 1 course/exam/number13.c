#include <stdio.h>

int palindr(int dig) {
    int rev = 0;
    int copy = dig;
    while (copy > 0) {
        rev = rev * 10 + (copy % 10);
        copy = copy / 10;
    }
    return rev == dig;
}

int main() {
    int dig;
    scanf("%d", &dig);
    if (palindr(dig)) {
        printf("Yes!\n");
    } else {
        printf("No!\n");
    }
}
