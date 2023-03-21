#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) throw std::out_of_range("Error: Wrong matrix size");
  matrix_ = nullptr;
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = nullptr;
  CreateMatrix();
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  rows_ = std::exchange(other.rows_, 0);
  cols_ = std::exchange(other.cols_, 0);
  matrix_ = std::exchange(other.matrix_, nullptr);
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

int S21Matrix::get_rows() const { return rows_; }

void S21Matrix::set_rows(int rows) {
  if (rows < 1) throw std::out_of_range("Error: Wrong rows size");
  if (rows != rows_) {
    int temp = rows_;
    ResizeMatrix(rows, cols_);
    for (auto row = 0; row < rows_; row++) {
      for (auto col = 0; col < cols_; col++) {
        if (row >= temp) matrix_[row][col] = 0;
      }
    }
  }
}

int S21Matrix::get_cols() const { return cols_; }

void S21Matrix::set_cols(int cols) {
  if (cols < 1) throw std::out_of_range("Error: Wrong cols size");
  if (cols != cols_) {
    int temp = cols_;
    ResizeMatrix(rows_, cols);
    for (auto row = 0; row < rows_; row++) {
      for (auto col = 0; col < cols_; col++) {
        if (col >= temp) matrix_[row][col] = 0;
      }
    }
  }
}

void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_];
  for (auto row = 0; row < rows_; row++) matrix_[row] = new double[cols_]();
}

void S21Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (auto row = 0; row < rows_; row++) {
      if (matrix_[row] != nullptr) {
        delete[] matrix_[row];
        matrix_[row] = nullptr;
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

void S21Matrix::RecreateMatrix(const S21Matrix &other) {
  RemoveMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  for (auto row = 0; row < rows_; row++)
    std::memcpy(matrix_[row], other.matrix_[row], cols_ * sizeof(double));
}

void S21Matrix::ResizeMatrix(int rows, int cols) {
  S21Matrix result(rows, cols);
  int minRow = (rows < rows_) ? rows : rows_;
  int minCol = (cols < cols_) ? cols : cols_;
  for (auto row = 0; row < minRow; row++)
    std::memcpy(result.matrix_[row], matrix_[row], minCol * sizeof(double));
  *this = std::move(result);
}

S21Matrix S21Matrix::GetMinorMatrix(int rows, int cols) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (auto row = 0, row_n = 0; row < rows_; row++) {
    if (row == rows) continue;
    for (auto col = 0, col_n = 0; col < cols_; col++) {
      if (col == cols) continue;
      minor.matrix_[row_n][col_n] = matrix_[row][col];
      col_n++;
    }
    row_n++;
  }
  return minor;
}

bool S21Matrix::IsSquare() const { return (rows_ == cols_); }

bool S21Matrix::IsEqualSize(const S21Matrix &other) const {
  return (rows_ == other.rows_ && cols_ == other.cols_);
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix &other) const {
  return !EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (&other != this) {
    if (!IsEqualSize(other)) {
      RecreateMatrix(other);
    }
    CopyMatrix(other);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (&other != this) {
    RemoveMatrix();
    rows_ = std::exchange(other.rows_, 0);
    cols_ = std::exchange(other.cols_, 0);
    matrix_ = std::exchange(other.matrix_, nullptr);
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result(*this);
  return result += other;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result(*this);
  return result -= other;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result(*this);
  return result *= other;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix operator*(double num, S21Matrix &other) {
  S21Matrix result(other);
  return result *= num;
}

S21Matrix operator*(S21Matrix &other, double num) {
  S21Matrix result(other);
  return result *= num;
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("Error: index is out of range");
  return matrix_[row][col];
}

const double &S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("Error: index is out of range");
  return matrix_[row][col];
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool result = false;
  if (this == &other) {
    result = true;
  } else if (IsEqualSize(other)) {
    result = true;
    for (auto row = 0; row < rows_; row++) {
      for (auto col = 0; col < cols_; col++) {
        if (matrix_[row][col] != other.matrix_[row][col]) {
          result = false;
        }
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!IsEqualSize(other))
    throw std::range_error("Error: Matrices should have the same size");
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < cols_; col++) {
      matrix_[row][col] += other.matrix_[row][col];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!IsEqualSize(other))
    throw std::range_error("Error: Matrices should have the same size");
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < cols_; col++) {
      matrix_[row][col] -= other.matrix_[row][col];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < cols_; col++) {
      matrix_[row][col] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::range_error(
        "Error: the number of columns of the first "
        "matrix is not equal to the number of rows of the second matrix");
  S21Matrix result(rows_, other.cols_);
  for (auto row = 0; row < result.rows_; row++) {
    for (auto col = 0; col < result.cols_; col++) {
      for (auto row_t = 0; row_t < cols_; row_t++) {
        result.matrix_[row][col] +=
            matrix_[row][row_t] * other.matrix_[row_t][col];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < cols_; col++) {
      result.matrix_[col][row] = matrix_[row][col];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (!IsSquare() || rows_ < 2)
    throw std::range_error("Error: matrix is not square");
  S21Matrix result(rows_, cols_);
  for (auto row = 0; row < rows_; row++) {
    for (auto col = 0; col < cols_; col++) {
      double det = GetMinorMatrix(row, col).Determinant();
      result.matrix_[row][col] = det * pow(-1, row + col);
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (!IsSquare()) throw std::range_error("Error: matrix is not square");
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    for (auto col = 0; col < cols_; col++) {
      S21Matrix minor(GetMinorMatrix(0, col));
      result += pow(-1, col) * matrix_[0][col] * minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (fabs(det) < 1e-6)
    throw std::range_error("Error: matrix Determinant is zero");
  S21Matrix transpose_matrix(CalcComplements().Transpose());
  return transpose_matrix * (1. / det);
}
