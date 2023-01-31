#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

typedef struct {
    char command;
    int k;
    double val;
} command;

typedef enum {

    STATE_NOT_WORD, // 0

    STATE_HELP, // 1
    STATE_HELP_AND_SPACE, // 2

    STATE_PRINT, // 3
    STATE_PRINT_AND_SPACE, // 4

    STATE_INSERT, // 5
    STATE_INSERT_AND_FIRST_SPACE, // 6
    STATE_INSERT_AND_MINUS, // 6,5
    STATE_INSERT_AND_FIRST_DIGIT, // 7
    STATE_INSERT_AND_SECOND_SPACE, // 8
    STATE_INSERT_AND_SECOND_DIGIT, // 9
    STATE_INSERT_AND_DOT, // 10
    STATE_INSERT_AND_THIRD_DIGIT, // 11
    STATE_INSERT_AND_THIRD_SPACE, // 11,5

    STATE_DELETE, // 12
    STATE_DELETE_AND_FIRST_SPACE, // 13
    STATE_DELETE_AND_DIGIT, // 14
    STATE_DELETE_AND_SECOND_SPACE, // 14,5

    STATE_LENGTH, // 15
    STATE_LENGTH_AND_SPACE, // 16

    STATE_CHANGE, // 17
    STATE_CHANGE_AND_FIRST_SPACE, // 18
    STATE_CHANGE_AND_DIGIT, // 19
    STATE_CHANGE_AND_SECOND_SPACE, // 20

    STATE_BAD_WORD, // 21

} state;

bool is_digit(char c);
double char2double(char c);
int power(int dig, int pow);

bool _help(char c);
bool _print(char c);
bool _insert(char c);
bool _delete(char c);
bool _length(char c);
bool _change(char c);

command parser();
