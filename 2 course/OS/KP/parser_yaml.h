// Гарантируется, что данные в файле .yaml написаны корректно. Проверок на правильность записи информации нет.

#ifndef _PARSER_YAML_H_
#define _PARSER_YAML_H_

#include <stdio.h>
#include <stdbool.h>
#include "vector_yaml.h"

typedef enum {
    STATE_NOT_PATH,  // 0
    STATE_C_1,  // 1
    STATE_H_1,  // 2
    STATE_I_1,  // 3
    STATE_L_1,  // 4
    STATE_D_1,  // 5
    STATE_COLON_1,  // 6
    STATE_SPACE_1,  // 7
    STATE_DIG_1,  // 8
} state_1;

typedef enum {
    STATE_NOT_DATA,  // 0
    STATE_I_2,  // 1
    STATE_D_2,  // 2
    STATE_COLON_2,  // 3
    STATE_SPACE_2,  // 4
    STATE_DIG_2,  // 5
    STATE_C_2,  // 6
    STATE_H_2,  // 7
    STATE_I_3,  // 8
    STATE_L_2,  // 9
    STATE_D_3,  // 10
    STATE_COLON_3,  // 11
    STATE_SPACE_3,  // 12
    STATE_DIG_3,  // 13
    STATE_P_2,  // 14
    STATE_A_2,  // 15
    STATE_T_2,  // 16
    STATE_H_3,  // 17
    STATE_COLON_4,  // 18
    STATE_SPACE_4,  // 19
    STATE_QUOTES_1,  // 20
    STATE_PATH,  // 21
    STATE_B_1,  // 22
    STATE_A_1,  // 23
    STATE_R_1,  // 24
    STATE_R_2,  // 25
    STATE_I_4,  // 26
    STATE_E_1,  // 27
    STATE_R_3,  // 28
    STATE_COLON_5,  // 29
    STATE_SPACE_5,  // 30
    STATE_QUOTES_2,  // 31
    STATE_BARRIER_NAME,  // 32
} state_2;

int get_size_dag(char file[]);
bool parsing_file_writing_to_vector(vector_yaml *v, char file_name[]);
bool append_end_jobs(vector_yaml *v);

#endif
