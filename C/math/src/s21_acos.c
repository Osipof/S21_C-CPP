#include "s21_math.h"

long double s21_acos(double x) {
  return (1 >= x && x >= -1) ? (S21_M_PI / 2.0 - s21_asin(x)) : S21_NAN;
}