#include "s21_math.h"

long double s21_floor(double x) {
  int i = 0;
  long double tmp = x < 0 ? -x : x;
  for (; i < tmp; i++)
    ;
  return x < 0 ? -i : i - (i != x);
}
