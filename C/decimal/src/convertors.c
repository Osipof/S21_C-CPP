#include <math.h>
#include <stdbool.h>

#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int codeError = 0;
  if (dst) {
    int sign = (s21_getSign(src) ? -1 : 1);
    src.bits[3] = s21_reset_bit(src.bits[3], 31);
    int mantiss = src.bits[3] >> 16;
    *dst = src.bits[0] / pow(10, mantiss) * sign;
  } else {
    codeError = 1;
  }
  return codeError;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 1;
  s21_truncate(src, &src);
  if (src.bits[1] == 0 && src.bits[2] == 0) {
    *dst = src.bits[0];
    if (s21_getSign(src)) {
      *dst *= -1;
    }
    res = 0;
  }
  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int codeError = 0;
  if (is_inf(src) || is_nan(src)) {
    codeError = 1;
  } else if (dst) {
    int sign = 0;
    if (src < 0) {
      src = -src;
      sign = 1;
    }
    long int new = (long int)src;
    long int mantiss = 0;
    while (src - ((float)new / (long int)(pow(10, mantiss))) != 0) {
      mantiss++;
      new = src *(long int)(pow(10, mantiss));
    }
    s21_decimal_init(dst);
    bool temp[96] = {0};
    int m = 0;
    // printf("%ld\n", new);
    while (new >= 1) {
      if (new % 2 == 1) {
        temp[m] = 1;
      }
      m++;
      new /= 2;
    }
    int k = 95;
    for (int i = 2; i >= 0; i--) {
      for (int j = 31; j >= 0; j--) {
        dst->bits[i] = (dst->bits[i] << 1) + temp[k--];
      }
    }

    if (sign) {
      dst->bits[3] |= MINUS_SIGN;
    }
    dst->bits[3] += mantiss << 16;
  } else {
    codeError = 1;
  }
  return codeError;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int codeError = 0;
  if (dst) {
    s21_decimal_init(dst);
    if (src < 0) {
      dst->bits[3] |= MINUS_SIGN;
    }
    dst->bits[0] = src < 0 ? -src : src;
  } else {
    codeError = 1;
  }
  return codeError;
}
