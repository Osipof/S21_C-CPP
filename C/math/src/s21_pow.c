#include "s21_math.h"

long double s21_pow(double base, double exp) {
  return s21_exp(s21_log(base) * exp);
}
