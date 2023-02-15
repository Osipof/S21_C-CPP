#include "s21_math.h"

long double s21_sqrt(double x) {
  long double tmp = 0, res = x < 0 ? -S21_NAN : x / 2;
  while (s21_fabs(res - tmp) > S21_EPS) {
    tmp = res;
    res = (x / tmp + tmp) / 2;
  }

  return res;
}
