#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

class S21MatrixTest : public testing::Test {
 protected:
  S21Matrix *matrix_3x3;
  S21Matrix *matrix_4x3;
  S21Matrix *matrix_temp;

  void SetUp() {
    matrix_3x3 = new S21Matrix();
    (*matrix_3x3)(0, 0) = 0;
    (*matrix_3x3)(0, 1) = 1;
    (*matrix_3x3)(0, 2) = 2;
    (*matrix_3x3)(1, 0) = 3;
    (*matrix_3x3)(1, 1) = 4;
    (*matrix_3x3)(1, 2) = 5;
    (*matrix_3x3)(2, 0) = 6;
    (*matrix_3x3)(2, 1) = 7;
    (*matrix_3x3)(2, 2) = 8;

    matrix_4x3 = new S21Matrix(4, 3);
    (*matrix_4x3)(0, 0) = 0;
    (*matrix_4x3)(0, 1) = 1;
    (*matrix_4x3)(0, 2) = 2;
    (*matrix_4x3)(1, 0) = 3;
    (*matrix_4x3)(1, 1) = 4;
    (*matrix_4x3)(1, 2) = 5;
    (*matrix_4x3)(2, 0) = 6;
    (*matrix_4x3)(2, 1) = 7;
    (*matrix_4x3)(2, 2) = 8;
    (*matrix_4x3)(3, 0) = 9;
    (*matrix_4x3)(3, 1) = 10;
    (*matrix_4x3)(3, 2) = 11;
  }

  void TearDown() {
    delete matrix_3x3;
    delete matrix_4x3;
  }
};

TEST_F(S21MatrixTest, constructor) {
  S21Matrix matrix;
  EXPECT_EQ(3, matrix.get_rows());
  EXPECT_EQ(3, matrix.get_cols());
}

TEST_F(S21MatrixTest, constructorWithParameters) {
  S21Matrix matrix(5, 6);
  EXPECT_EQ(5, matrix.get_rows());
  EXPECT_EQ(6, matrix.get_cols());
}

TEST_F(S21MatrixTest, constructorWithParametersError) {
  EXPECT_THROW(matrix_temp = new S21Matrix(0, 0), std::out_of_range);
}

TEST_F(S21MatrixTest, constructorCopy) {
  S21Matrix matrix(*matrix_4x3);
  EXPECT_EQ(4, matrix.get_rows());
  EXPECT_EQ(3, matrix.get_cols());
  EXPECT_EQ(4, matrix_4x3->get_rows());
  EXPECT_EQ(3, matrix_4x3->get_cols());
  EXPECT_EQ(1, *matrix_4x3 == matrix);
}

TEST_F(S21MatrixTest, constructorMove) {
  S21Matrix matrix_copy(*matrix_4x3);
  S21Matrix matrix(std::move(*matrix_4x3));
  EXPECT_EQ(4, matrix.get_rows());
  EXPECT_EQ(3, matrix.get_cols());
  EXPECT_EQ(1, matrix_copy == matrix);
  EXPECT_EQ(0, matrix_4x3->get_rows());
  EXPECT_EQ(0, matrix_4x3->get_cols());
}

TEST_F(S21MatrixTest, get_colsAndRows) {
  EXPECT_EQ(3, matrix_3x3->get_rows());
  EXPECT_EQ(3, matrix_3x3->get_cols());
  EXPECT_EQ(4, matrix_4x3->get_rows());
  EXPECT_EQ(3, matrix_4x3->get_cols());
}

TEST_F(S21MatrixTest, set_colsAndRows) {
  matrix_3x3->set_rows(4);
  EXPECT_EQ(4, matrix_3x3->get_rows());
  EXPECT_THROW(matrix_3x3->set_rows(-1), std::out_of_range);
  matrix_3x3->set_cols(4);
  EXPECT_EQ(4, matrix_3x3->get_cols());
  EXPECT_THROW(matrix_3x3->set_cols(0), std::out_of_range);
}

TEST_F(S21MatrixTest, qualityOperator) {
  S21Matrix matrix, empty_matrix;
  EXPECT_EQ(0, *matrix_3x3 == *matrix_4x3);
  EXPECT_EQ(0, *matrix_3x3 == matrix);
  EXPECT_EQ(1, *matrix_3x3 == *matrix_3x3);
}

TEST_F(S21MatrixTest, equalsOperator) {
  S21Matrix matrix;
  matrix = *matrix_3x3;
  EXPECT_EQ(1, *matrix_3x3 == matrix);
  matrix = *matrix_4x3;
  EXPECT_EQ(1, *matrix_4x3 == matrix);
}

TEST_F(S21MatrixTest, plusAndEqualsOperator) {
  S21Matrix result;
  result(0, 0) = 0;
  result(0, 1) = 2;
  result(0, 2) = 4;
  result(1, 0) = 6;
  result(1, 1) = 8;
  result(1, 2) = 10;
  result(2, 0) = 12;
  result(2, 1) = 14;
  result(2, 2) = 16;
  S21Matrix test_result;
  test_result = *matrix_3x3 + *matrix_3x3;
  *matrix_3x3 += *matrix_3x3;
  EXPECT_EQ(1, result == *matrix_3x3 && result == test_result);
}

