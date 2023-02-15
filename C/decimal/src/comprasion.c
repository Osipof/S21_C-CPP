#include "s21_decimal.h"

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  int res = 1;
  if (s21_getSign(value1) == s21_getSign(value2)) {
    s21_normalization(&value1, &value2);
    for (int i = 95; i >= 0; i--) {
      if (s21_getBit(value1, i) != s21_getBit(value2, i)) {
        res = 0;
        break;
      }
    }
  } else {
    if (div_to_zero(value1) || div_to_zero(value2)) res = 0;
  }
  return res;
}

int s21_is_not_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_equal(value1, value2);
}

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  int res = 0;
  int signValue1 = s21_getSign(value1);
  int signValue2 = s21_getSign(value2);
  if (signValue1 != signValue2) {
    if (signValue1 == 0) {
      if (!div_to_zero(value1) && !div_to_zero(value2)) {
        res = 0;
      } else {
        res = 1;
      }
    }
  } else {
    s21_normalization(&value1, &value2);
    for (int i = 95; i >= 0; i--) {
      int valueBit1 = s21_getBit(value1, i);
      int valueBit2 = s21_getBit(value2, i);
      if (valueBit1 != valueBit2) {
        if (valueBit1 == 1) {
          if (signValue1 == 0) {
            res = 1;
          }
          break;
        } else {
          if (signValue1 == 1) {
            res = 1;
          }
          break;
        }
      }
    }
  }
  return res;
}

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  return s21_is_greater(value2, value1);
}

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_greater(value1, value2);
}
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_less(value1, value2);
}
int s21_is_equal_logic(s21_decimal value1, s21_decimal value2) {
  int res = 1;
  for (int i = 95; i >= 0; i--) {
    if (s21_getBit(value1, i) != s21_getBit(value2, i)) {
      res = 0;
      break;
    }
  }
  return res;
}

int s21_is_greater_logic(s21_decimal value1, s21_decimal value2) {
  int res = 0;
  for (int i = 95; i >= 0; i--) {
    int valueBit1 = s21_getBit(value1, i);
    int valueBit2 = s21_getBit(value2, i);
    if (valueBit1 != valueBit2) {
      if (valueBit1 == 1) {
        res = 1;
        break;
      } else {
        res = 0;
        break;
      }
    }
  }

  return res;
}
/*
Return value:

0 - FALSE
1 - TRUE
*/
