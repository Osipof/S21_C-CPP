#include "cases.h"

void s21_matrix_testing(SRunner **sr);

// process calculation without errors
START_TEST(process_test_1) {
  double result = 0;
  ck_assert_int_eq(processCalculation("1+x", 1, &result), 0);
  ck_assert_double_eq(result, 1.0 + 1.0);
  ck_assert_int_eq(processCalculation("1+1 - 12 * (5^3) ", 0, &result), 0);
  ck_assert_double_eq(result, -1498.0);
  ck_assert_int_eq(
      processCalculation("1+1-2*3/"
                         "5^2-sin(1)+cos(2)-tan(1)+("
                         "sqrt(2)-log(4)+ln(2))+acos(1)+asin(1)+atan(1)",
                         0, &result),
      0);
  ck_assert_int_eq(processCalculation("10 mod 2", 0, &result), 0);
  ck_assert_double_eq(result, fmod(10, 2));
  ck_assert_int_eq(processCalculation("-1.1 + 1.1", 0, &result), 0);
  ck_assert_double_eq(result, -1.1 + 1.1);
  ck_assert_int_eq(processCalculation("10 mod 2 * 5", 0, &result), 0);
  ck_assert_double_eq(result, fmod(10, 2) * 5);
}
END_TEST

// error suitcases
START_TEST(process_test_2) {
  double res = 0;
  ck_assert_int_ne(processCalculation("hello", 0, &res), 0);
  ck_assert_int_ne(processCalculation("1+1)", 0, &res), 0);
  ck_assert_int_ne(processCalculation(")1+1 - 12 * (5^3) ", 0, &res), 0);
  ck_assert_int_ne(processCalculation("(23_32-3)", 0, &res), 0);
  ck_assert_int_ne(processCalculation(")1+2(", 0, &res), 0);
  ck_assert_int_ne(processCalculation("1.1.1+1", 0, &res), 0);
  ck_assert_int_ne(processCalculation("(+", 0, &res), 0);
  ck_assert_int_ne(processCalculation("+)", 0, &res), 0);
  ck_assert_int_ne(processCalculation("()", 0, &res), 0);
  ck_assert_int_ne(processCalculation("1+1)(1+1", 0, &res), 0);
  ck_assert_int_ne(processCalculation("2(", 0, &res), 0);
  ck_assert_int_ne(processCalculation(")2", 0, &res), 0);
  ck_assert_int_ne(processCalculation("(12))+(12", 0, &res), 0);
  ck_assert_int_ne(processCalculation("((3+3)", 0, &res), 0);
  ck_assert_int_ne(processCalculation("(-2.2 mod 2.1)", 0, &res), 0);
  ck_assert_int_ne(processCalculation("3/0", 0, &res), 0);
}
END_TEST

START_TEST(polish_test_1) {
  char input_char[512] = "";
  char output_char[512] = "";
  strcpy(input_char, "1+x");
  stringToReversePolishNotation(input_char, output_char);
  ck_assert_str_eq(output_char, "1 x +");
  strcpy(input_char, "1+1-12*(5^3)");
  stringToReversePolishNotation(input_char, output_char);
  ck_assert_str_eq(output_char, "1 1 + 12 5 3 ^ * -");
  strcpy(input_char,
         "1+1-2*3/"
         "5^2-sin(1)+cos(2)-tan(1)+("
         "sqrt(2)-log(4)+ln(2))+acos(1)+asin(1)+atan(1)");
  stringToReversePolishNotation(input_char, output_char);
  ck_assert_str_eq(output_char,
                   "1 1 + 2 3 * 5 2 ^ 1 s - 2 c + 1 t - 2 q 4 L - 2 l + + 1 C "
                   "+ 1 S + 1 T + / -");
  strcpy(input_char, "10 mod 2");
  stringToReversePolishNotation(input_char, output_char);
  ck_assert_str_eq(output_char, "10 2 m");
  strcpy(input_char, "-1.1 + 1.1");
  stringToReversePolishNotation(input_char, output_char);
  ck_assert_str_eq(output_char, "1,1 ~ 1,1 +");
}
END_TEST

Suite *suite_test(void) {
  Suite *s;
  TCase *process_test, *polish_test;

  s = suite_create("calc_test");

  process_test = tcase_create("processCalculation");
  tcase_add_test(process_test, process_test_1);
  tcase_add_test(process_test, process_test_2);
  suite_add_tcase(s, process_test);

  polish_test = tcase_create("polish");
  tcase_add_test(polish_test, polish_test_1);
  suite_add_tcase(s, polish_test);
  return s;
}
