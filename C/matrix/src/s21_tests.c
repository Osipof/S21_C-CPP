#include <check.h>
#include <stdio.h>

#include "s21_matrix.h"
void s21_matrix_testing(SRunner **sr);

START_TEST(s21_create_matrix_test_1) {
  matrix_t result_;
  int result = s21_create_matrix(-3, -1, &result_);
  int expected = INPUT_ERROR;
  ck_assert_uint_eq(expected, result);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_create_matrix_test_2) {
  matrix_t result_;
  int result = s21_create_matrix(44, -1, &result_);
  int expected = INPUT_ERROR;
  ck_assert_uint_eq(expected, result);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_create_matrix_test_3) {
  matrix_t result_;
  int result = s21_create_matrix(44, 0, &result_);
  int expected = INPUT_ERROR;
  ck_assert_uint_eq(expected, result);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_create_matrix_test_4) {
  matrix_t result_;
  int result = s21_create_matrix(0, 0, &result_);
  int expected = INPUT_ERROR;
  ck_assert_uint_eq(expected, result);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_create_matrix_test_5) {
  matrix_t result_;
  int result = s21_create_matrix(-1, 3, &result_);
  int expected = INPUT_ERROR;
  ck_assert_uint_eq(expected, result);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_create_matrix_test_6) {
  matrix_t result_;
  int result = s21_create_matrix(3, 3, &result_);
  int expected = OPERATION_SUCCESS;
  ck_assert_uint_eq(expected, result);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_create_matrix_test_7) {
  matrix_t result_;
  int result = s21_create_matrix(15, 15, &result_);
  int expected = OPERATION_SUCCESS;
  ck_assert_uint_eq(expected, result);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_create_matrix_test_8) {
  matrix_t result_;
  int result = s21_create_matrix(3, 25, &result_);
  int expected = OPERATION_SUCCESS;
  ck_assert_uint_eq(expected, result);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_create_matrix_test_9) {
  matrix_t result_;
  int result = s21_create_matrix(2, 2, &result_);
  int expected = OPERATION_SUCCESS;
  ck_assert_uint_eq(expected, result);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_create_matrix_test_10) {
  matrix_t result_;
  int result = s21_create_matrix(1, 1, &result_);
  int expected = OPERATION_SUCCESS;
  ck_assert_uint_eq(expected, result);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_create_matrix_test_11) {
  int result = s21_create_matrix(1, 1, NULL);
  int expected = INPUT_ERROR;
  ck_assert_uint_eq(expected, result);
}
END_TEST
Suite *s21_create_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_create_matrix;
  s = suite_create("\n s21_create_matrix");
  tc_s21_create_matrix = tcase_create("create_matrix");
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_1);
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_2);
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_3);
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_4);
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_5);
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_6);
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_7);
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_8);
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_9);
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_10);
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_11);
  suite_add_tcase(s, tc_s21_create_matrix);
  return s;
}

