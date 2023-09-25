#include "lib.h"

int prime_count(int a, int b) {
    int count = 0;
    for (int i = a; i < b + 1; i++) {
        int dividers = 0;
        if (i == 1) {
            continue;
        }
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                dividers++;
                break;
            }
        }
        if (dividers == 0) {
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
    return dec2smth(x, 2);
}
