#include <stdio.h>
#include "svdbl.h"

typedef struct {
    int m;
    int n;
} dimension;

typedef enum {
    STATE_NOT_A_DIGIT,    // 0
    STATE_FIRST_ZERO,    // 1
    STATE_LINE,    // 2
    STATE_COLUMN,    // 3
    STATE_VALUE,    // 4
    STATE_SECOND_ZERO    // 5
} state;

svector_dbl read_matrix(int m, int n) {
    printf("Введите матрицу:\n");
    svector_dbl res;
    svdbl_init(&res);
    for (int i = 0; i < m; i++) {
        svdbl_push_back(&res, 0.);
        svdbl_push_back(&res, (double)(i + 1));
        for (int j = 0; j < n; j++) {
            double a;
            if(scanf("%lf", &a)){};
            if (a != 0) {
                svdbl_push_back(&res, (double)(j + 1));
                svdbl_push_back(&res, a);
            }
        }
    }
    svdbl_push_back(&res, 0.);
    svdbl_push_back(&res, 0.);
    return res;
}

svector_dbl read_column(int n) {
    printf("Введите столбец:\n");
    svector_dbl res;
    svdbl_init(&res);
    for (int i = 0; i < n; i++) {
        double a;
        if(scanf("%lf", &a)){};
        svdbl_push_back(&res, a);
    }
    return res;
}

dimension read_dimension() {
    printf("Введите размерность матрицы:\n");
    dimension res;
    int m, n;
    if(scanf("%d%d", &m, &n)){};
    res.m = m;
    res.n = n;
    return res;
}

svector_dbl multiplication(svector_dbl mtr, svector_dbl clm) {
    svector_dbl res;
    svdbl_init(&res);
    state s = STATE_NOT_A_DIGIT;
    int j = 0;
    double sum = 0.;
    for (int i = 0; i < svdbl_get_size(&mtr); i++) {
        if (s == STATE_NOT_A_DIGIT && svdbl_get(&mtr, i) == 0) {
            s = STATE_FIRST_ZERO;
        } else if (s == STATE_FIRST_ZERO && svdbl_get(&mtr, i) != 0) {
            s = STATE_LINE;
        } else if (s == STATE_LINE && svdbl_get(&mtr, i) == 0) {
            s = STATE_FIRST_ZERO;
            svdbl_push_back(&res, 0.);
        } else if (s == STATE_LINE && svdbl_get(&mtr, i) != 0) {
            s = STATE_COLUMN;
            j = svdbl_get(&mtr, i);
        } else if (s == STATE_COLUMN && svdbl_get(&mtr, i) != 0) {
            s = STATE_VALUE;
            sum += svdbl_get(&mtr, i) * svdbl_get(&clm, j - 1);
        } else if (s == STATE_VALUE && svdbl_get(&mtr, i) != 0) {
            s = STATE_COLUMN;
            j = svdbl_get(&mtr, i);
        } else if (s == STATE_VALUE && svdbl_get(&mtr, i) == 0) {
            s = STATE_FIRST_ZERO;
            svdbl_push_back(&res, sum);
            sum = 0;
        } else if (s == STATE_FIRST_ZERO && svdbl_get(&mtr, i) == 0) {
            s = STATE_SECOND_ZERO;
        } 
    }
    return res;
}

int number_nonzero(svector_dbl mltpl) {
    int res = 0;
    for (int i = 0; i < svdbl_get_size(&mltpl); i++) {
        if (svdbl_get(&mltpl, i) != 0) {
            res++;
        }
    }
    return res;
}

int main(void) {
    dimension dim = read_dimension();
    svector_dbl matr = read_matrix(dim.m, dim.n);
    svector_dbl clmn = read_column(dim.n);
    svector_dbl mltpl = multiplication(matr, clmn);
    printf("Количество ненулевых элементов: %d\n", number_nonzero(mltpl));
}
