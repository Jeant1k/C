#include <stdio.h>
#include <math.h>

double mach_eps_search() {

    double e = 1;
    while (e / 2 + 1 > 1) {
		e /= 2;
	}
    return e;

}

double func(double x) {
    return (2 * x - 3) / (pow(x - 1, 2));
}

int main() {

    double e = mach_eps_search();
    printf("Машинный эпсилон равен %.2e\n", e);
    
    int n;
    printf("Введите n: ");
    scanf("%d", &n);

    printf("  x          sum_of_ser             func_value       i     difference  \n");

    double a = -0.1, b = 0.6;
    double x = a;
    for (int i = 0; i <= n; ++ i) {
        double part_summ = a, summ = -3;
        int iter = 0, k = 1;
        while (fabs(part_summ) > e && iter <= 100) {
            part_summ = (k + 3) * pow(x, k);
            summ -= part_summ;
            k ++;
            iter ++;
        }
        double func_value = func(x);
        printf("%.3f   %.16f   %.16f   %d   %e\n", x, summ, func_value, iter, summ - func_value);
        x += (b - a) / n;
        
    }
}