START_TEST(s21_eq_matrix_test_1) {
  matrix_t A, B;
  s21_create_matrix(15, 4, &A);
  s21_create_matrix(15, 4, &B);
  int expected = 1;
  int result_ = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(expected, result_);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_eq_matrix_test_2) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = -0.000001;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 0.0000001;
  A.matrix[1][0] = 5.88;
  A.matrix[1][1] = 1.3;
  A.matrix[1][2] = 33.5;
  A.matrix[2][0] = -11;
  A.matrix[2][1] = -21;
  A.matrix[2][2] = -31;
  B.matrix[0][0] = -0.000001;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 0.0000001;
  B.matrix[1][0] = 5.88;
  B.matrix[1][1] = 1.3;
  B.matrix[1][2] = 33.5;
  B.matrix[2][0] = -11;
  B.matrix[2][1] = -21;
  B.matrix[2][2] = -31;
  int expected = 1;
  int result_ = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected, result_);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_eq_matrix_test_3) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = 0.0001;
  A.matrix[0][1] = 3;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = 72;
  A.matrix[1][1] = -144;
  A.matrix[1][2] = 44.44;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 1;
  B.matrix[0][0] = 0.0000001;
  B.matrix[0][1] = 3;
  B.matrix[0][2] = -3;
  B.matrix[1][0] = 72;
  B.matrix[1][1] = -144;
  B.matrix[1][2] = 44.44;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;
  int expected = 0;
  int result_ = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected, result_);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_eq_matrix_test_4) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 55;
  A.matrix[1][1] = 66.01;
  A.matrix[1][2] = 77.01;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = -0.000001;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 55;
  B.matrix[1][1] = 66.01;
  B.matrix[1][2] = 77.01;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 0.000001;
  int expected = 0;
  int result_ = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected, result_);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_eq_matrix_test_5) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 55;
  A.matrix[1][1] = 66.01;
  A.matrix[1][2] = 77.01;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = -0.000001;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 55;
  B.matrix[1][1] = 66.01;
  B.matrix[1][2] = 77.01;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = -0.000011;
  int expected = 0;
  int result_ = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected, result_);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_eq_matrix_test_6) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 55;
  A.matrix[1][1] = 66.01;
  A.matrix[1][2] = 77.01;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = -0.000011;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 55;
  B.matrix[1][1] = 66.01;
  B.matrix[1][2] = 77.01;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = -0.000011;
  int expected = 1;
  int result_ = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected, result_);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_eq_matrix_test_7) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 0, &B);
  A.matrix[0][0] = 0.01;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 2;
  A.matrix[1][0] = 3.3;
  A.matrix[1][1] = 3.3;
  A.matrix[1][2] = 3.4;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 1;
  int expected = 0;
  int result_ = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(expected, result_);
  s21_remove_matrix(&A);
}
END_TEST
Suite *s21_eq_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_eq_matrix;
  s = suite_create("s21_eq_matrix");
  tc_s21_eq_matrix = tcase_create("eq_matrix");
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_1);
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_2);
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_3);
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_4);
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_5);
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_6);
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_7);
  suite_add_tcase(s, tc_s21_eq_matrix);
  return s;
}

