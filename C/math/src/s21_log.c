#include "s21_math.h"

long double s21_log(double x) {
  long double sign = 1, pow = 0, res, tmp;

  x < 0 ? x = -x, sign = -sign : 0;

  while ((x >= 10) || (x < 1 && x > 0)) {
    if (1 > x && x > 0) {
      x *= 10;
      pow -= 1;
    } else {
      x *= 0.1;
      pow += 1;
    }
  }

  x *= sign / 10;

  if (x < 0) {
    res = -S21_NAN;
  } else if (x == 0) {
    res = -S21_INF;
  } else {
    res = --x;
    tmp = x;
    for (int i = 1; s21_fabs(res) > S21_EPS;
         i++, res *= -x * (i - 1) / i, tmp += res)
      ;
    res = tmp + (pow + 1) * S21_M_LN10;
  }

  return (x == 1) ? 0 : res;
}