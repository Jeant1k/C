#include "parser.h"

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

double char2double(char c) {
    return (double)c - '0';
}

int power(int dig, int pow) {
    double res = 1;
    for (int i = 0; i < pow; i++) {
        res *= dig;
    }
    return res;
}

bool _help(char c) {
    return c == 'h' || c == 'e' || c == 'l' || c == 'p';
}

bool _print(char c) {
    return c == 'p' || c == 'r' || c == 'i' || c == 'n' || c == 't';
}

bool _insert(char c) {
    return c == 'i' || c == 'n' || c == 's' || c == 'e' || c == 'r' || c == 't';
}

bool _delete(char c) {
    return c == 'd' || c == 'e' || c == 'l' || c == 'e' || c == 't' || c == 'e';
}

bool _length(char c) {
    return c == 'l' || c == 'e' || c == 'n' || c == 'g' || c == 't' || c == 'h';
}

bool _change(char c) {
    return c == 'c' || c == 'h' || c == 'a' || c == 'n' || c == 'g' || c == 'e';
}

command parser() {
    command cmd;
    cmd.command = '\0';
    cmd.k = -1;
    cmd.val = -1;
    char str[10] = {'\0'}, flag = '\n', c;
    int k = 0, i = 0, deg = 2, insert_flag_1 = 0, insert_flag_2 = 0, delete_flag = 0, change_flag = 0, minus_flag = 0;
    double val = 0;
    state s = STATE_NOT_WORD;
    while ((c = getchar()) != '\n') {
        if (s == STATE_NOT_WORD && c == ' ') {
            continue;
        } else if (s == STATE_NOT_WORD && c == 'h') {
            str[i] = c;
            i++;
            flag = 'h';
            s = STATE_HELP;
            continue;
        } else if (s == STATE_HELP && _help(c) && i < 4) {
            str[i] = c;
            i++;
            continue;
        } else if (s == STATE_HELP && i < 4) {
            cmd.command = 'w';
            cmd.k = 0;
            continue;
        } else if (s == STATE_HELP && c == ' ') {
            s = STATE_HELP_AND_SPACE;
            continue;
        } else if (s == STATE_HELP) {
            cmd.command = 'w';
            cmd.k = 0;
            continue;
        } else if (s == STATE_HELP_AND_SPACE && c == ' ') {
            continue;
        } else if (s == STATE_HELP_AND_SPACE) {
            cmd.command = 'w';
            cmd.k = 0;
            continue;
        } else if (s == STATE_NOT_WORD && c == 'p') {
            str[i] = c;
            i++;
            flag = 'p';
            s = STATE_PRINT;
            continue;
        } else if (s == STATE_PRINT && _print(c) && i < 5) {
            str[i] = c;
            i++;
            continue;
        } else if (s == STATE_PRINT && i < 5) {
            cmd.command = 'w';
            cmd.k = 1;
            continue;
        } else if (s == STATE_PRINT && c == ' ') {
            s = STATE_PRINT_AND_SPACE;
            continue;
        } else if (s == STATE_PRINT) {
            cmd.command = 'w';
            cmd.k = 1;
            continue;
        } else if (s == STATE_PRINT_AND_SPACE && c == ' ') {
            continue;
        } else if (s == STATE_PRINT_AND_SPACE) {
            cmd.command = 'w';
            cmd.k = 1;
            continue;
        } else if (s == STATE_NOT_WORD && c == 'i') {
            str[i] = c;
            i++;
            flag = 'i';
            s = STATE_INSERT;
            continue;
        } else if (s == STATE_INSERT && _insert(c) && i < 6) {
            str[i] = c;
            i++;
            continue;
        } else if (s == STATE_INSERT && i < 6) {
            cmd.command = 'w';
            cmd.k = 2;
            continue;
        } else if (s == STATE_INSERT && c == ' ') {
            s = STATE_INSERT_AND_FIRST_SPACE;
            continue;
        } else if (s == STATE_INSERT) {
            cmd.command = 'w';
            cmd.k = 2;
            continue;
        } else if (s == STATE_INSERT_AND_FIRST_SPACE && c == ' ') {
            continue;
        } else if (s == STATE_INSERT_AND_FIRST_SPACE && c == '-') {
            minus_flag = 1;
            s = STATE_INSERT_AND_MINUS;
            continue;
        } else if (s == STATE_INSERT_AND_FIRST_SPACE && is_digit(c)) {
            insert_flag_1 = 1;
            val = val * 10 + char2double(c);
            s = STATE_INSERT_AND_SECOND_DIGIT;
            continue;
        } else if (s == STATE_INSERT_AND_FIRST_SPACE) {
            cmd.command = 'w';
            cmd.k = 2;
            continue;
        } else if (s == STATE_INSERT_AND_MINUS && is_digit(c)) {
            insert_flag_1 = 1;
            val = val * 10 + char2double(c);
            s = STATE_INSERT_AND_SECOND_DIGIT;
            continue;
        } else if (s == STATE_INSERT_AND_MINUS) {
            cmd.command = 'w';
            cmd.k = 2;
            continue;
        } else if (s == STATE_INSERT_AND_FIRST_DIGIT && is_digit(c)) {
            k = k * 10 + char2double(c);
            continue;
        } else if (s == STATE_INSERT_AND_FIRST_DIGIT && c == ' ') {
            s = STATE_INSERT_AND_SECOND_SPACE;
            continue;
        } else if (s == STATE_INSERT_AND_FIRST_DIGIT) {
            cmd.command = 'w';
            cmd.k = 2;
            continue;
        } else if (s == STATE_INSERT_AND_SECOND_SPACE && c == ' ') {
            continue;
        } else if (s == STATE_INSERT_AND_SECOND_SPACE && is_digit(c)) {
            insert_flag_2 = 1;
            s = STATE_INSERT_AND_SECOND_DIGIT;
            val = val * 10 + char2double(c);
            continue;
        } else if (s == STATE_INSERT_AND_SECOND_SPACE) {
            cmd.command = 'w';
            cmd.k = 2;
            continue;
        } else if (s == STATE_INSERT_AND_SECOND_DIGIT && is_digit(c)) {
            val = val * 10 + char2double(c);
            continue;
        } else if (s == STATE_INSERT_AND_SECOND_DIGIT && c == '.') {
            s = STATE_INSERT_AND_DOT;
            continue;
        } else if (s == STATE_INSERT_AND_SECOND_DIGIT) {
            cmd.command = 'w';
            cmd.k = 2;
            continue;
        } else if (s == STATE_INSERT_AND_DOT && is_digit(c)) {
            val = val + char2double(c) / 10;
            s = STATE_INSERT_AND_THIRD_DIGIT;
            continue;
        } else if (s == STATE_INSERT_AND_DOT) {
            cmd.command = 'w';
            cmd.k = 2;
            continue;
        } else if (s == STATE_INSERT_AND_THIRD_DIGIT && is_digit(c)) {
            val = val + char2double(c) / power(10, deg);
            deg++;
            continue;
        } else if (s == STATE_INSERT_AND_THIRD_DIGIT && c == ' ') {
            s = STATE_INSERT_AND_THIRD_SPACE;
            continue;
        } else if (s == STATE_INSERT_AND_THIRD_DIGIT) {
            cmd.command = 'w';
            cmd.k = 2;
            continue;
        } else if (s == STATE_INSERT_AND_THIRD_SPACE && c == ' ') {
            continue;
        } else if (s == STATE_INSERT_AND_THIRD_SPACE) {
            cmd.command = 'w';
            cmd.k = 2;
            continue;
        } else if (s == STATE_NOT_WORD && c == 'd') {
            str[i] = c;
            i++;
            flag = 'd';
            s = STATE_DELETE;
            continue;
        } else if (s == STATE_DELETE && _delete(c) && i < 6) {
            str[i] = c;
            i++;
            continue;
        } else if (s == STATE_DELETE && i < 6) {
            cmd.command = 'w';
            cmd.k = 3;
            continue;
        } else if (s == STATE_DELETE && c == ' ') {
            s = STATE_DELETE_AND_FIRST_SPACE;
            continue;
        } else if (s == STATE_DELETE) {
            cmd.command = 'w';
            cmd.k = 3;
            continue;
        } else if (s == STATE_DELETE_AND_FIRST_SPACE && c == ' ') {
            continue;
        } else if (s == STATE_DELETE_AND_FIRST_SPACE && is_digit(c)) {
            delete_flag = 1;
            k = k * 10 + char2double(c);
            s = STATE_DELETE_AND_DIGIT;
            continue;
        } else if (s == STATE_DELETE_AND_FIRST_SPACE) {
            cmd.command = 'w';
            cmd.k = 3;
            continue;
        } else if (s == STATE_DELETE_AND_DIGIT && is_digit(c)) {
            k = k * 10 + char2double(c);
            continue;
        } else if (s == STATE_DELETE_AND_DIGIT && c == ' ') {
            s = STATE_DELETE_AND_SECOND_SPACE;
            continue;
        } else if (s == STATE_DELETE_AND_DIGIT) {
            cmd.command = 'w';
            cmd.k = 3;
            continue;
        } else if (s == STATE_DELETE_AND_SECOND_SPACE && c == ' ') {
            continue;
        } else if (s == STATE_DELETE_AND_SECOND_SPACE) {
            cmd.command = 'w';
            cmd.k = 3;
            continue;
        } else if (s == STATE_NOT_WORD && c == 'l') {
            str[i] = c;
            i++;
            flag = 'l';
            s = STATE_LENGTH;
            continue;
        } else if (s == STATE_LENGTH && _length(c) && i < 6) {
            str[i] = c;
            i++;
            continue;
        } else if (s == STATE_LENGTH && i < 6) {
            cmd.command = 'w';
            cmd.k = 4;
            continue;
        } else if (s == STATE_LENGTH && c == ' ') {
            s = STATE_LENGTH_AND_SPACE;
            continue;
        } else if (s == STATE_LENGTH) {
            cmd.command = 'w';
            cmd.k = 4;
            continue;
        } else if (s == STATE_LENGTH_AND_SPACE && c == ' ') {
            continue;
        } else if (s == STATE_LENGTH_AND_SPACE) {
            cmd.command = 'w';
            cmd.k = 4;
            continue;
        } else if (s == STATE_NOT_WORD && c == 'c') {
            str[i] = c;
            i++;
            flag = 'c';
            s = STATE_CHANGE;
            continue;
        } else if (s == STATE_CHANGE && _change(c) && i < 6) {
            str[i] = c;
            i++;
            continue;
        } else if (s == STATE_CHANGE && i < 6) {
            cmd.command = 'w';
            cmd.k = 5;
            continue;
        } else if (s == STATE_CHANGE && c == ' ') {
            s = STATE_CHANGE_AND_FIRST_SPACE;
            continue;
        } else if (s == STATE_CHANGE) {
            cmd.command = 'w';
            cmd.k = 5;
            continue;
        } else if (s == STATE_CHANGE_AND_FIRST_SPACE && c == ' ') {
            continue;
        } else if (s == STATE_CHANGE_AND_FIRST_SPACE && is_digit(c)) {
            change_flag = 1;
            k = k * 10 + char2double(c);
            s = STATE_CHANGE_AND_DIGIT;
            continue;
        } else if (s == STATE_CHANGE_AND_FIRST_SPACE) {
            cmd.command = 'w';
            cmd.k = 5;
            continue;
        } else if (s == STATE_CHANGE_AND_DIGIT && is_digit(c)) {
            k = k * 10 + char2double(c);
            continue;
        } else if (s == STATE_CHANGE_AND_DIGIT && c == ' ') {
            s = STATE_CHANGE_AND_SECOND_SPACE;
            continue;
        } else if (s == STATE_CHANGE_AND_DIGIT) {
            cmd.command = 'w';
            cmd.k = 5;
            continue;
        } else if (s == STATE_CHANGE_AND_SECOND_SPACE && c == ' ') {
            continue;
        } else if (s == STATE_CHANGE_AND_SECOND_SPACE) {
            cmd.command = 'w';
            cmd.k = 5;
            continue;
        } else if (s == STATE_BAD_WORD) {
            continue;
        } else {
            cmd.command = 'w';
            cmd.k = 6;
            s = STATE_BAD_WORD;
            continue;
        }
    }
    if (strcmp(str, "help") == 0) {
        cmd.command = 'h';
    } else if (flag == 'h') {
        cmd.command = 'w';
        cmd.k = 0;
    }
    if (strcmp(str, "print") == 0) {
        cmd.command = 'p';
    } else if (flag == 'p') {
        cmd.command = 'w';
        cmd.k = 1;
    }
    if (strcmp(str, "insert") == 0 && insert_flag_1 == 1) {
        cmd.command = 'i';
        cmd.k = k;
        if (minus_flag == 1) {
            cmd.val = val * (-1);
        } else {
            cmd.val = val;
        }
    } else if (flag == 'i') {
        cmd.command = 'w';
        cmd.k = 2;
    }
    if (strcmp(str, "delete") == 0 && delete_flag == 1) {
        cmd.command = 'd';
        cmd.k = k;
    } else if (flag == 'd') {
        cmd.command = 'w';
        cmd.k = 3;
    }
    if (strcmp(str, "length") == 0) {
        cmd.command = 'l';
    } else if (flag == 'l') {
        cmd.command = 'w';
        cmd.k = 4;
    }
    if (strcmp(str, "change") == 0 && change_flag == 1) {
        cmd.command = 'c';
        cmd.k = k;
    } else if (flag == 'c') {
        cmd.command = 'w';
        cmd.k = 5;
    }
    return cmd;
}