START_TEST(s21_sum_matrix_test_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  matrix_t B;
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 1.0;
  A.matrix[0][2] = 2.0;

  A.matrix[1][0] = 3.3;
  A.matrix[1][1] = 3.3;
  A.matrix[1][2] = 3.4;

  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = 1.0;
  A.matrix[2][2] = 1.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[0][2] = 2.0;

  B.matrix[1][0] = 3.3;
  B.matrix[1][1] = 3.3;
  B.matrix[1][2] = 3.4;

  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;

  matrix_t expected;
  s21_create_matrix(3, 3, &expected);
  matrix_t result_;
  s21_sum_matrix(&A, &B, &result_);
  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 4;

  expected.matrix[1][0] = 6.6;
  expected.matrix[1][1] = 6.6;
  expected.matrix[1][2] = 6.8;

  expected.matrix[2][0] = 2;
  expected.matrix[2][1] = 2;
  expected.matrix[2][2] = 2;
  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_sum_matrix_test_2) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  matrix_t B;
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 1.0;
  A.matrix[0][2] = 2.0;
  A.matrix[1][0] = 3.3;
  A.matrix[1][1] = 3.3;
  A.matrix[1][2] = 3.4;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = 1.0;
  A.matrix[2][2] = 1.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[0][2] = 2.0;
  B.matrix[1][0] = 3.3;
  B.matrix[1][1] = 3.3;
  B.matrix[1][2] = 3.4;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;
  matrix_t expected;
  s21_create_matrix(3, 3, &expected);
  matrix_t result_;
  s21_sum_matrix(&A, &B, &result_);
  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 4;
  expected.matrix[1][0] = 6.6;
  expected.matrix[1][1] = 6.6;
  expected.matrix[1][2] = 6.8;
  expected.matrix[2][0] = 2;
  expected.matrix[2][1] = 2;
  expected.matrix[2][2] = 2;
  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_sum_matrix_test_3) {
  matrix_t A;
  s21_create_matrix(3, 2, &A);
  matrix_t B;
  s21_create_matrix(3, 2, &B);
  A.matrix[0][0] = 0.1;
  A.matrix[0][1] = 0.2;
  A.matrix[1][0] = -1.;
  A.matrix[1][1] = -1.;
  A.matrix[2][0] = -1.0;
  A.matrix[2][1] = -1.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[1][0] = 3.3;
  B.matrix[1][1] = 3.3;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  matrix_t expected;
  s21_create_matrix(3, 2, &expected);
  matrix_t result_;
  s21_sum_matrix(&A, &B, &result_);
  expected.matrix[0][0] = 1.1;
  expected.matrix[0][1] = 1.2;
  expected.matrix[1][0] = 2.3;
  expected.matrix[1][1] = 2.3;
  expected.matrix[2][0] = 0;
  expected.matrix[2][1] = 0;
  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_sum_matrix_test_4) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  matrix_t B;
  s21_create_matrix(3, 2, &B);
  A.matrix[0][0] = 0.1;
  A.matrix[0][1] = 0.2;
  A.matrix[1][0] = -1.;
  A.matrix[1][1] = -1.;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[1][0] = 3.3;
  B.matrix[1][1] = 3.3;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  matrix_t result_;
  int result = s21_sum_matrix(&A, &B, &result_);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  int expected = EXECUTION_ERROR;
  ck_assert_int_eq(expected, result);
}
END_TEST
START_TEST(s21_sum_matrix_test_5) {
  matrix_t A;
  s21_create_matrix(-2, -2, &A);
  matrix_t B;
  s21_create_matrix(3, 2, &B);
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[1][0] = 3.3;
  B.matrix[1][1] = 3.3;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  matrix_t result_;
  int result = s21_sum_matrix(&A, &B, &result_);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  int expected = INPUT_ERROR;
  ck_assert_int_eq(expected, result);
}
END_TEST
Suite *s21_sum_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_sum_matrix;
  s = suite_create("s21_sum_matrix");
  tc_s21_sum_matrix = tcase_create("sum_matrix");
  tcase_add_test(tc_s21_sum_matrix, s21_sum_matrix_test_1);
  tcase_add_test(tc_s21_sum_matrix, s21_sum_matrix_test_2);
  tcase_add_test(tc_s21_sum_matrix, s21_sum_matrix_test_3);
  tcase_add_test(tc_s21_sum_matrix, s21_sum_matrix_test_4);
  tcase_add_test(tc_s21_sum_matrix, s21_sum_matrix_test_5);
  suite_add_tcase(s, tc_s21_sum_matrix);
  return s;
}

