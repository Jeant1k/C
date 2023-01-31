#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = n; i >= 0; i--) {
        a[n - i] = a[n - i] * i;
    }
    for (int i = 0; i <= n; i++) {
        printf("%d\n", a[i]);
    }
}
