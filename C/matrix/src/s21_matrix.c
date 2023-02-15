#include "s21_matrix.h"

int matrix_check(matrix_t *A) {
  int res = 0;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    res = 1;
  }
  return res;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (rows > 0 && columns > 0 && result != NULL) {
    result->columns = columns;
    result->rows = rows;
    result->matrix = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      (result->matrix)[i] = malloc(sizeof(double) * columns);
      for (int j = 0; j < columns; ++j) {
        result->matrix[i][j] = 0;
      }
    }
  } else {
    if (result != NULL) {
      result->matrix = NULL;
    }
    error = INPUT_ERROR;
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
    A = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 1;
  if (matrix_check(A) && matrix_check(B) && A->rows == B->rows &&
      A->columns == B->columns && A->matrix && B->matrix) {
    for (int i = 0; i < A->rows && res; ++i)
      for (int j = 0; j < A->columns && res; j++)
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 10e-7) {
          res = 0;
        }
  } else {
    res = 0;
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OPERATION_SUCCESS;
  if (matrix_check(A) && matrix_check(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        for (int i = 0; i < A->rows; ++i) {
          for (int j = 0; j < A->columns; ++j) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      } else {
        error = EXECUTION_ERROR;
      }
    } else {
      error = EXECUTION_ERROR;
    }
  } else {
    error = INPUT_ERROR;
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OPERATION_SUCCESS;
  if (matrix_check(A) && matrix_check(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        for (int i = 0; i < A->rows; ++i) {
          for (int j = 0; j < A->columns; ++j) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      } else {
        error = EXECUTION_ERROR;
      }
    } else {
      error = EXECUTION_ERROR;
    }
  } else {
    error = INPUT_ERROR;
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OPERATION_SUCCESS;
  if (matrix_check(A)) {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows; ++i)
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
    } else {
      error = EXECUTION_ERROR;
    }
  } else {
    error = INPUT_ERROR;
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OPERATION_SUCCESS;
  if (matrix_check(A) && matrix_check(B)) {
    if (A->rows == B->columns && A->columns == B->rows &&
        !s21_create_matrix(A->rows, B->columns, result)) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < B->rows; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      error = EXECUTION_ERROR;
    }
  } else {
    error = INPUT_ERROR;
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OPERATION_SUCCESS;
  if (matrix_check(A)) {
    if (!s21_create_matrix(A->columns, A->rows, result)) {
      for (int i = 0; i < A->rows; ++i)
        for (int j = 0; j < A->columns; j++)
          result->matrix[j][i] = A->matrix[i][j];
    } else {
      error = EXECUTION_ERROR;
    }
  } else {
    error = INPUT_ERROR;
  }
  return error;
}

int get_minor(matrix_t *A, int m, int n, double *result) {
  matrix_t temp;
  int err = OPERATION_SUCCESS;
  if (!s21_create_matrix(A->rows - 1, A->rows - 1, &temp)) {
    int x = 0, y;
    for (int i = 0; i < A->rows; ++i) {
      if (i != m) {
        y = 0;
        for (int j = 0; j < A->columns; ++j) {
          if (j != n) {
            temp.matrix[x][y] = A->matrix[i][j];
            y++;
          }
        }
        x++;
      }
    }
    err = s21_determinant(&temp, result);
  } else {
    err = EXECUTION_ERROR;
  }
  s21_remove_matrix(&temp);
  return err;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = OPERATION_SUCCESS;
  double res = 0;
  if (matrix_check(A)) {
    if (A->rows == A->columns && !s21_create_matrix(A->rows, A->rows, result)) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->rows; j++) {
          err = get_minor(A, i, j, &res);
          if ((i + j) % 2 == 1) {
            res *= -1;
          }
          result->matrix[i][j] = res;
        }
      }
    } else {
      err = EXECUTION_ERROR;
    }
  } else {
    err = INPUT_ERROR;
  }
  return err;
}

void get_cofactor(double **m, double **tmp, int skip_row, int skip_col,
                  int size) {
  for (int i = 0, row = 0; row < size; row++) {
    for (int j = 0, col = 0; col < size; col++) {
      if (row != skip_row && col != skip_col) {
        tmp[i][j] = m[row][col];
        j++;
        if (j == size - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}

double det(double **m, int size) {
  double res = 0;

  if (size == 1) {
    res = m[0][0];
  } else {
    matrix_t temp = {0};
    if (!s21_create_matrix(size, size, &temp)) {
      int sign = 1;
      for (int i = 0; i < size; i++) {
        get_cofactor(m, temp.matrix, 0, i, size);
        res += sign * m[0][i] * det(temp.matrix, size - 1);
        sign = -sign;
      }
    } else {
      res = EXECUTION_ERROR;
    }
    s21_remove_matrix(&temp);
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = OPERATION_SUCCESS;
  if (matrix_check(A) && result) {
    if (A->rows == A->columns) {
      if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else if (A->rows == 2) {
        *result = A->matrix[0][0] * A->matrix[1][1] -
                  A->matrix[1][0] * A->matrix[0][1];
      } else {
        *result = det(A->matrix, A->rows);
      }
    } else {
      error = EXECUTION_ERROR;
    }
  } else {
    error = INPUT_ERROR;
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = OPERATION_SUCCESS;
  err = s21_create_matrix(A->rows, A->columns, result);
  if (matrix_check(A)) {
    if (A->rows == A->columns) {
      double det = 0;
      matrix_t temp;
      err = (err) ? err : s21_mult_number(A, 1, &temp);
      err = (err) ? err : s21_determinant(&temp, &det);
      s21_remove_matrix(&temp);
      if (!err && det != 0 && det == det) {
        matrix_t temp2;
        err = (err) ? err : s21_calc_complements(A, &temp2);
        err = (err) ? err : s21_transpose(&temp2, &temp);
        s21_remove_matrix(result);
        err = (err) ? err : s21_mult_number(&temp, 1 / det, result);
        s21_remove_matrix(&temp);
        s21_remove_matrix(&temp2);
      } else {
        err = EXECUTION_ERROR;
      }
      err = (err) ? EXECUTION_ERROR : 0;
    } else {
      err = EXECUTION_ERROR;
    }
  } else {
    err = INPUT_ERROR;
  }
  return err;
}
