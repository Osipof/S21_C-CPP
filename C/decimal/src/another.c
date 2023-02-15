#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (!result) {
    error = 1;
  } else {
    s21_decimal_init(result);
    s21_decimal value_truncate = {{0}};
    s21_decimal ostatochek = {{0}};
    s21_decimal value_copy = {{0}};
    int sign = s21_getSign(value);
    s21_copy(&value_copy, value);
    s21_removeBit(&value_copy, 127);
    s21_truncate(value_copy, &value_truncate);
    s21_sub(value_copy, value_truncate, &ostatochek);
    value_truncate = s21_banking_round(value_truncate, ostatochek);
    if (sign) s21_negate(value_truncate, &value_truncate);
    s21_copy(result, value_truncate);
  }
  return error;
}

s21_decimal s21_banking_round(s21_decimal value_without_fractional,
                              s21_decimal fractional) {
  s21_decimal five = {{5, 0, 0, 65536}};
  s21_decimal result = {{0}};
  if (s21_is_equal(fractional, five)) {
    if (s21_decimal_even(value_without_fractional)) {
      s21_copy(&result, value_without_fractional);
    } else {
      s21_decimal add_one_bit = {{1, 0, 0, 0}};
      s21_add(value_without_fractional, add_one_bit, &result);
    }
  } else if (s21_is_greater(fractional, five)) {
    s21_decimal add_one_bit = {{1, 0, 0, 0}};
    s21_add(value_without_fractional, add_one_bit, &result);
  } else {
    s21_copy(&result, value_without_fractional);
  }
  return result;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  s21_copy(result, value);
  if ((value.bits[3] & (1u << 31)) == 0) {
    result->bits[3] |= (1u << 31);
  } else {
    result->bits[3] &= ~(1u << 31);
  }

  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal_init(result);
  int error = 0;
  int sign = s21_getSign(value);
  if (s21_getDegree(value) > 28) {
    error++;
  } else {
    while (s21_getDegree(value) > 0) {
      s21_decreaseDegree(&value, 0);
    }
    s21_copy(result, value);
    if (sign) s21_setBit(result, 127);
  }
  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal_init(result);
  int error = 0;
  s21_decimal one = {{1, 0, 0, 0}};
  int sign = s21_getSign(value);
  error = s21_truncate(value, &value);

  if (sign) {
    s21_add_logic(value, one, &value);
  }
  s21_copy(result, value);

  if (sign) s21_setBit(result, 127);
  return error;
}
