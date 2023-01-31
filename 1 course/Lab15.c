#include <stdio.h>

#define max_order 8

int scan_matr(int n, int m[max_order][max_order]) {

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &m[i][j]);
        }
    }
    return 0;

}

int mult_upp_triang_by_low_triang_min(int n, int m[max_order][max_order]) {

    int mn = m[0][0];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (m[i][j] < mn) {
                mn = m[i][j];
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i <= j; ++i) {
            m[i][j] *= mn;
        }
    }

    return 0;
}

int print_matr(int n, int m[max_order][max_order]) {

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", m[i][j]);
        }
        putchar('\n');
    }
    return 0;

}

int main(void) {
 
    int m[max_order][max_order];

    int n;
    printf("Введите порядок квадратной матрицы: ");
    scanf("%d", &n);
    printf("Введите саму матрицу:\n");
    scan_matr(n, m);

    mult_upp_triang_by_low_triang_min(n, m);

    printf("Ответ:\n");
    print_matr(n, m);

}
