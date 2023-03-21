#ifndef MATRIX_S21_MATRIX_OOP_H
#define MATRIX_S21_MATRIX_OOP_H

#include <cstring>
#include <cmath>
#include <stdexcept>

class S21Matrix {
private:
    // attributes
    int rows_, cols_;
    double **matrix_;

    void createMatrix();
    void removeMatrix();
    void recreateMatrix(const S21Matrix& other);
    void copyMatrix(const S21Matrix& other);
    void resizeMatrix(int rows, int cols);
    S21Matrix getMinorMatrix(int rows, int cols);

    bool isSquare() const;
    bool isEqualSize(const S21Matrix &other) const;

public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    int getRows() const;
    void setRows(int rows);
    int getCols() const;
    void setCols(int cols);

    bool operator==(const S21Matrix &other);
    S21Matrix& operator=(const S21Matrix& other);
    S21Matrix operator+=(const S21Matrix& other);
    S21Matrix operator+(const S21Matrix& other);
    S21Matrix operator-=(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*=(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix operator*=(const double num);
    S21Matrix operator*(const double num);
    double& operator()(int row, int col);
    double& operator()(int row, int col) const;

    // some public methods
    bool eqMatrix(const S21Matrix& other);
    void sumMatrix(const S21Matrix& other);
    void subMatrix(const S21Matrix& other);
    void mulNumber(const double num);
    void mulMatrix(const S21Matrix& other);
    S21Matrix transpose();
    S21Matrix calcComplements();
    double determinant();
    S21Matrix inverseMatrix();

    void toString();
};

#endif //  MATRIX_S21_MATRIX_OOP_H
