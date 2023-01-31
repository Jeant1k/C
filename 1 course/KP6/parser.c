#include <stdio.h>
#include <string.h>

void print_str(char *str) {
    for (int i = 0; i < strlen(str); i ++) {
        printf("%c", str[i]);
    }
    printf(" ");
}

struct travel {
    float latitude;
    float longitude;
    char locality[32];
    int cost;
};

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr, "Вы ввели неверное количество аргументов!\n");
        return 1;
    }

    struct travel t;
    FILE *from = fopen(argv[1], "r");
    int max_cost = 0;

    while (fread(&t, sizeof(t), 1, from) == 1) {
        if (max_cost < t.cost) {
            max_cost = t.cost;
        }
    }

    int second_category = max_cost / 3;
    int third_category = max_cost / 3 * 2;

    fseek(from, 0, SEEK_SET);

    printf("\n");
    printf("В первую ценовую категорию (от 0 до %d рублей) стоимостей поездок в различные курорты относится:\n", second_category);
    
    while(fread(&t, sizeof(t), 1, from) == 1) {
        if (t.cost <= second_category) {
            print_str(t.locality);
            printf("\t\t%.2f\t%.2f\t%d\n", t.latitude, t.longitude, t.cost);
        }
    }
    
    fseek(from, 0, SEEK_SET);

    printf("\n");
    printf("Во вторую ценовую категорию (от %d до %d рублей) стоимостей поездок в различные курорты относится:\n", second_category, third_category);

    while(fread(&t, sizeof(t), 1, from) == 1) {
        if (second_category < t.cost && t.cost <= third_category) {
            print_str(t.locality);
            printf("\t\t%.2f\t%.2f\t%d\n", t.latitude, t.longitude, t.cost);
        }
    }

    fseek(from, 0, SEEK_SET);
    
    printf("\n");
    printf("В третью ценовую категорию (от %d до %d рублей) стоимостей поездок в различные курорты относится:\n", third_category, max_cost);

    while(fread(&t, sizeof(t), 1, from) == 1) {
        if (third_category < t.cost && t.cost <= max_cost) {
            print_str(t.locality);
            printf("\t\t%.2f\t%.2f\t%d\n", t.latitude, t.longitude, t.cost);
        }
    }
}
