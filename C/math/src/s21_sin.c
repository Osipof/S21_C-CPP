#include "s21_math.h"

long double s21_sin(double x) {
  for (; s21_fabs(x) > S21_M_PI;
       x += x > S21_M_PI ? 2 * -S21_M_PI : 2 * S21_M_PI)
    ;
  long double res = x, tmp = x, i;
  for (i = 1.0; s21_fabs(tmp) > S21_EPS; i++) {
    res += tmp = (-tmp) * x * x / ((2 * i + 1) * (2 * i));
  }
  return res;
}
