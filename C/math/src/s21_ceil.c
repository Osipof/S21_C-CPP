#include "s21_math.h"

long double s21_ceil(double x) {
  int i = 0;
  long double tmp = x < 0 ? -x : x;
  for (; i < tmp; i++)
    ;
  return x == S21_NAN ? S21_NAN : x < 0 ? -i + (-i != x) : i;
}
