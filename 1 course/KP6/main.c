#include <stdio.h>

struct travel {
    float latitude;
    float longitude;
    char locality[32];
    int cost;
};

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        fprintf(stderr, "Вы ввели неверное количество аргументов!\n");
        return 1;
    }
    
    struct travel t;
    
    FILE *from = fopen(argv[1], "r");
    FILE *here = fopen(argv[2], "w");
    
    while (fscanf(from, "%e    %e    %[^\t]    %d", &t.latitude, &t.longitude,  t.locality, &t.cost) == 4) {
        
        if (1 != fwrite(&t, sizeof(t), 1, here)) {
            fprintf(stderr, "Произошла ошибка!\n");
            return 1;
        }    
        
    }

    fclose(from);
    fclose(here);
}
