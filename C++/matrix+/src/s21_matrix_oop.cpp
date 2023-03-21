#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows < 1 || cols < 1)
        throw std::out_of_range("Error: Wrong matrix size");
    this->matrix_ = nullptr;
    this->createMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
    this->matrix_ = nullptr;
    this->createMatrix();
    this->copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) : S21Matrix(other) {
    other.removeMatrix();
    other.cols_ = 0;
    other.rows_ = 0;
}

S21Matrix::~S21Matrix() {
    this->removeMatrix();
}

int S21Matrix::getRows() const {
    return rows_;
}

void S21Matrix::setRows(int rows) {
    if (rows < 1)
        throw std::out_of_range("Error: Wrong rows size");
    if (rows != this->rows_)
        this->resizeMatrix(rows, this->cols_);
}

int S21Matrix::getCols() const {
    return cols_;
}

void S21Matrix::setCols(int cols) {
    if (cols < 1)
        throw std::out_of_range("Error: Wrong cols size");
    if (cols != this->cols_)
        this->resizeMatrix(this->rows_, cols);
}

void S21Matrix::createMatrix() {
    this->matrix_ = new double*[this->rows_];
    for (size_t row = 0; row < this->rows_; row++)
        this->matrix_[row] = new double[this->cols_];
}

void S21Matrix::removeMatrix() {
    if (this->matrix_ != nullptr) {
        for (size_t row = 0; row < this->rows_; row++) {
            if (this->matrix_[row] != nullptr) {
                delete[] this->matrix_[row];
                this->matrix_[row] = nullptr;
            }
        }
        delete[] this->matrix_;
        this->matrix_ = nullptr;
    }
}

void S21Matrix::recreateMatrix(const S21Matrix &other) {
    this->removeMatrix();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->createMatrix();
}

void S21Matrix::copyMatrix(const S21Matrix &other) {
    for (auto row = 0; row < this->rows_; row++)
        std::memcpy(this->matrix_[row], other.matrix_[row], this->cols_ * sizeof(double));
}

void S21Matrix::resizeMatrix(int rows, int cols) {
    S21Matrix result(rows, cols);
    int minRow = (rows < this->rows_) ? rows : this->rows_;
    int minCol = (cols < this->cols_) ? cols : this->cols_;
    for (auto row = 0; row < minRow; row++)
        std::memcpy(result.matrix_[row], this->matrix_[row], minCol * sizeof(double));
    *this = result;
}

S21Matrix S21Matrix::getMinorMatrix(int rows, int cols) {
    S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
    for (auto row = 0, rowN = 0; row < this->rows_; row++) {
        if (row == rows)
            continue;
        for (auto col = 0, colN = 0; col < this->cols_; col++) {
            if (col == cols)
                continue;
            minor.matrix_[rowN][colN] = this->matrix_[row][col];
            colN++;
        }
        rowN++;
    }
    return minor;
}

bool S21Matrix::isSquare() const {
    return (this->rows_ == this->cols_);
}

bool S21Matrix::isEqualSize(const S21Matrix &other) const {
    return (this->rows_ == other.rows_ && this->cols_ == other.cols_);
}

