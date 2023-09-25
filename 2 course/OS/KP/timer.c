#include <stdio.h>
#include <unistd.h>

#define RESET "\033[0m"
#define GREEN "\033[0;32m"

int main(int argc, char *argv[]) {
    
    int i = 0, dig = 0;
    while (argv[1][i] != '\0') {
        dig = dig * 10 + argv[1][i] - '0';
        i++;
    }
    
    sleep(1000);
    
    printf("%sДжоба с id = %d отработала!%s\n", GREEN, dig, RESET);

    return 0;
    
}
