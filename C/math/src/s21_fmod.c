#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double res = y == 0   ? -S21_NAN
                    : x == y ? 0
                             : s21_fabs(x),
              tmpy = s21_fabs(y);
  while (res > tmpy) res -= tmpy;
  return x < 0 ? -res : res;
}