bool S21Matrix::operator==(const S21Matrix &other) {
    return this->eqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
    if (&other != this) {
        if (!this->isEqualSize(other)) {
            this->recreateMatrix(other);
        }
        this->copyMatrix(other);
    }
    return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
    this->sumMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
    S21Matrix result(*this);
    result.sumMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
    this->subMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
    S21Matrix result(*this);
    result.subMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
    this->mulMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
    S21Matrix result(*this);
    result.mulMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator*=(const double num) {
    this->mulNumber(num);
    return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix result(*this);
    result.mulNumber(num);
    return result;
}

double &S21Matrix::operator()(int row, int col) {
    if (row < 0 || col < 0 || row >= this->rows_ || col >= this->cols_)
        throw std::out_of_range("Error: index is out of range");
    return this->matrix_[row][col];
}

double &S21Matrix::operator()(int row, int col) const {
    if (row < 0 || col < 0 || row >= this->rows_ || col >= this->cols_)
        throw std::out_of_range("Error: index is out of range");
    return this->matrix_[row][col];
}

bool S21Matrix::eqMatrix(const S21Matrix &other) {
    bool result = false;
    if (this == &other) {
        result = true;
    } else if (this->isEqualSize(other)) {
        result = true;
        for (auto row = 0; row < this->rows_; row++) {
            for (auto col = 0; col < this->cols_; col++) {
                if (this->matrix_[row][col] != other.matrix_[row][col]) {
                    result = false;
                }
            }
        }
    }
    return result;
}

void S21Matrix::sumMatrix(const S21Matrix &other) {
    if (!this->isEqualSize(other))
        throw std::range_error("Error: Matrices should have the same size");
    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < this->cols_; col++) {
            this->matrix_[row][col] += other.matrix_[row][col];
        }
    }
}

void S21Matrix::subMatrix(const S21Matrix &other) {
    if (!this->isEqualSize(other))
        throw std::range_error("Error: Matrices should have the same size");
    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < this->cols_; col++) {
            this->matrix_[row][col] -= other.matrix_[row][col];
        }
    }
}

void S21Matrix::mulNumber(const double num) {
    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < this->cols_; col++) {
            this->matrix_[row][col] *= num;
        }
    }
}

void S21Matrix::mulMatrix(const S21Matrix &other) {
    if (this->cols_ != other.rows_)
        throw std::range_error("Error: the number of columns of the first "
        "matrix is not equal to the number of rows of the second matrix");
    S21Matrix result(this->rows_, this->cols_);
    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < other.cols_; col++) {
            for (auto row_t = 0; row_t < other.rows_; row_t++) {
                result.matrix_[row][col] += this->matrix_[row][row_t] * other.matrix_[row_t][col];
            }
        }
    }
    *this = result;
}

S21Matrix S21Matrix::transpose() {
    S21Matrix result(this->cols_, this->rows_);
    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < this->cols_; col++) {
            result.matrix_[col][row] = this->matrix_[row][col];
        }
    }
    return result;
}

S21Matrix S21Matrix::calcComplements() {
    if (!this->isSquare())
        throw std::range_error("Error: matrix is not square");
    S21Matrix result(this->rows_, this->cols_);
    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < this->cols_; col++) {
            S21Matrix minor(this->getMinorMatrix(row, col));
            double det = minor.determinant();
            result.matrix_[row][col] = det * pow(-1, row + col);
        }
    }
    return result;
}

double S21Matrix::determinant() {
    if (!this->isSquare())
        throw std::range_error("Error: matrix is not square");
    double result = 0.0;
    if (this->rows_ == 1) {
        result = this->matrix_[0][0];
    } else if (this->rows_ == 2) {
        result = this->matrix_[0][0] * this->matrix_[1][1] -
                 this->matrix_[1][0] * this->matrix_[0][1];
    } else {
        for (auto col = 0; col < this->cols_; col++) {
            S21Matrix minor(this->getMinorMatrix(0, col));
            result += pow(-1, col) * this->matrix_[0][col] * minor.determinant();
        }
    }
    return result;
}

S21Matrix S21Matrix::inverseMatrix() {
    double det = this->determinant();
    if (det == 0)
        throw std::range_error("Error: matrix determinant is zero");
    S21Matrix compMatrix(this->calcComplements());
    S21Matrix transposeMatrix(compMatrix.transpose());
    return transposeMatrix * (1. / det);
}

void S21Matrix::toString() {
  for (auto row = 0; row < this->rows_; row++) {
    for (auto col = 0; col < this->cols_; col++) {
      printf("%lf ", this->matrix_[row][col]);
    }
    printf("\n");
  }
}
