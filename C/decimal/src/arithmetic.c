#include <limits.h>
#include <math.h>

#include "s21_decimal.h"

#define ERROR_BIG 1
#define ERROR_SMALL 2
#define ERROR_NAN 3

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int sign_1 = s21_getSign(value_1);
  int sign_2 = s21_getSign(value_2);

  if (sign_1 ^ sign_2) {
    // знак минус меняем на плюс, и ставим на второе место
    if (sign_1) {
      s21_negate(value_1, &value_1);
      error = s21_sub(value_2, value_1, result);
    }
    if (sign_2) {
      s21_negate(value_2, &value_2);
      error = s21_sub(value_1, value_2, result);
    }
  } else {
    // if если 1 децимал равен decimal max а второй не равен 0
    // степень равна нулю, знак
    if (s21_check_add_overflow(value_1, value_2)) {
      error = !sign_1 ? ERROR_BIG : ERROR_SMALL;
    } else {
      s21_normalization(&value_1, &value_2);
      error = s21_add_logic(value_1, value_2, result);
      s21_normalization_result(value_1, result, sign_1);
    }
  }

  return error;
}

int s21_check_add_overflow(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  s21_decimal decimal_max = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  if (!s21_getDegree(value_1) && s21_is_equal_logic(decimal_max, value_1) &&
      !s21_isZero(value_2))
    flag = 1;
  if (!s21_getDegree(value_2) && s21_is_equal_logic(decimal_max, value_2) &&
      !s21_isZero(value_1))
    flag = 1;

  return flag;
}

int s21_add_logic(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result) {
  int error = 0;
  int next = 0, prev = 0;
  int sign_1 = s21_getSign(value_1);
  s21_decimal_init(result);

  for (int i = 0; i < 96; i++) {
    prev = next;
    int bit1 = s21_getBit(value_1, i);
    int bit2 = s21_getBit(value_2, i);
    result->bits[i / 32] += ((bit1 + bit2 + prev) % 2) * ((int)pow(2, i % 32));
    next = (bit1 & bit2) | (bit1 & prev) | (bit2 & prev);
  }
  if (next && !sign_1) error = ERROR_BIG;
  if (next && sign_1) error = ERROR_SMALL;
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int sign_1 = s21_getSign(value_1);
  int sign_2 = s21_getSign(value_2);

  if (sign_1 ^ sign_2) {
    s21_negate(value_2, &value_2);
    error = s21_add(value_1, value_2, result);
  } else {
    if (s21_is_equal(value_1, value_2)) {
      for (int i = 0; i < 4; i++) {
        result->bits[i] = 0;
      }
    } else {
      if (sign_1 &&
          sign_2) {  // если оба значения отрицательные, меняем местами
        value_crutch(&value_1, &value_2);
      }
      s21_normalization(&value_1, &value_2);

      if (s21_is_greater(value_1, value_2)) {
        s21_sub_results(value_1, value_2, result);

      } else {
        s21_sub_results(value_2, value_1, result);
        s21_negate(*result, result);
      }
      s21_setDegree(result, s21_getDegree(value_1));
    }
  }
  return error;
}

void s21_sub_results(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  if (value_1.bits[0] < value_2.bits[0]) {  // вычитание младших битов
    if (value_1.bits[1] != 0) {
      value_1.bits[1] -= 1u;  // вычитаем один ансайн инт( один бит)
      result->bits[0] = UINT_MAX - value_2.bits[0] + value_1.bits[0];
    } else {
      value_1.bits[2] -= 1u;  // вычитаем один ансайн инт( один бит) из верхних(
                              // так как средние равны 0)
      value_1.bits[1] = UINT_MAX;
      result->bits[0] = UINT_MAX - value_2.bits[0] + value_1.bits[0];
    }
  } else {
    result->bits[0] = value_1.bits[0] - value_2.bits[0];
  }
  if (value_1.bits[1] < value_2.bits[1]) {  // вычитание средних битов
    if (value_1.bits[2] != 0) {
      value_1.bits[2] -= 1u;  // вычитаем один ансайн инт( один бит)
      result->bits[1] = UINT_MAX - value_2.bits[1] + value_1.bits[1];
    }
  } else {
    result->bits[1] = value_1.bits[1] - value_2.bits[1];
  }  // вычитание старших битов
  result->bits[2] = value_1.bits[2] - value_2.bits[2];
  result->bits[3] = value_1.bits[3];
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int sign = 0;
  int flag = 0;
  flag = div_to_zero(value_2);
  if (flag == 0) {
    error = ERROR_NAN;
  } else {
    // s21_normalization(&value_1, &value_2);
    if (s21_getSign(value_1) ^ s21_getSign(value_2)) {
      s21_removeBit(&value_1, 127);
      s21_removeBit(&value_2, 127);
      sign = 1;
    }
    if (s21_is_equal_logic(value_1, value_2)) {
      result->bits[0] = 1;
    } else {
      if (value_2.bits[0] == 1 && value_2.bits[1] == 0 &&
          value_2.bits[2] == 0) {
        s21_copy(result, value_1);
      } else {
        s21_decimal add_1_bit = {{1, 0, 0, 0}};
        while (s21_is_greater_logic(value_1, value_2)) {
          // printf("Hey");
          s21_sub(value_1, value_2, &value_1);
          s21_add_logic(*result, add_1_bit, result);
          // printdecimal(value_1);
        }
        if (s21_is_equal(value_1, value_2)) result->bits[0] += 1;
        if (sign == 1) s21_negate(*result, result);
      }
    }
  }
  return error;
}

