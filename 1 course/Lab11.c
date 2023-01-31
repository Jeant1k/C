#include <stdio.h>

typedef enum {
  STATE_NOT_A_DIGIT, // 0
  STATE_SIGN, // 1
  STATE_DIGIT, // 2
  STATE_WORD // 3
} state;

int interpreter (int a) {
  return a - '0';
}

int is_separator (char c) {
  if (c == ' ' || c == ',' || c == '\t' || c == '\n' || c == EOF) {
    return 1;
  } else {
    return 0;
  }
}

int is_digit (int dig) {
  if (dig >= '0' && dig <= '9') {
    return 1;
  }
  return 0;
}

int main() {
  int c = 0;
  char sign = '\0';
  long long n = 0;
  state s = STATE_NOT_A_DIGIT;
  while ((c = getchar()) != EOF) {
    if (s == STATE_NOT_A_DIGIT && is_separator(c) == 1) {
      printf("%c", c);
    } else if (s == STATE_NOT_A_DIGIT && (c == '+' || c == '-')) {
      s = STATE_SIGN;
      if (c == '+') {
        sign = '+';
      } else {
        sign = '-';
      }
    } else if (s == STATE_NOT_A_DIGIT && is_digit(c) == 1) {
      s = STATE_DIGIT;
      n = n * 10 + interpreter(c);
    } else if (s == STATE_NOT_A_DIGIT && is_digit(c) == 0 && is_separator(c) == 0) {
      s = STATE_WORD;
      printf("%c", c);
    } else if (s == STATE_SIGN && is_separator(c) == 1) {
      s = STATE_NOT_A_DIGIT;
      printf("%c%c", sign, c);
      sign = '\0';
    } else if (s == STATE_SIGN && is_digit(c) == 1) {
      s = STATE_DIGIT;
      n = n * 10 + interpreter(c);
    } else if (s == STATE_SIGN && is_digit(c) == 0 && is_separator(c) == 0) {
      s = STATE_WORD;
      printf("%c%c", sign, c);
      sign = '\0';
    } else if (s == STATE_DIGIT && is_separator(c) == 1) {
      s = STATE_NOT_A_DIGIT;
      if (n > 2147483647) {
        printf("%c%lld%c", sign, n, c);
      } else {
        printf("%c", c);
      }
      n = 0;
      sign = '\0';
    } else if (s == STATE_DIGIT && is_digit(c) == 1) {
      n = n * 10 + interpreter(c);
    } else if (s == STATE_DIGIT && is_digit(c) == 0 && is_separator(c) == 0) {
      s = STATE_WORD;
      printf("%c%lld%c", sign, n, c);
      n = 0;
      sign = '\0';
    } else if (s == STATE_WORD && is_separator(c) == 1) {
      s = STATE_NOT_A_DIGIT;
      printf("%c", c);
    } else if (s == STATE_WORD && is_separator(c) == 0) {
      printf("%c", c);
    }
  }
}
