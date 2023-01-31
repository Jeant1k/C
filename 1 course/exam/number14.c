#include <stdio.h>

int main(void) {
    int ASCII = 255;
    int cod = ASCII;
    for (int i = 0; i <= cod; i++) {
        printf("%d: %c\n", i, i);
    }
}
