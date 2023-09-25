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
            continue;
        } else if (s == STATE_NOT_A_DIGIT && c == '-') {
            minus = true;
            s = STATE_MINUS;
        } else if (s == STATE_NOT_A_DIGIT && is_digit(c)) {
            s = STATE_DIGIT;
            dig = char2double(c);
        } else if (s == STATE_MINUS && is_digit(c)) {
            s = STATE_DIGIT;
            dig = char2double(c);
        } else if (s == STATE_DIGIT && c == ' ') {
            s = STATE_NOT_A_DIGIT;
            if (minus) {
                dig *= -1;
            }
            qdbl_push_back(&q, dig);
            dig = 0;
            minus = false;
        } else if (s == STATE_DIGIT && is_digit(c)) {
            dig = dig * 10 + char2double(c);
        } else if (s == STATE_DIGIT && c == '.') {
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
            s = STATE_FRACTIONAL_PART;
            dig = dig + char2double(c) / 10;
        } else if (s == STATE_FRACTIONAL_PART && c == ' ' ) {
            s = STATE_NOT_A_DIGIT;
            if (minus) {
                dig *= -1;
            }
            qdbl_push_back(&q, dig);
            minus = false;
            dig = 0;
            k = 2;
        } else if (s == STATE_FRACTIONAL_PART && is_digit(c)) {
            dig = dig + char2double(c) / power(10, k);
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
