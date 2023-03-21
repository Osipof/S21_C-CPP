#ifndef MATRIX_S21_MATRIX_OOP_H
#define MATRIX_S21_MATRIX_OOP_H

#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <utility>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  void CreateMatrix();
  void RemoveMatrix();
  void RecreateMatrix(const S21Matrix& other);
  void CopyMatrix(const S21Matrix& other);
  void ResizeMatrix(int rows, int cols);
  S21Matrix GetMinorMatrix(int rows, int cols) const;

  bool IsSquare() const;
  bool IsEqualSize(const S21Matrix& other) const;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int get_rows() const;
  void set_rows(int rows);
  int get_cols() const;
  void set_cols(int cols);

  bool operator==(const S21Matrix& other) const;
  bool operator!=(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix& operator*=(double num);
  friend S21Matrix operator*(S21Matrix& other, double num);
  friend S21Matrix operator*(double num, S21Matrix& other);

  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
};

#endif  //  MATRIX_S21_MATRIX_OOP_H
