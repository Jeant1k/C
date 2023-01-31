#include <stdio.h>

int palindrome(unsigned int a) {
    unsigned int rev = 0;
    unsigned int dig = a;
    while (a > 0) {
        rev = rev * 10 + a % 10;
        a /= 10;
    }
    return dig == rev;
}

int main(void) {
    printf("Введите число для проверки: ");
    unsigned int dig = 0;
    scanf("%d", &dig);
    if (palindrome(dig)) {
        printf("Число ялвяется палиндромом");
    } else {
        printf("Число не является палиндромом");
    }
}
