#include <stdio.h>
int main() {
    int q0, q1;
    char a, b, move;
    while (scanf("(%d, %c, %c, %c, %d)", &q0, &a, &b, &move, &q1)) {
        if ((int)move == (int)'u') {
            printf("(%d, %c, %c, %d)\n", q0, a, b, q1);
        } else if ((int)a == (int)b) {
            printf("(%d, %c, %c, %d)\n", q0, a, move, q1);
        } else {
            printf("(%d, %c, %c, %d)\n", q0, a, b, q0 + q1);
            printf("(%d, %c, %c, %d)\n", q0 + q1, b, move, q1);
        }
        if ((int)move == (int)'s') {
            break;
        }
    }
}