START_TEST(s21_sub_matrix_test_1) {
  matrix_t A;
  s21_create_matrix(3, 2, &A);
  matrix_t B;
  s21_create_matrix(3, 2, &B);
  A.matrix[0][0] = 0.1;
  A.matrix[0][1] = 0.2;

  A.matrix[1][0] = -1.;
  A.matrix[1][1] = -1.;

  A.matrix[2][0] = -1.0;
  A.matrix[2][1] = -1.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;

  B.matrix[1][0] = 3.3;
  B.matrix[1][1] = 3.3;

  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;

  matrix_t expected;
  s21_create_matrix(3, 2, &expected);
  matrix_t result_;
  s21_sub_matrix(&A, &B, &result_);
  expected.matrix[0][0] = -0.9;
  expected.matrix[0][1] = -0.8;

  expected.matrix[1][0] = -4.3;
  expected.matrix[1][1] = -4.3;

  expected.matrix[2][0] = -2.;
  expected.matrix[2][1] = -2.;

  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_sub_matrix_test_2) {
  matrix_t A;
  int row = -1;
  s21_create_matrix(row, 2, &A);
  matrix_t B;
  s21_create_matrix(3, 2, &B);
  matrix_t result;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[1][0] = 3.3;
  B.matrix[1][1] = 3.3;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  int expected = INPUT_ERROR;
  int result_ = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(expected, result_);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_sub_matrix_test_3) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  matrix_t B;
  s21_create_matrix(3, 2, &B);
  A.matrix[0][0] = 0.1;
  A.matrix[0][1] = 0.2;
  A.matrix[1][0] = -1.;
  A.matrix[1][1] = -1.;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[1][0] = 3.3;
  B.matrix[1][1] = 3.3;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  matrix_t result_;
  int result = s21_sub_matrix(&A, &B, &result_);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  int expected = EXECUTION_ERROR;
  ck_assert_int_eq(expected, result);
}
END_TEST
Suite *s21_sub_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_sub_matrix;
  s = suite_create("s21_sub_matrix");
  tc_s21_sub_matrix = tcase_create("sub_matrix");
  tcase_add_test(tc_s21_sub_matrix, s21_sub_matrix_test_1);
  tcase_add_test(tc_s21_sub_matrix, s21_sub_matrix_test_2);
  tcase_add_test(tc_s21_sub_matrix, s21_sub_matrix_test_3);
  suite_add_tcase(s, tc_s21_sub_matrix);
  return s;
}

