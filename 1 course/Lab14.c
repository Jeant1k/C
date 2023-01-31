#include <stdio.h> 

enum {maxn = 100};

int main(){
	int m[maxn][maxn];
	
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d", &m[i][j]);
		}
	}
	
    if (n == 1) {
        printf("%d\n", m[0][0]);
    } else {

        int i = 0;
        int j = 0;
        int len_1 = n;
        while (len_1 > 0) {
            printf("%d ", m[i][j]);
            i ++;
            j ++;
            len_1 --;
        }
        
        int len_2 = n;
        int i_head = 0;
        int j_head = 0;
        int k = n - 1;
        for (int r = 1; r <= len_2; r ++) {
            if (r % 2 == 1) {
                i_head = len_2 - r - 1;
                j_head = len_2 - 1;
                for (int v = 1; v <= k; v ++) {
                    printf("%d ", m[i_head][j_head]);
                    i_head --;
                    j_head --;
                }
                i_head = len_2 - r - 1;
                j_head = len_2 - 1;
                for (int w = 1; w <= k; w ++) {
                    printf("%d ", m[j_head][i_head]);
                    i_head --;
                    j_head --;
                }
            } else {
                i_head = r;
                j_head = 0;
                for (int c = 1; c <= k; c ++) {
                    printf("%d ", m[i_head][j_head]);
                    i_head ++;
                    j_head ++;
                }
                i_head = r;
                j_head = 0;
                for (int p = 1; p <= k; p ++) {
                    printf("%d ", m[j_head][i_head]);
                    i_head ++;
                    j_head ++;
                }
            }
            k --;
        }
        putchar('\n');
    }   
}
