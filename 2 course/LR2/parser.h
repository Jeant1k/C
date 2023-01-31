#include <stdio.h>
#include <stdbool.h>
#include "qdbl.h"

typedef enum {
    STATE_NOT_A_DIGIT, // 0
    STATE_MINUS, // 1
    STATE_DIGIT, // 2
    STATE_DOT, // 3
    STATE_FRACTIONAL_PART, // 4
} state;

bool is_digit(char c);
double char2int(char c);
int power(int dig, int pow);

queue_dbl parser();