START_TEST(s21_mult_number_test_1) {
  matrix_t A;
  s21_create_matrix(3, 2, &A);
  matrix_t result;
  A.matrix[0][0] = 0.1;
  A.matrix[0][1] = 0.2;

  A.matrix[1][0] = -1.;
  A.matrix[1][1] = -1.;

  A.matrix[2][0] = -1.0;
  A.matrix[2][1] = -1.0;
  matrix_t check;
  s21_create_matrix(3, 2, &check);

  check.matrix[0][0] = 0;
  check.matrix[0][1] = 0;

  check.matrix[1][0] = 0;
  check.matrix[1][1] = 0;

  check.matrix[2][0] = 0;
  check.matrix[2][1] = 0;
  double value = 0;
  int expected = OPERATION_SUCCESS;
  int result_ = s21_mult_number(&A, value, &result);
  ck_assert_int_eq(expected, result_);

  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      flag = 0;
      if (fabs(check.matrix[i][j] - result.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST
START_TEST(s21_mult_number_test_2) {
  matrix_t A;
  s21_create_matrix(3, 2, &A);
  matrix_t result;
  A.matrix[0][0] = 0.1;
  A.matrix[0][1] = 0.2;
  A.matrix[1][0] = -1.;
  A.matrix[1][1] = -1.;
  A.matrix[2][0] = -1.5;
  A.matrix[2][1] = -3.0000007;
  matrix_t check;
  s21_create_matrix(3, 2, &check);
  check.matrix[0][0] = -0.1;
  check.matrix[0][1] = -0.2;
  check.matrix[1][0] = 1.;
  check.matrix[1][1] = 1.;
  check.matrix[2][0] = 1.5;
  check.matrix[2][1] = 3.0000007;
  double value = -1;
  int expected = OPERATION_SUCCESS;
  int result_ = s21_mult_number(&A, value, &result);
  ck_assert_int_eq(expected, result_);
  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      flag = 0;
      if (fabs(check.matrix[i][j] - result.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST
START_TEST(s21_mult_number_test_3) {
  matrix_t A;
  s21_create_matrix(-1, 2, &A);
  matrix_t result;

  double value = -1;
  int expected = INPUT_ERROR;
  int result_ = s21_mult_number(&A, value, &result);
  ck_assert_int_eq(expected, result_);
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_mult_number_test_4) {
  matrix_t A;
  s21_create_matrix(3, 2, &A);
  matrix_t result;
  A.matrix[0][0] = 0.1;
  A.matrix[0][1] = 0.2;
  A.matrix[1][0] = -1.;
  A.matrix[1][1] = -1.;
  A.matrix[2][0] = -1.5;
  A.matrix[2][1] = -3.0000007;
  matrix_t check;
  s21_create_matrix(3, 2, &check);
  check.matrix[0][0] = 0.;
  check.matrix[0][1] = 0.;
  check.matrix[1][0] = 0.;
  check.matrix[1][1] = 0.;
  check.matrix[2][0] = 0.;
  check.matrix[2][1] = 0.;
  double value = 0.;
  int expected = OPERATION_SUCCESS;
  int result_ = s21_mult_number(&A, value, &result);
  ck_assert_int_eq(expected, result_);
  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      flag = 0;
      if (fabs(check.matrix[i][j] - result.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST
Suite *s21_mult_number_suite(void) {
  Suite *s;
  TCase *tc_s21_mult_number;
  s = suite_create("s21_mult_number");
  tc_s21_mult_number = tcase_create("mult_number");
  tcase_add_test(tc_s21_mult_number, s21_mult_number_test_1);
  tcase_add_test(tc_s21_mult_number, s21_mult_number_test_2);
  tcase_add_test(tc_s21_mult_number, s21_mult_number_test_3);
  tcase_add_test(tc_s21_mult_number, s21_mult_number_test_4);
  suite_add_tcase(s, tc_s21_mult_number);
  return s;
}

START_TEST(s21_mult_matrix_test_1) {
  matrix_t A;
  s21_create_matrix(3, 2, &A);
  matrix_t B;
  s21_create_matrix(2, 3, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;

  A.matrix[1][0] = -1.;
  A.matrix[1][1] = -1.;

  A.matrix[2][0] = -1.0;
  A.matrix[2][1] = -1.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[0][2] = 1.;

  B.matrix[1][0] = 3.3;
  B.matrix[1][1] = 3.3;
  B.matrix[1][2] = 0.3;

  matrix_t expected;
  s21_create_matrix(3, 3, &expected);
  matrix_t result_;
  s21_mult_matrix(&A, &B, &result_);
  expected.matrix[0][0] = 4.3;
  expected.matrix[0][1] = 4.3;
  expected.matrix[0][2] = 1.3;

  expected.matrix[1][0] = -4.3;
  expected.matrix[1][1] = -4.3;
  expected.matrix[1][2] = -1.3;

  expected.matrix[2][0] = -4.3;
  expected.matrix[2][1] = -4.3;
  expected.matrix[2][2] = -1.3;

  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result_);
  s21_remove_matrix(&expected);
}
END_TEST
START_TEST(s21_mult_matrix_test_2) {
  matrix_t A;
  s21_create_matrix(3, 2, &A);
  matrix_t B;
  s21_create_matrix(2, 3, &B);
  A.matrix[0][0] = 0.;
  A.matrix[0][1] = 0.;
  A.matrix[1][0] = -1.;
  A.matrix[1][1] = -1.;
  A.matrix[2][0] = -1.0;
  A.matrix[2][1] = -1.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[0][2] = -1;
  B.matrix[1][0] = 3.3;
  B.matrix[1][1] = 3.3;
  B.matrix[1][2] = -1;
  matrix_t expected;
  s21_create_matrix(3, 3, &expected);
  matrix_t result_;
  s21_mult_matrix(&A, &B, &result_);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 0;
  expected.matrix[0][2] = 0;
  expected.matrix[1][0] = -4.3;
  expected.matrix[1][1] = -4.3;
  expected.matrix[1][2] = 2;
  expected.matrix[2][0] = -4.3;
  expected.matrix[2][1] = -4.3;
  expected.matrix[2][2] = 2;
  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_mult_matrix_test_3) {
  matrix_t A;
  s21_create_matrix(3, 2, &A);
  matrix_t B;
  s21_create_matrix(1, 3, &B);
  A.matrix[0][0] = 0.;
  A.matrix[0][1] = 0.;
  A.matrix[1][0] = -1.;
  A.matrix[1][1] = -1.;
  A.matrix[2][0] = -1.0;
  A.matrix[2][1] = -1.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[0][2] = -1;
  matrix_t result_;
  int expected = EXECUTION_ERROR;
  int result = s21_mult_matrix(&A, &B, &result_);
  ck_assert_int_eq(expected, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_mult_matrix_test_4) {
  matrix_t A;
  s21_create_matrix(3, 2, &A);
  matrix_t B;
  int row = -1;
  s21_create_matrix(row, 3, &B);
  matrix_t result_;

  int expected = INPUT_ERROR;
  int result = s21_mult_matrix(&A, &B, &result_);
  ck_assert_int_eq(expected, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
START_TEST(s21_mult_matrix_test_5) {
  matrix_t A;
  s21_create_matrix(1, 3, &A);
  matrix_t B;
  s21_create_matrix(3, 1, &B);
  matrix_t result_;
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  A.matrix[0][2] = 3.;
  B.matrix[0][0] = 1.0;
  B.matrix[1][0] = 1.0;
  B.matrix[2][0] = 2.;
  matrix_t check;
  s21_create_matrix(1, 1, &check);
  check.matrix[0][0] = 9.0;
  int expected = OPERATION_SUCCESS;
  int result = s21_mult_matrix(&A, &B, &result_);
  ck_assert_int_eq(expected, result);
  int flag = 0, res = 1;
  if (fabs(check.matrix[0][0] - result_.matrix[0][0]) < 10e-6) flag = 1;
  ck_assert_int_eq(flag, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result_);
  s21_remove_matrix(&check);
}
END_TEST
Suite *s21_mult_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_mult_matrix;
  s = suite_create("s21_mult_matrix");
  tc_s21_mult_matrix = tcase_create("mult_matrix");
  tcase_add_test(tc_s21_mult_matrix, s21_mult_matrix_test_1);
  tcase_add_test(tc_s21_mult_matrix, s21_mult_matrix_test_2);
  tcase_add_test(tc_s21_mult_matrix, s21_mult_matrix_test_3);
  tcase_add_test(tc_s21_mult_matrix, s21_mult_matrix_test_4);
  tcase_add_test(tc_s21_mult_matrix, s21_mult_matrix_test_5);
  suite_add_tcase(s, tc_s21_mult_matrix);
  return s;
}

START_TEST(s21_transpose_test_1) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;

  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 4;

  A.matrix[2][0] = 1;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 3;
  A.matrix[2][3] = 4;

  A.matrix[3][0] = 1;
  A.matrix[3][1] = 2;
  A.matrix[3][2] = 3;
  A.matrix[3][3] = 4;

  matrix_t expected;
  s21_create_matrix(4, 4, &expected);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      expected.matrix[i][j] = A.matrix[j][i];
    }
  }

  matrix_t result_;
  s21_transpose(&A, &result_);

  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_transpose_test_2) {
  matrix_t A;
  s21_create_matrix(2, 4, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 4;
  matrix_t expected;
  s21_create_matrix(4, 2, &expected);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      expected.matrix[i][j] = A.matrix[j][i];
    }
  }
  matrix_t result_;
  s21_transpose(&A, &result_);
  int flag = 0, res = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_transpose_test_3) {
  matrix_t A;
  int s21_check = s21_create_matrix(0, 4, &A);

  matrix_t result_;
  s21_check = s21_transpose(&A, &result_);
  ck_assert_uint_eq(INPUT_ERROR, s21_check);
}
END_TEST
START_TEST(s21_transpose_test_4) {
  matrix_t A;
  s21_create_matrix(-2, 4, &A);
  matrix_t result_;
  int check = s21_transpose(&A, &result_);
  int s21_check = INPUT_ERROR;
  ck_assert_int_eq(check, s21_check);
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_transpose_test_5) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1.;
  matrix_t result_;
  int check = s21_transpose(&A, &result_);
  int s21_check = OPERATION_SUCCESS;
  ck_assert_int_eq(check, s21_check);
  int flag = 0, res = 1;
  if (fabs(A.matrix[0][0] - result_.matrix[0][0]) < 10e-6) flag = 1;
  ck_assert_int_eq(flag, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result_);
}
END_TEST
Suite *s21_transpose_suite(void) {
  Suite *s;
  TCase *tc_s21_transpose;
  s = suite_create("s21_transpose");
  tc_s21_transpose = tcase_create("transpose");
  tcase_add_test(tc_s21_transpose, s21_transpose_test_1);
  tcase_add_test(tc_s21_transpose, s21_transpose_test_2);
  tcase_add_test(tc_s21_transpose, s21_transpose_test_3);
  tcase_add_test(tc_s21_transpose, s21_transpose_test_4);
  tcase_add_test(tc_s21_transpose, s21_transpose_test_5);
  suite_add_tcase(s, tc_s21_transpose);
  return s;
}

START_TEST(s21_calc_complements_test_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  matrix_t expected;
  s21_create_matrix(3, 3, &expected);

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;

  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;

  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  matrix_t result_;
  s21_calc_complements(&A, &result_);

  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result_);
}

START_TEST(s21_calc_complements_test_2) {
  matrix_t A;
  s21_create_matrix(3, 4, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 10;
  A.matrix[0][2] = -20;
  A.matrix[0][3] = 0;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = -14;
  A.matrix[1][2] = 8;
  A.matrix[1][3] = 0;

  A.matrix[2][0] = -8;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = 4;
  A.matrix[2][3] = 0;
  matrix_t result_;
  int result = s21_calc_complements(&A, &result_);
  int expected = EXECUTION_ERROR;
  ck_assert_int_eq(result, expected);
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_calc_complements_test_3) {
  matrix_t A;
  s21_create_matrix(-1, 4, &A);
  matrix_t result_;
  int result = s21_calc_complements(&A, &result_);
  int expected = INPUT_ERROR;
  ck_assert_int_eq(result, expected);
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_calc_complements_test_4) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 5.55;
  A.matrix[0][1] = 32;
  A.matrix[1][0] = -55;
  A.matrix[1][1] = -4;
  matrix_t expected;
  s21_create_matrix(2, 2, &expected);
  expected.matrix[0][0] = -4;
  expected.matrix[0][1] = 55;
  expected.matrix[1][0] = -32;
  expected.matrix[1][1] = 5.55;
  matrix_t result_;
  s21_calc_complements(&A, &result_);
  int flag = 0, res = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result_);
}

Suite *s21_calc_complements_suite(void) {
  Suite *s;
  TCase *tc_s21_calc_complements;
  s = suite_create("s21_calc_complements");
  tc_s21_calc_complements = tcase_create("calc_complements");
  tcase_add_test(tc_s21_calc_complements, s21_calc_complements_test_1);
  tcase_add_test(tc_s21_calc_complements, s21_calc_complements_test_2);
  tcase_add_test(tc_s21_calc_complements, s21_calc_complements_test_3);
  tcase_add_test(tc_s21_calc_complements, s21_calc_complements_test_4);
  suite_add_tcase(s, tc_s21_calc_complements);
  return s;
}

START_TEST(s21_determinant_test_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  double expected = 0;
  double result_ = 0.0;
  s21_determinant(&A, &result_);
  int flag = 0, res = 1;

  if (fabs(expected - result_) < 10e-6) flag = 1;

  ck_assert_int_eq(flag, res);
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_determinant_test_2) {
  matrix_t A;
  s21_create_matrix(3, 4, &A);
  double result_ = 0;
  int expected = 2;
  int result = s21_determinant(&A, &result_);
  ck_assert_int_eq(expected, result);
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_determinant_test_3) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 3;
  double expected = 3.;
  double result_ = 0.0;
  s21_determinant(&A, &result_);
  int flag = 0, res = 1;
  if (fabs(expected - result_) < 10e-6) flag = 1;
  ck_assert_int_eq(flag, res);
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_determinant_test_4) {
  matrix_t A;
  s21_create_matrix(0, 1, &A);
  double result_ = 0.0;
  int s21_check = s21_determinant(&A, &result_);
  int check = INPUT_ERROR;
  ck_assert_int_eq(check, s21_check);
  s21_remove_matrix(&A);
}
END_TEST
Suite *s21_determinant_suite(void) {
  Suite *s;
  TCase *tc_s21_determinant;
  s = suite_create("s21_determinant");
  tc_s21_determinant = tcase_create("determinant");
  tcase_add_test(tc_s21_determinant, s21_determinant_test_1);
  tcase_add_test(tc_s21_determinant, s21_determinant_test_2);
  tcase_add_test(tc_s21_determinant, s21_determinant_test_3);
  tcase_add_test(tc_s21_determinant, s21_determinant_test_4);
  suite_add_tcase(s, tc_s21_determinant);
  return s;
}

START_TEST(s21_inverse_matrix_test_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;

  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  matrix_t expected;
  s21_create_matrix(3, 3, &expected);

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;

  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;

  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  matrix_t result_;
  int check = s21_inverse_matrix(&A, &result_);
  int flag = 0, res = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      flag = 0;
      if (fabs(expected.matrix[i][j] - result_.matrix[i][j]) < 10e-6) flag = 1;
      ck_assert_int_eq(flag, res);
    }
  }
  ck_assert_int_eq(check, OPERATION_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result_);
}

START_TEST(s21_inverse_matrix_test_2) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  int expected = EXECUTION_ERROR;
  matrix_t result_;
  int result = s21_inverse_matrix(&A, &result_);
  ck_assert_int_eq(expected, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result_);
}
END_TEST
START_TEST(s21_inverse_matrix_test_3) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0. / 0.;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  int expected = EXECUTION_ERROR;

  matrix_t result_;
  int result = s21_inverse_matrix(&A, &result_);
  ck_assert_int_eq(expected, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result_);
}
END_TEST
END_TEST
Suite *s21_inverse_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_inverse_matrix;
  s = suite_create("s21_inverse_matrix");
  tc_s21_inverse_matrix = tcase_create("inverse_matrix");
  tcase_add_test(tc_s21_inverse_matrix, s21_inverse_matrix_test_1);
  tcase_add_test(tc_s21_inverse_matrix, s21_inverse_matrix_test_2);
  tcase_add_test(tc_s21_inverse_matrix, s21_inverse_matrix_test_3);
  suite_add_tcase(s, tc_s21_inverse_matrix);
  return s;
}

void s21_matrix_testing(SRunner **sr) {
  *sr = srunner_create(s21_create_matrix_suite());
  srunner_add_suite(*sr, s21_eq_matrix_suite());
  srunner_add_suite(*sr, s21_sum_matrix_suite());
  srunner_add_suite(*sr, s21_sub_matrix_suite());
  srunner_add_suite(*sr, s21_mult_number_suite());
  srunner_add_suite(*sr, s21_mult_matrix_suite());
  srunner_add_suite(*sr, s21_transpose_suite());
  srunner_add_suite(*sr, s21_calc_complements_suite());
  srunner_add_suite(*sr, s21_determinant_suite());
  srunner_add_suite(*sr, s21_inverse_matrix_suite());
}

int main(void) {
  int number_failed;
  SRunner *sr = NULL;
  s21_matrix_testing(&sr);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
