#include <stdio.h>

int is_sep(int c) {
    return c == ' ' || c == ',' || c == '\n' || c == '\t';
}

int main(void) {
    char words[20][4];
    int c = 0;
    int word = 0;
    int i = 0;
    int max_i = 0;
    while ((c = getchar()) != EOF) {
        if (!is_sep(c)) {
            words[i][word] = (char)c;
            i++;
        } else {
            if (i > max_i) {
                max_i = i;
            }
            i = 0;
            word++;
        }
    }

    int flag = 0;
    char letters[20];
    for (int m = 0; m <= max_i; m++) {
        for (int n = 0; n <= word; n++) {
            letters[n] = words[m][n];
        }
        for (int v = 0; v < word; v++) {
            if ((int)letters[v] > (int)letters[v + 1]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            printf("No");
            break;
            }
        printf("\n");
    }
}
