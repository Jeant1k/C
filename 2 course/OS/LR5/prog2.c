#include <stdio.h>
#include <time.h>
#include <dlfcn.h>

void help() {
    printf("Приветствую в программе, которая умеет находить количество простых чисел и переводить число из десятичной системы счисления в двоичную. Введите:\n\n\t0 - переключить реализацию контрактов на другую\n\t1 A B - посчитать количество простых чисел от числа A до числа B включительно\n\t2 n - перевести число n в двоичную систему счисления\n\nдля того, чтобы воспользоваться программой.\n\n");
}

int main(void) {
    
    const char* libs[] = {"./lib1.so", "./lib2.so"};
    int arg, cur_lib = 0;
    help();

    void *lib_handler;
    int (*func1)(int a, int b);
    char *(*func2)(long x);

    lib_handler = dlopen("./lib1.so", RTLD_LAZY);
	if (lib_handler == NULL) {
		fprintf(stderr, "dlopen() error: %s\n", dlerror());
		return 1;
	};

    func1 = dlsym(lib_handler, "prime_count");
    func2 = dlsym(lib_handler, "translate");
    
    while(scanf("%d", &arg) != EOF) {
        if (arg == 0) {
            if (cur_lib == 0) {
                cur_lib++;
            } else {
                cur_lib--;
            }
            dlclose(lib_handler);
            lib_handler = dlopen(libs[cur_lib], RTLD_LAZY);
        	if (lib_handler == NULL) {
        		fprintf(stderr, "dlopen() error: %s\n", dlerror());
        		return 1;
        	};
            func1 = dlsym(lib_handler, "prime_count");
            func2 = dlsym(lib_handler, "translate");
            printf("Реализация контрактов успешно переключена!\n\n");
        } else if (arg == 1) {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("Между числами %d и %d находится %d простых чисел.\n\n", a, b, (*func1)(a, b));
        } else if (arg == 2) {
            long n;
            scanf("%ld", &n);
            printf("Число %ld в двоичной системе счисления: %s\n\n", n, (*(*func2))(n));
        } else {
            help();
            return -1;
        }
    }
    
    dlclose(lib_handler);
}
