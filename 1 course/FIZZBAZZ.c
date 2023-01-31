#include <stdio.h>

int main() {
  for(int i = 1; i <= 100; i++) {
    if (i % 3 == 0 && i % 5 != 0) {
      printf("FIZZ\n");
    }
    if (i % 3 != 0 && i % 5 == 0) {
      printf("BUZZ\n");
    }
    if (i % 3 == 0 && i % 5 == 0) {
      printf("FIZZBUZZ\n");
    }
    if (i % 3 != 0 && i % 5 != 0) {
      printf("%d\n", i);
    }
  }
}
