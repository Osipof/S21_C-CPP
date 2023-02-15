#include "s21_decimal.h"

int s21_getBit(s21_decimal value, int bit) {
  return (value.bits[bit / 32] & (1 << (bit % 32))) != 0;
}  // получение нужного бита

int s21_getSign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }

// получение знака

void s21_setBit(s21_decimal *value, int bit) {
  value->bits[bit / 32] |= (1 << (bit % 32));
}  // ставит 1 в нужный бит

void s21_removeBit(s21_decimal *value, int bit) {
  value->bits[bit / 32] &= ~(1 << (bit % 32));
}  // ставит 0 в нужный бит

// void s21_inverseBit(s21_decimal *value, int bit) {
//   value->bits[bit / 32] ^= (1 << (bit % 32));
// }  // меняет нужный бит на другой

int get_scale(s21_decimal value) {
  int shift = 16;
  int scale = 0, i = 0;
  while (shift <= 23) {
    int bit = ((value.bits[3] & (1 << shift)) != 0);
    scale += bit * pow(2, i);
    shift++;
    i++;
  }
  return scale;
}

int s21_getDegree(s21_decimal value) {
  int result = (value.bits[3] << 1);
  // printf("\n result: %d", result);

  return (result >>= 17);

}  // получение степени

void s21_decreaseDegree(s21_decimal *value, int round) {
  int degree = s21_getDegree(*value) - 1;
  s21_div_to_10(value, round);
  s21_setDegree(value, degree);

}  // уменьшение степени

int s21_increaseDegree(s21_decimal *value) {
  s21_decimal maxdecimal_div_by_ten = {{2576980378, 2576980377, 429496729, 0}};
  s21_decimal ten = {0}, result = {0};
  ten.bits[0] |= 10;
  int overflow = 0;
  if (s21_is_greater_logic(maxdecimal_div_by_ten, *value)) {
    s21_mul(*value, ten, &result);
    s21_copy(value, result);
    s21_setDegree(value, s21_getDegree(result) + 1);
  } else {
    overflow = 1;
  }

  return overflow;
}  // работает

void s21_setDegree(s21_decimal *value, int degree) {
  int sign = s21_getSign(*value);
  value->bits[3] &= 0;
  value->bits[3] |= degree << 16;
  value->bits[3] |= sign << 31;

}  // замена ТОЛЬКО степени

// Как работает нормализация
// Если степень одного числа меньше другого, увеличиваем ту что меньше
// Если никуда увеличивать, то уменьшаем ту что больше
// Надо проверять что следующее увелечение не приведёт к переполнению

void s21_normalization(s21_decimal *value1, s21_decimal *value2) {
  int flag = 0;
  while (s21_getDegree(*value1) != s21_getDegree(*value2) &&
         !flag) {  // если степени не равны увеличиваем ту что
    if (s21_getDegree(*value1) > s21_getDegree(*value2)) {
      flag = s21_increaseDegree(value2);
    } else if (s21_getDegree(*value1) < s21_getDegree(*value2)) {
      flag = s21_increaseDegree(value1);
    }
  }

  while (s21_getDegree(*value1) != s21_getDegree(*value2)) {
    if (s21_getDegree(*value1) > s21_getDegree(*value2)) {
      s21_decreaseDegree(value1, 1);
    } else if (s21_getDegree(*value1) < s21_getDegree(*value2)) {
      s21_decreaseDegree(value2, 1);
    }
  }
}  // приведение к одной степени

void s21_normalization_result(s21_decimal value, s21_decimal *result,
                              int sign) {
  s21_setDegree(result, s21_getDegree(value));  // ставим степень
  if (sign) s21_setBit(result, 127);            // ставим знак
}

void s21_decimal_init(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) {
    decimal->bits[i] = 0;
  }
}

int s21_reset_bit(int num, int idx) { return num & ~(1 << idx); }

int s21_isZero(s21_decimal value) {
  int flag = 1;
  for (int i = 0; i < 3; i++) {
    if (value.bits[i] != 0) {
      flag = 0;
    }
  }
  return flag;
}

int s21_decimal_even(s21_decimal value) { return (value.bits[0] & 1) != 1; }