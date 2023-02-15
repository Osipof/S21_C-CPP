#include "s21_math.h"

long double s21_atan(double x) {
  return x < 0 ? -1 * s21_acos(1.0 / (s21_sqrt(1.0 + x * x)))
               : s21_acos(1.0 / (s21_sqrt(1.0 + x * x)));
}