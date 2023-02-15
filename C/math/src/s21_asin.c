#include "s21_math.h"

long double s21_asin(double x) {
  long double tmp = x, res = S21_NAN, i;

  if (-1 <= x && x <= 1) {
    if (x == 1 || x == -1) {
      res = S21_M_PI_2 * x;
    } else {
      for (i = 1, res = x; s21_fabs(tmp) > S21_EPS; i++) {
        res += tmp *= x * x * (2 * i - 1) * (2 * i - 1) / ((2 * i + 1) * 2 * i);
      }
    }
  }
  return res;
}
