#include "s21_math.h"

long double s21_exp(double x) {
  long double res = 1, tmp = 1;
  int flag = 0;
  x < 0 ? x = -x, flag = 1 : 0;

  for (int i = 0; s21_fabs(res) > S21_EPS; i++, res *= x / i, tmp += res) {
    if (tmp > S21_MAX_DOUBLE) {
      tmp = S21_INF;
      break;
    }
  }
  flag ? tmp = 1.0 / tmp : 0;
  return tmp;
}
