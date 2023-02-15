#include "s21_math.h"

long double s21_cos(double x) {
  for (; s21_fabs(x) > S21_M_PI;
       x += x > S21_M_PI ? -2 * S21_M_PI : 2 * S21_M_PI)
    ;

  return s21_sin(S21_M_PI_2 - x);
}
