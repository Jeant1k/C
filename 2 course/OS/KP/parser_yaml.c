#include "parser_yaml.h"

static bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

static int char2int(char c) {
    return c - '0';
}

static int str2int(char str[]) {
    
    int res = 0;
    for (int i = 0; i < LENGTH_BARRIER_NAME; i++) {
        if (str[i] == '\0') {
            break;
        }
        res = res * 10 + char2int(str[i]);
    }
    
    return res;
    
}

int get_size_dag(char file_name[]) {

    FILE *my_file;
    if ((my_file = fopen(file_name, "r")) == NULL) {
        printf("Не удалось открыть файл.\n");
        return 0;
    }
    
    char c;
    state_1 s = STATE_NOT_PATH;
    int max_child = 0;
    int child = 0;
    while ((c = fgetc(my_file)) != EOF) {
        if (s == STATE_NOT_PATH && c == 'c') {
            s = STATE_C_1;
        } else if (s == STATE_NOT_PATH) {
            continue;
        } else if (s == STATE_C_1 && c == 'h') {
            s = STATE_H_1;
        } else if (s == STATE_C_1) {
            s = STATE_NOT_PATH;
        } else if (s == STATE_H_1 && c == 'i') {
            s = STATE_I_1;
        } else if (s == STATE_H_1) {
            s = STATE_NOT_PATH;
        } else if (s == STATE_I_1 && c == 'l') {
            s = STATE_L_1;
        } else if (s == STATE_I_1) {
            s = STATE_NOT_PATH;
        } else if (s == STATE_L_1 && c == 'd') {
            s = STATE_D_1;
        } else if (s == STATE_L_1) {
            s = STATE_NOT_PATH;
        } else if (s == STATE_D_1 && c == ':') {
            s = STATE_COLON_1;
        } else if (s == STATE_D_1) {
            s = STATE_NOT_PATH;
        } else if (s == STATE_COLON_1 && c == ' ') {
            s = STATE_SPACE_1;
        } else if (s == STATE_COLON_1) {
            s = STATE_NOT_PATH;
        } else if (s == STATE_SPACE_1 && is_digit(c)) {
            s = STATE_DIG_1;
            child = child * 10 + char2int(c);
        } else if (s == STATE_SPACE_1) {
            s = STATE_NOT_PATH;
        } else if (s == STATE_DIG_1 && is_digit(c)) {
            child = child * 10 + char2int(c);
        } else if (s == STATE_DIG_1) {
            s = STATE_NOT_PATH;
            if (child > max_child)
                max_child = child;
            child = 0;
        }
    }

    fclose(my_file);
    
    return max_child;
    
}