TEST_F(S21MatrixTest, plusAndEqualsOperatorError) {
  EXPECT_THROW(*matrix_3x3 + *matrix_4x3, std::range_error);
}

TEST_F(S21MatrixTest, minusAndEqualsOperatorError) {
  EXPECT_THROW(*matrix_3x3 - *matrix_4x3, std::range_error);
}

TEST_F(S21MatrixTest, mulMatrixAndEqualsOperatorError) {
  EXPECT_THROW(*matrix_3x3 * *matrix_4x3, std::range_error);
}

TEST_F(S21MatrixTest, mulNumberAndEqualsOperator) {
  S21Matrix result;
  result(0, 0) = 0;
  result(0, 1) = 5;
  result(0, 2) = 10;
  result(1, 0) = 15;
  result(1, 1) = 20;
  result(1, 2) = 25;
  result(2, 0) = 30;
  result(2, 1) = 35;
  result(2, 2) = 40;
  S21Matrix test_result;
  test_result = *matrix_3x3 * 5;
  *matrix_3x3 *= 5;
  EXPECT_EQ(1, result == *matrix_3x3 && result == test_result);
}

TEST_F(S21MatrixTest, bracketsOperator) {
  EXPECT_EQ(0, (*matrix_3x3)(0, 0));
  EXPECT_EQ(1, (*matrix_3x3)(0, 1));
  EXPECT_EQ(2, (*matrix_3x3)(0, 2));
  EXPECT_EQ(3, (*matrix_3x3)(1, 0));
  EXPECT_EQ(4, (*matrix_3x3)(1, 1));
  EXPECT_EQ(5, (*matrix_3x3)(1, 2));
  EXPECT_EQ(6, (*matrix_3x3)(2, 0));
  EXPECT_EQ(7, (*matrix_3x3)(2, 1));
  EXPECT_EQ(8, (*matrix_3x3)(2, 2));
}

TEST_F(S21MatrixTest, bracketsOperatorError) {
  EXPECT_THROW((*matrix_3x3)(-1, 0), std::out_of_range);
  EXPECT_THROW((*matrix_3x3)(1, 4), std::out_of_range);
}

TEST_F(S21MatrixTest, bracketsOperatorConstError) {
  S21Matrix const matrix;
  EXPECT_THROW(matrix.operator()(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix.operator()(1, 4), std::out_of_range);
}

TEST_F(S21MatrixTest, trans) {
  S21Matrix result;
  S21Matrix temp;
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(0, 2) = 3;
  temp(1, 0) = 4;
  temp(1, 1) = 5;
  temp(1, 2) = 6;
  temp(2, 0) = 7;
  temp(2, 1) = 8;
  temp(2, 2) = 9;
  result = temp.Transpose();
  EXPECT_EQ(0, (temp == result));
}

TEST_F(S21MatrixTest, complements) {
  (*matrix_3x3)(0, 0) = -5;
  S21Matrix result;
  result(0, 0) = -3;
  result(0, 1) = 6;
  result(0, 2) = -3;
  result(1, 0) = 6;
  result(1, 1) = -52;
  result(1, 2) = 41;
  result(2, 0) = -3;
  result(2, 1) = 31;
  result(2, 2) = -23;
  S21Matrix test_result;
  test_result = matrix_3x3->CalcComplements();
  EXPECT_EQ(1, result == test_result);
}

TEST_F(S21MatrixTest, complementsError) {
  EXPECT_THROW(matrix_4x3->CalcComplements(), std::range_error);
}

TEST_F(S21MatrixTest, Determinant) {
  EXPECT_EQ(0, matrix_3x3->Determinant());
  (*matrix_3x3)(0, 0) = -5;
  EXPECT_EQ(15, matrix_3x3->Determinant());
  S21Matrix matrix_1x1(1, 1);
  matrix_1x1(0, 0) = 5;
  EXPECT_EQ(5, matrix_1x1.Determinant());
}

TEST_F(S21MatrixTest, DeterminantError) {
  EXPECT_THROW(matrix_4x3->Determinant(), std::range_error);
}

TEST_F(S21MatrixTest, inverse) {
  (*matrix_3x3)(0, 0) = 2;
  (*matrix_3x3)(0, 1) = 5;
  (*matrix_3x3)(0, 2) = 7;
  (*matrix_3x3)(1, 0) = 6;
  (*matrix_3x3)(1, 1) = 3;
  (*matrix_3x3)(1, 2) = 4;
  (*matrix_3x3)(2, 0) = 5;
  (*matrix_3x3)(2, 1) = -2;
  (*matrix_3x3)(2, 2) = -3;
  S21Matrix result;
  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;
  S21Matrix test_result;
  test_result = matrix_3x3->InverseMatrix();
  EXPECT_EQ(1, result == test_result);
}

TEST_F(S21MatrixTest, inverseError) {
  EXPECT_THROW(matrix_3x3->InverseMatrix(), std::range_error);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}