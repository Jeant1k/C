#include "lib.h"

int prime_count(int a, int b) {
    int digits[b - a + 1];
    for (int i = 0; i < b + 1; i++) {
        digits[i] = i;
    }
    digits[1] = 0;
    for (int i = 2; i < (int)sqrt(b) + 1; i++) {
        if (digits[i] != 0) {
            for (int j = 2 * i; j < b + 1; j += i) {
                digits[j] = 0;
            }
        }
    }
    int count = 0;
    for (int i = 0; i < b + 1; i++) {
        if (digits[i] != 0) {
            count++;
        }
    }
    return count;
}

static void reverse(char *mass) {
    int length = 0;
    for (int i = 0; mass[i] != '\0'; i++) {
        length++;
    }
    for (int i = 0; i < length / 2; i++) {
        char tmp = mass[i];
        mass[i] = mass[length - i - 1];
        mass[length - i - 1] = tmp;
    }
}

static char *dec2smth(long x, int system) {
    char *smth = malloc(INT_MAX * sizeof(char));
    int i = 0;
    while (x) {
        smth[i] = x % system + '0';
        i++;
        x /= system;
    }
    smth[i + 1] = '\0';
    reverse(smth);
    return smth;
}

char *translate(long x) {
    return dec2smth(x, 3);
}
