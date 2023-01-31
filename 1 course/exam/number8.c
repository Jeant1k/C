#include <stdio.h>
#include <string.h>


int main(void) {
    char str1[128];
    scanf("%s", str1);
    int len1 = strlen(str1);
    for (int i = 0; i < len1; i++) {
        if (str1[i - 1] > str1[i]) {
            char t = str1[i];
            str1[i] = str1[i - 1];
            str1[i - 1] = t;
            i -= 2;
            if (i < 0) {
                i = 0;
            }
        }
    }
    printf("%s", str1);
}
