#include <stdio.h>

int num_of_div(dig) {
  int k = 0;
  for (int i = 0; i <= dig; i++) {
    if (dig % i == 0) {
      k += 1;
    }
  }
  return k;
}

int main() {
  int a = 10;
  int k = 0;
  k = num_of_div(a);
  printf("Количество делителей числа %d = %d", a, k);
}
