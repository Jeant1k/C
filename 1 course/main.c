#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "parser.h"
#include "bdlist.h"

void cmd_help() {
    printf("\nБлагодя этой программе вы можете поиграть со списком. Она умеет выводить справку, печатать список, вставлять новые элементы, удалять элементы, печатать длину списка, и менять местами элементы.\n\nСписок команд, их описание и синтаксис:\n\nhelp - вывод справки. Синтаксис: help.\nprint - печать списка. Синтаксис: print.\ninsert - вставка элемента val типа double в конец списка. Синтаксис: insert [val].\ndelete - удаление k-ого элемента. k типа unsigned int. Синтаксис: delete [k]\nlength - вывод количества элементов списка. Синтаксис: length.\nchange - смена мест k - 1 и k + 1 элемента. k типа unsigned int. Синтаксис: change [k]\n\nВАЖНО! Нумерация элементов начинается с 0.\n\n");
}

int main(void) {
    list l;
    list_init(&l);
    list_iter it;
    cmd_help();
    command cmd;
    while (true) {
        cmd = parser();
        if (cmd.command == 'h') {
            cmd_help();
        }
        if (cmd.command == 'p') {
            putchar('\n');
            it = list_iter_begin(&l);
            if (list_iter_equal(list_iter_begin(&l), list_iter_end(&l))) {
                printf("Список пуст.");
            } else {
                while (!list_iter_equal(it, list_iter_end(&l))) {
                    printf("%lf ", list_iter_get(&it));
                    list_iter_move_next(&it);
                }
            }
            printf("\n\n");
        }
        if (cmd.command == 'i') {
            it = list_iter_end(&l);
            list_iter_insert_before(&it, cmd.val);
            printf("\nВставил элемент %lf в конец.\n\n", cmd.val);
        }
        if (cmd.command == 'd') {
            it = list_iter_begin(&l);
            int count = 0;
            while (!list_iter_equal(it, list_iter_end(&l))) {
                count++;
                list_iter_move_next(&it);
            }
            if (cmd.k > count - 1) {
                printf("\nЭлемента с индексом %d в списке нет\n\n", cmd.k);
            } else {
                it = list_iter_begin(&l);
                for (int i = 0; i < cmd.k; i++) {
                    list_iter_move_next(&it);
                }
                double el = list_iter_get(&it);
                list_iter_remove(&it);
                printf("\nУдалил элемент %lf с индексом %d\n\n", el, cmd.k);
            }
        }
        if (cmd.command == 'l') {
            it = list_iter_begin(&l);
            int count = 0;
            while (!list_iter_equal(it, list_iter_end(&l))) {
                count++;
                list_iter_move_next(&it);
            }
            printf("\nДлина списка равна %d.\n\n", count);
        }
        if (cmd.command == 'c') {
            it = list_iter_begin(&l);
            int count = 0;
            while (!list_iter_equal(it, list_iter_end(&l))) {
                count++;
                list_iter_move_next(&it);
            }
            if (cmd.k > count - 1) {
                printf("\nЭлемента с индексом %d в списке нет\n\n", cmd.k);
            }
            if (count - 2 < cmd.k && cmd.k <= count - 1) {
                printf("\nНельзя произвести обмен, так как это последний элемент.\n\n");
            }
            if (count - 2 >= cmd.k && cmd.k >= 1) {
                it = list_iter_begin(&l);
                for (int i = 0; i < cmd.k - 1; i++) {
                    list_iter_move_next(&it);
                }
                double el1 = list_iter_get(&it);
                list_iter_move_next(&it);
                list_iter_move_next(&it);
                double el2 = list_iter_get(&it);
                list_iter_set(&it, el1);
                list_iter_move_prev(&it);
                list_iter_move_prev(&it);
                list_iter_set(&it, el2);
                printf("\nПоменял местами элемент %lf и %lf.\n\n", el1, el2);
            }
            if (cmd.k < 1) {
                printf("\nНельзя произвести обмен, так как это первый элемент.\n\n");
            }
        }
        if (cmd.command == 'w' && cmd.k == 0) {
            printf("\nВы имели в виду команду help?\n\nhelp - вывод справки. Синтаксис: help.\n\n");
        }
        if (cmd.command == 'w' && cmd.k == 1) {
            printf("\nВы имели в виду команду print?\n\nprint - печать списка. Синтаксис: print.\n\n");
        }
        if (cmd.command == 'w' && cmd.k == 2) {
            printf("\nВы имели в виду команду insert?\n\ninsert - вставка элемента val типа double в конец списка. Синтаксис: insert [val].\n\n");
        }
        if (cmd.command == 'w' && cmd.k == 3) {
            printf("\nВы имели в виду команду delete?\n\ndelete - удаление k-ого элемента. k типа unsigned int. Синтаксис: delete [k]\n\n");
        }
        if (cmd.command == 'w' && cmd.k == 4) {
            printf("\nВы имели в виду команду length?\n\nlength - вывод количества элементов списка. Синтаксис: length.\n\n");
        }
        if (cmd.command == 'w' && cmd.k == 5) {
            printf("\nВы имели в виду команду change?\n\nchange - смена мест k - 1 и k + 1 элемента. k типа unsigned int. Синтаксис: change [k]\n\n");
        }
        if (cmd.command == 'w' && cmd.k == 6) {
            printf("\nЧтобы вывести справку, наберите help\n\n");
        }
    }
}
