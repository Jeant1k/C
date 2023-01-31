#include <stdio.h>

int num_of_dig (int dig) {
  int k = 0;
  while (dig != 0) {
    k += 1;
    dig /= 10;
  }
  return k;
}

int power (int a, int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return power (a, n-1) * a;
	else {
		int b = power (a, n/2);
		return b * b;
	}
}

int modul (int a) {
  if (a < 0) {
    return a * -1;
  } else {
    return a;
  }
}

int main() {
  int dig = 0;
  int n = 0;
  int a = 0;
  int b = 0;
  int c = 0;
  while (scanf("%d", &dig) == 1) {
    dig = modul(dig);
    n = num_of_dig(dig) - 1;

    int res = 0;

    for (int i = 2; i <= n; i++) {
      
      int pwr = power(10, i);

      a = (dig / pwr) % 10;
      b = (dig / (pwr / 10)) % 10;
      c = (dig / (pwr / 100)) % 10;

      if (a == (b + c)) {
        res = res * 10 + a;
      }
    }
    printf("%d\n", res);
  }
}
