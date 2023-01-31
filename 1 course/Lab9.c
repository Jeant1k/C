#include <stdio.h>

int modul(int dig) {
  if (dig < 0 ) {
    dig *= -1;
  }
  return dig;
}

int minim(int a, int b) {
  if (a <= b) {
    return a;
  } else {
    return b;
  }
}

int maxim(int a, int b) {
  if (a >= b ) {
    return a;
  } else {
    return b;
  }
}

int remainder_of_the_division(int dig, int div) {
  return (div + dig % div) % div;
}

int signal(int a) {
  if (a < 0) {
    return -1;
  } else if (a == 0) {
    return 0;
  } else {
    return 1;
  }
}

int i_k_plus_1(int i_k, int j_k, int l_k, int k) {
  return remainder_of_the_division(minim(i_k + j_k, i_k + l_k) * (k + 1), 30);
}

int j_k_plus_1(int i_k, int j_k, int l_k, int k) {
  return j_k + remainder_of_the_division(l_k * signal(j_k), 20) + remainder_of_the_division(k * signal(i_k), 10);
}

int l_k_plus_1(int i_k, int j_k, int l_k, int k) {
  return remainder_of_the_division(maxim(maxim(i_k * j_k, i_k * l_k), j_k * l_k), 30);
}


int main() {
  int i_k = 26;
  int j_k = 8;
  int l_k = -3;
  int k = 0;
  while (k <= 50) {
    if ((((i_k - 10) * (i_k - 10) + (j_k - 10) * (j_k - 10)) < 100) && (((i_k - 10) * (i_k - 10) + (j_k - 10) * (j_k - 10)) > 25)) {
      printf("Yess! You are sniper!\ni = %d\nj = %d\nl = %d\nk = %d\n", i_k, j_k, l_k, k);
      break;
    } else {
      if (k == 50) {
        printf("Loser\ni = %d\nj = %d\nl = %d\nk = %d\n\n", i_k, j_k, l_k, k);
      }
      int i_k_old = i_k;
      int j_k_old = j_k;
      int l_k_old = l_k;
      i_k = i_k_plus_1(i_k, j_k, l_k, k);
      j_k = j_k_plus_1(i_k_old, j_k_old, l_k_old, k);
      l_k = l_k_plus_1(i_k_old, j_k_old, l_k_old, k);
      k += 1;
    }
  }
  if (k == 51) {
    printf("You tried but you failed!\n");
  }
}
