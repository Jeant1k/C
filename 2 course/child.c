
#include "parser.h"
#include <float.h> 

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

double char2double(char c) {
    return (double)c - '0';
}

int power(int dig, int pow) {
    double res = 1;
    for (int i = 0; i < pow; i++) {
        res *= dig;
    }
    return res;
}

queue_dbl parser() {
    queue_dbl q;
    qdbl_init(&q);
    char c;
    state s = STATE_NOT_A_DIGIT;
    double dig;
    int k = 2;
    int count = 0;
    bool minus = false;
    while ((c = getchar()) != EOF) {
        count++;
        if  (s == STATE_NOT_A_DIGIT && (c == ' ' || c == '\n')) {
            // printf("1) Я прочитала пробел под номером %d\n", count);
            continue;
        } else if (s == STATE_NOT_A_DIGIT && c == '-') {
            // printf("2) Я прочитала %c под номером %d\n", c, count);
            minus = true;
            s = STATE_MINUS;
        } else if (s == STATE_NOT_A_DIGIT && is_digit(c)) {
            // printf("3) Я прочитала %c под номером %d\n", c, count);
            s = STATE_DIGIT;
            dig = char2double(c);
            // printf("1) Сформировано %lf\n", dig);
        } else if (s == STATE_MINUS && is_digit(c)) {
            // printf("Я прочитала %c под номером %d\n", c, count);
            s = STATE_DIGIT;
            dig = char2double(c);
            // printf("2) Сформировано %lf\n", dig);
        } else if (s == STATE_DIGIT && c == ' ') {
            s = STATE_NOT_A_DIGIT;
            if (minus) {
                dig *= -1;
            }
            // printf("Из пункта, где число без точки записываем %lf\n", dig);
            qdbl_push_back(&q, dig);
            dig = 0;
            minus = false;
        } else if (s == STATE_DIGIT && is_digit(c)) {
            // printf("4) Я прочитала %c под номером %d\n", c, count);
            dig = dig * 10 + char2double(c);
            // printf("3) Сформировано %lf\n", dig);
        } else if (s == STATE_DIGIT && c == '.') {
            // printf("5) Я прочитала %c под номером %d\n", c, count);
            s = STATE_DOT;
        } else if (s == STATE_DIGIT && c == '\n') {
            s = STATE_NOT_A_DIGIT;
            if (minus) {
                dig *= -1;
            }
            qdbl_push_back(&q, dig);
            qdbl_push_back(&q, DBL_MAX);
            dig = 0;
            minus = false;
        } else if (s == STATE_DOT && is_digit(c)) {
            // printf("6) Я прочитала %c под номером %d\n", c, count);
            s = STATE_FRACTIONAL_PART;
            dig = dig + char2double(c) / 10;
            // printf("4) Сформировано %lf\n", dig);
        } else if (s == STATE_FRACTIONAL_PART && c == ' ' ) {
            s = STATE_NOT_A_DIGIT;
            if (minus) {
                dig *= -1;
            }
            // printf("Из пункта, где число с точкой записываем %lf\n", dig);
            qdbl_push_back(&q, dig);
            minus = false;
            dig = 0;
            k = 2;
        } else if (s == STATE_FRACTIONAL_PART && is_digit(c)) {
            // printf("7) Я прочитала %c под номером %d\n", c, count);
            dig = dig + char2double(c) / power(10, k);
            // printf("5) Сформировано %lf\n", dig);
            k++;
        } else if (s == STATE_FRACTIONAL_PART && c == '\n') {
            s = STATE_NOT_A_DIGIT;
            if (minus) {
                dig *= -1;
            }
            qdbl_push_back(&q, dig);
            qdbl_push_back(&q, DBL_MAX);
            minus = false;
            dig = 0;
            k = 2;
        }
    }
    return q;
}
