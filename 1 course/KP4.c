#include <stdio.h>
#include <math.h>

struct result {
    double x;
    int iters;
    int success;
};

double my_func_14(double x) {
    return tan(x / 2) - 1/tan(x / 2) + x;
}

double my_func_14_x(double x) {
    return tan(x / 2) - 1/tan(x / 2) + 2 * x;
}

double my_func_15(double x) {
    return 0.4 + atan(sqrt(x)) - x;
}

double my_func_15_x(double x) {
    return 0.4 + atan(sqrt(x));
}

double dx(double (*f)(double), double x) {
    double dx = pow(2, -26);
    return (f(x + dx) - f(x - dx)) / (2 * dx);
}

double ddx(double (*f)(double), double x) {
    double dx = pow(2, -13);
    return (f(x + dx) - 2 * f(x) + f(x - dx)) / (dx * dx); 
}

struct result diho(double (*f)(double), double a, double b) {
    struct result res;
    double delta = pow(2, -26);
    res.iters = 0;
    while (b - a > delta) {
        double c = (a + b) / 2;
        if (f(a) * f(c) < 0) {
            b = c;
        } else {
          a = c;
        }
        res.iters++;
    }
    res.x = (a + b) / 2;
    res.success = 1;
    return res;
}

struct result iter(double (*f)(double), double a, double b) {
    struct result res;
    double delta = pow(2, -26);
    double x_k = (a + b) / 2;
    double x_k_1 = x_k;
    res.iters = 0;
    do {
        if (fabs(dx(f, x_k)) >= 1) {
            res.success = 0;
            return res;
        }
        x_k = x_k_1;
        x_k_1 = f(x_k);
        res.iters++;
    } while (fabs(x_k_1 - x_k) > delta);
    res.x = x_k_1;
    res.success = 1;
    return res;
}

struct result newton(double (*f)(double), double a, double b) {
    struct result res;
    double x_k = (a + b) / 2;
    double delta = pow(2, -26);
    double x_k_1 = x_k;
    res.iters = 0;
    do {
        if (fabs(f(x_k) * ddx(f, x_k)) >= pow(dx(f, x_k), 2)) {
            res.success = 0;
            return res;
        }
        x_k = x_k_1;
        x_k_1 = x_k - f(x_k) / dx(f, x_k);
        res.iters++;
    } while (fabs(x_k_1 - x_k) > delta);
    res.x = x_k_1;
    res.success = 1;
    return res;
}

int main() {

    struct result res_diho_1 = diho(my_func_14, 1.0, 2.0);
    double x_diho_1 = res_diho_1.x;
    int iter_diho_1 = res_diho_1.iters;

    struct result res_iter_1 = iter(my_func_14_x, 1.0, 2.0);
    double x_iter_1 = res_iter_1.x;
    int iter_iter_1 = res_iter_1.iters;
    int success_iter_1 = res_iter_1.success;

    struct result res_newton_1 = newton(my_func_14, 1.0, 2.0);
    double x_newton_1 = res_newton_1.x;
    int iter_newton_1 = res_newton_1.iters;
    int success_newton_1 = res_newton_1.success;

    struct result res_dih_2 = diho(my_func_15, 1.0, 2.0);
    double x_diho_2 = res_dih_2.x;
    int iter_diho_2 = res_dih_2.iters;

    struct result res_iter_2 = iter(my_func_15_x, 1.0, 2.0);
    double x_iter_2 = res_iter_2.x;
    int iter_iter_2 = res_iter_2.iters;
    int success_iter_2 = res_iter_2.success;

    struct result res_newton_2 = newton(my_func_15, 1.0, 2.0);
    double x_newton_2 = res_newton_2.x;
    int iter_newton_2 = res_newton_2.iters;
    int success_newton_2 = res_newton_2.success;

    printf("╔════════════════════════════╦════════════╦═══════════╦══════════════╦══════════╦═════════════════╗\n");
    printf("║          Функция           ║ Промежуток ║   Метод   ║ Применимость ║  Корень  ║ Кол-во итераций ║\n");
    printf("╠════════════════════════════╬════════════╬═══════════╬══════════════╬══════════╬═════════════════╣\n");
    printf("║                            ║            ║ Дихотомия ║      Да      ║ %lf ║        %d       ║\n", x_diho_1, iter_diho_1);
    printf("║ tg(x / 2) - ctg(x / 2) + x ║   [1, 2]   ║ Итераций  ║      Да      ║ %lf ║        %d        ║\n", x_iter_1, iter_iter_1);
    printf("║                            ║            ║ Ньютона   ║      Да      ║ %lf ║        %d        ║\n", x_newton_1, iter_newton_1);
    printf("╠════════════════════════════╬════════════╬═══════════╬══════════════╬══════════╬═════════════════╣\n");
    printf("║                            ║            ║ Дихотомия ║      Да      ║ %lf ║        %d       ║\n", x_diho_2, iter_diho_2);
    printf("║     0,4 + arctg(√x) - x    ║   [1, 2]   ║ Итераций  ║      Да      ║ %lf ║        %d       ║\n", x_iter_2, iter_iter_2);
    printf("║                            ║            ║ Ньютона   ║      Да      ║ %lf ║        %d        ║\n", x_newton_2, iter_newton_2);
    printf("╚════════════════════════════╩════════════╩═══════════╩══════════════╩══════════╩═════════════════╝\n");
}