// int s21_div_10(s21_decimal value_1, s21_decimal *result) {
//   int error = 0;
//   int sign = s21_getSign(value_1);
//   s21_decimal value_2 = {10, 0, 0, 0};
//   s21_decimal add_1_bit = {1, 0, 0, 0};
//   while (s21_is_greater_logic(value_1, value_2)) {
//     s21_sub_results(value_1, value_2, &value_1);
//     s21_add_logic(*result, add_1_bit, result);
//   }
//   if (s21_is_equal_logic(value_1, value_2)) result->bits[0] += 1;
//   if (sign == 1) s21_negate(*result, result);

//   return error;
// }

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int flag = 0;
  flag = div_to_zero(value_2);
  if (flag == 0) {
    error = ERROR_NAN;
  } else {
    // if (s21_getSign(value_1) ^ s21_getSign(value_2)) {
    //   sign = 1;
    // }
    if (s21_is_equal(value_1, value_2)) {
      zero_result(result);
    } else {
      while (s21_is_greater(value_1, value_2)) {
        // printf("HELLO");
        s21_sub(value_1, value_2, &value_1);
      }
      if (s21_is_equal(value_1, value_2)) {
        zero_result(result);
      } else {
        *result = value_1;
      }
    }
  }
  return error;
}

int div_to_zero(s21_decimal value_2) {
  int flag = 0;
  for (int i = 0; i < 96; i++) {
    if (s21_getBit(value_2, i) != 0) {
      flag = 1;
    }
  }
  return flag;
}

void zero_result(s21_decimal *result) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
}

void s21_copy(s21_decimal *dst, s21_decimal src) {
  s21_decimal_init(dst);
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src.bits[i];
  }
}

int s21_shift(s21_decimal *decimal, int pos) {
  int codeError = 0;
  s21_decimal temp;
  s21_decimal_init(&temp);
  for (int i = 0; i < 96; i++) {
    if (s21_getBit(*decimal, i) == 1) {
      if (i + pos >= 96) {
        codeError = 1;
        break;
      }
      s21_setBit(&temp, i + pos);
    }
  }
  s21_copy(decimal, temp);
  return codeError;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int codeError = 0;
  s21_decimal_init(result);
  if (result) {
    s21_decimal_init(result);
    int sign_1 = s21_getSign(value_1);
    int sign_2 = s21_getSign(value_2);
    for (int i = 0; i < 96; i++) {
      int y = s21_getBit(value_2, i);
      if (y != 0) {
        s21_decimal temp_value_1;
        s21_copy(&temp_value_1, value_1);
        temp_value_1.bits[3] = 0;
        if (s21_shift(&temp_value_1, i)) {
          if (sign_1 == sign_2) {
            // Большое положительное число
            codeError = ERROR_BIG;
          }
          if (sign_1 != sign_2) {
            // Слишком маленькое число
            codeError = ERROR_SMALL;
          }
        }
        s21_decimal temp_result;
        s21_copy(&temp_result, *result);
        s21_decimal_init(result);
        s21_add_logic(temp_result, temp_value_1, result);
      }
    }
    result->bits[3] = value_1.bits[3] + value_2.bits[3];
  } else {
    codeError = ERROR_BIG;
  }
  return codeError;
}

void s21_div_to_10(s21_decimal *value, int round) {
  uint64_t p_rest = 0;
  int div = 10;
  int rest = 0;
  for (int i = 2; i >= 0; i--) {
    p_rest = rest * 4294967296 + value->bits[i];
    value->bits[i] = p_rest / div;
    rest = p_rest - div * value->bits[i];
  }
  if (rest > 4 && round) {
    s21_decimal add_one = {{1, 0, 0, 0}};
    s21_add_logic(*value, add_one, value);
  }
}  // идеальное деление на 10

void value_crutch(s21_decimal *value_1, s21_decimal *value_2) {
  s21_decimal value_crutch = {0};
  s21_negate(*value_2, value_2);
  s21_negate(*value_1, value_1);
  s21_copy(&value_crutch, *value_2);
  s21_copy(value_2, *value_1);
  s21_copy(value_1, value_crutch);
}