bool parsing_file_writing_to_vector(vector_yaml *v, char file_name[]) {
    
    FILE *my_file;
    if ((my_file = fopen(file_name, "r")) == NULL) {
        printf("Не удалось открыть файл.\n");
        return false;
    }
    
    char c;
    int id = 0;
    int child_id = 0;
    int i_child_id = 0;
    char path[LENGTH_PATH] = {'\0'};
    int i_path = 0;
    char barrier_name[LENGTH_BARRIER_NAME] = {'\0'};
    int i_barrier_name = 0;
    int i_buf = 0;
    state_2 s = STATE_NOT_DATA;

    while ((c = fgetc(my_file)) != EOF) {
        if (s == STATE_NOT_DATA && c == 'i') {
            s = STATE_I_2;
        } else if (s == STATE_I_2 && c == 'd') {
            s = STATE_D_2;
        } else if (s == STATE_I_2) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_D_2 && c == ':') {
            s = STATE_COLON_2;
        } else if (s == STATE_D_2) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_COLON_2) {
            s = STATE_SPACE_2;
        } else if (s == STATE_SPACE_2 && is_digit(c)) {
            s = STATE_DIG_2;
            id = char2int(c);
        } else if (s == STATE_SPACE_2) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_DIG_2 && is_digit(c)) {
            id = id * 10 + char2int(c);
        } else if (s == STATE_DIG_2) {
            s = STATE_NOT_DATA;
            v -> buf[i_buf].id = id;
            id = 0;
        } else if (s == STATE_NOT_DATA && c == 'c') {
            s = STATE_C_2;
        } else if (s == STATE_C_2 && c == 'h') {
            s = STATE_H_2;
        } else if (s == STATE_C_2) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_H_2 && c == 'i') {
            s = STATE_I_3;
        } else if (s == STATE_H_2) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_I_3 && c == 'l') {
            s = STATE_L_2;
        } else if (s == STATE_I_3) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_L_2 && c == 'd') {
            s = STATE_D_3;
        } else if (s == STATE_L_2) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_D_3 && c == ':') {
            s = STATE_COLON_3;
        } else if (s == STATE_D_3) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_COLON_3) {
            s = STATE_SPACE_3;
        } else if (s == STATE_SPACE_3 && is_digit(c)) {
            s = STATE_DIG_3;
            child_id = char2int(c);
        } else if (s == STATE_SPACE_3) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_DIG_3 && is_digit(c)) {
            child_id = child_id * 10 + char2int(c);
        } else if (s == STATE_DIG_3) {
            s = STATE_NOT_DATA;
            v -> buf[i_buf].child_ids[i_child_id] = child_id;
            i_child_id++;
            child_id = 0;
        } else if (s == STATE_NOT_DATA && c == 'p') {
            s = STATE_P_2;
        } else if (s == STATE_P_2 && c == 'a') {
            s = STATE_A_2;
        } else if (s == STATE_P_2) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_A_2 && c == 't') {
            s = STATE_T_2;
        } else if (s == STATE_A_2) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_T_2 && c == 'h') {
            s = STATE_H_3;
        } else if (s == STATE_T_2) {
            s = STATE_NOT_DATA;
        }else if (s == STATE_H_3 && c == ':') {
            s = STATE_COLON_4;
        } else if (s == STATE_H_3) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_COLON_4) {
            s = STATE_SPACE_4;
        } else if (s == STATE_SPACE_4 && c == '"') {
            s = STATE_QUOTES_1;
        } else if (s == STATE_SPACE_4) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_QUOTES_1) {
            s = STATE_PATH;
            path[i_path] = c;
            i_path++;
        } else if (s == STATE_PATH && c != '"') {
            path[i_path] = c;
            i_path++;
        } else if (s == STATE_PATH) {
            s = STATE_NOT_DATA;
            for (int i = 0; i < LENGTH_PATH; i++) {
                v -> buf[i_buf].path[i] = path[i];
            }
            i_buf++;
            i_path = 0;
            i_child_id = 0;
            for (int i = 0; i < LENGTH_PATH; i++) {
                path[i] = '\0';
            }
        } else if (s == STATE_NOT_DATA && c == 'b') {
            s = STATE_B_1;
        } else if (s == STATE_B_1 && c == 'a') {
            s = STATE_A_1;
        } else if (s == STATE_B_1) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_A_1 && c == 'r') {
            s = STATE_R_1;
        } else if (s == STATE_A_1) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_R_1 && c == 'r') {
            s = STATE_R_2;
        } else if (s == STATE_R_1) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_R_2 && c == 'i') {
            s = STATE_I_4;
        } else if (s == STATE_R_2) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_I_4 && c == 'e') {
            s = STATE_E_1;
        } else if (s == STATE_I_4) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_E_1 && c == 'r') {
            s = STATE_R_3;
        } else if (s == STATE_E_1) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_R_3 && c == ':') {
            s = STATE_COLON_5;
        } else if (s == STATE_R_3) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_COLON_5) {
            s = STATE_SPACE_5;
        } else if (s == STATE_SPACE_5 && c == '"') {
            s = STATE_QUOTES_2;
        } else if (s == STATE_SPACE_5) {
            s = STATE_NOT_DATA;
        } else if (s == STATE_QUOTES_2) {
            s = STATE_BARRIER_NAME;
            barrier_name[i_barrier_name] = c;
            i_barrier_name++;
        } else if (s == STATE_BARRIER_NAME && c != '"') {
            barrier_name[i_barrier_name] = c;
            i_barrier_name++;
        } else if (s == STATE_BARRIER_NAME) {
            s = STATE_NOT_DATA;
            v -> buf[i_buf - 1].barrier = true;
            v -> buf[i_buf - 1].barrier_name = str2int(barrier_name);
            i_barrier_name = 0;
            for (int i = 0; i < LENGTH_BARRIER_NAME; i++) {
                barrier_name[i] = '\0';
            }
        }
    }

    fclose(my_file);
    
    return true;
    
}
