#include <stdio.h>

typedef enum {
    OUT_OF_THE_WORD, // 0
    NOT_CONSONANT_LETTER, // 1
    J_G_H, // 2
    THIS_WORD_IS_NOT_GOOD, // 3
    NOT_CONSONANT_LETTER_AFTER_GOOD_CONSISTENT // 4
} state;

typedef unsigned int set;

int letter_to_index(int c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else {
        return -1;
    }
}

int letter_to_set(int c) {
    int index = letter_to_index(c);
    if (index == -1) {
        return 0;
    }
    return ((set)1) << index;
}

char index_to_letter(int c) {
    return c + 'a';
}

int is_separator(int c) {
    return c == ' ' || c == ',' || c == '\t' || c == '\n' || c == EOF;
}

int is_letter_in_set(set set, int c) {
    int g = letter_to_set(c);
    if (g != 0) {
        return g == (set & g);
    } else {
        return 0;
    }
}

int main() {
    set j_g_h = letter_to_set('j') | letter_to_set('g') | letter_to_set('h');
    set consonant = letter_to_set('b') | letter_to_set('c') | letter_to_set('d') | letter_to_set('f') | letter_to_set('g') | letter_to_set('h') | letter_to_set('j') | letter_to_set('k') | letter_to_set('l') | letter_to_set('m') | letter_to_set('n') | letter_to_set('q') | letter_to_set('r') | letter_to_set('s') | letter_to_set('t') | letter_to_set('v') | letter_to_set('w') | letter_to_set('x') | letter_to_set('z');
    int c = 0;
    int flag_yes = 1;
    state s = OUT_OF_THE_WORD;
    while (1) {
        c = getchar();
        if (c == '\n' || c == EOF) {
            flag_yes = 0;
        }
        if (s == OUT_OF_THE_WORD && is_separator(c)) {
        } else if (s == OUT_OF_THE_WORD && !is_letter_in_set(consonant, c) && !is_separator(c)) {
            s = NOT_CONSONANT_LETTER;
        } else if (s == OUT_OF_THE_WORD && is_letter_in_set(j_g_h, c)) {
            s = J_G_H;
        } else if (s == OUT_OF_THE_WORD && is_letter_in_set(consonant, c) && !is_letter_in_set(j_g_h, c)) {
            s = THIS_WORD_IS_NOT_GOOD;
        } else if (s == NOT_CONSONANT_LETTER && is_separator(c)) {
            s = OUT_OF_THE_WORD;
        } else if (s == NOT_CONSONANT_LETTER && !is_letter_in_set(consonant, c) && !is_separator(c)) {
        } else if (s == NOT_CONSONANT_LETTER && is_letter_in_set(j_g_h, c)) {
            s = J_G_H;
        } else if (s == J_G_H && is_separator(c)) {
            s = OUT_OF_THE_WORD;
            if (flag_yes == 0) {
                printf("Yes!\n");
                flag_yes = 1;
            }
        } else if (s == J_G_H && is_letter_in_set(j_g_h, c)) {
        } else if (s == J_G_H && is_letter_in_set(consonant, c) && !is_letter_in_set(j_g_h, c)) {
            s = THIS_WORD_IS_NOT_GOOD;
        } else if (s == J_G_H && !is_letter_in_set(consonant, c) && !is_separator(c)) {
            s = NOT_CONSONANT_LETTER_AFTER_GOOD_CONSISTENT;
        } else if (s == THIS_WORD_IS_NOT_GOOD && is_separator(c)) {
            s = OUT_OF_THE_WORD;
        } else if (s == THIS_WORD_IS_NOT_GOOD && !is_separator(c)) {
        } else if (s == NOT_CONSONANT_LETTER_AFTER_GOOD_CONSISTENT && is_separator(c)) {
            s = OUT_OF_THE_WORD;
            if (flag_yes == 0) {
                printf("Yes!\n");
                flag_yes = 1;
            }
        } else if (s == NOT_CONSONANT_LETTER_AFTER_GOOD_CONSISTENT && is_letter_in_set(j_g_h, c)) {
            s = J_G_H;
        } else if (s == NOT_CONSONANT_LETTER_AFTER_GOOD_CONSISTENT && is_letter_in_set(consonant, c) && !is_letter_in_set(j_g_h, c)) {
            s = THIS_WORD_IS_NOT_GOOD;
        } else if (s == NOT_CONSONANT_LETTER_AFTER_GOOD_CONSISTENT && !is_separator(c) && !is_letter_in_set(consonant, c)) {
        }
        if (flag_yes == 0 && (c == '\n' || c == EOF)) {
                printf("No!\n");
            }
        if (c == EOF) {
            break;
        }
    }
}
