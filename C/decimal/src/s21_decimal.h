#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define NUM_255 255
#define S21_MAX_UINT 4294967295
#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)
#define S21_MAX_UINT 4294967295

#define MINUS_SIGN 2147483648

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// Arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_sub_results(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);

// Comparison Operators
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Another functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Auxiliary functions
int s21_isNull(s21_decimal value);

int s21_getBit(s21_decimal value, int bit);
int s21_getSign(s21_decimal value);
int s21_isNull(s21_decimal value);
int s21_getDegree(s21_decimal value);
void s21_decreaseDegree(s21_decimal *value, int round);
void s21_setDegree(s21_decimal *value, int degree);
void s21_normalization(s21_decimal *value1, s21_decimal *value2);
void s21_normalization_result(s21_decimal value, s21_decimal *result, int sign);
void s21_setBit(s21_decimal *value, int bit);
void s21_removeBit(s21_decimal *value, int bit);
void s21_inverseBit(s21_decimal *value, int bit);

void printdecimal(s21_decimal num);
void s21_decimal_init(s21_decimal *decimal);
int s21_reset_bit(int num, int idx);
int div_to_zero(s21_decimal value_2);
void zero_result(s21_decimal *result);
void s21_copy(s21_decimal *dst, s21_decimal src);

int s21_add_logic(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result);

int s21_div_10(s21_decimal value_1, s21_decimal *result);

int s21_is_equal_logic(s21_decimal value1, s21_decimal value2);
int s21_is_greater_logic(s21_decimal value1, s21_decimal value2);
void s21_copy_3(s21_decimal *dst, s21_decimal src);
void s21_div_to_10(s21_decimal *value, int round);
int s21_check_add_overflow(s21_decimal value_1, s21_decimal value_2);
int s21_isZero(s21_decimal value);
int get_scale(s21_decimal value);
int s21_decimal_even(s21_decimal value);
void value_crutch(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal s21_banking_round(s21_decimal value_without_fractional,
                              s21_decimal fractional);