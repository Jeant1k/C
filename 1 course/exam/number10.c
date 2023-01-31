#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double function(double x) {
    return cos(x) + pow(tan(x), 2);
}

void print_num_matr(int** M, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

void print_graphics(int** M, int rows, int cols) {
    char vert = (char)124;
    char horiz = (char)45;
    char arrow_up = '^';
    char arrow_left = '>';
    char main_c = '*';
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(M[i][j] == 0) {
                printf(" ");
            } else if(M[i][j] == 1) {
                printf("%c", main_c);
            } else if(M[i][j] == 2) {
                printf("%c", vert);
            } else if(M[i][j] == 3) {
                printf("%c", horiz);
            } else if(M[i][j] == 4) {
                printf("%c", arrow_up);
            } else if(M[i][j] == 5) {
                printf("%c", arrow_left);
            }
        }
        printf("\n");
    }
}

int main() {
    const int screen_h = 120;
    const int screen_w = 120;
    const double scale = 20;
    // создание и инициализация матрицы
    int** field = (int**)malloc(screen_h * sizeof(int*));
    for(int i = 0; i < screen_h; i++) {
        field[i] = (int*)malloc(screen_w * sizeof(int));
        for(int j = 0; j < screen_w; j++) {
            field[i][j] = 0;
        }
    }
    // рисуем оси
    // вертикальная ось
    for(int i = 0; i < screen_h; i++) {
        field[i][screen_w/2] = 2;
        if(i == 0) {
            field[i][screen_w/2] = 4;
        }
    }
    // горизонтальная ось
    for(int i = 0; i < screen_w; i++) {
        field[screen_h/2][i] = 3;
        if(i == screen_w - 1) {
            field[screen_h/2][i] = 5;
        }
    }
    for(int i = 0; i < screen_w; i++) {
        double x = ((double)i - (double)(screen_w / 2)) / scale;
        double f = scale * function(x);
        int y = screen_w / 2 - ceil(f);
        if(y >= 0 && y < screen_h) {
            field[y][i] = 1;
        }
    }
    //print_num_matr(field, screen_h, screen_w);
    print_graphics(field, screen_h, screen_w);
    // освобождаем память
    for(int i = 0; i < screen_h; i++) {
        free(field[i]);
    }
    free(field);
    return 0;
}
