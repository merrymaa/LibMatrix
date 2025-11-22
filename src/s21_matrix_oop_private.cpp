#include "s21_matrix_oop.h"

bool S21Matrix::sizeEq(const S21Matrix &other) {
  return cols_ == other.cols_ && rows_ == other.rows_;
}

bool S21Matrix::negativeSize(const S21Matrix *matrix) {
  if (matrix->rows_ <= 0 || matrix->cols_ <= 0)
    return true;
  else
    return false;
}

bool S21Matrix::negativeSize(const S21Matrix &matrix) {
  if (matrix.rows_ <= 0 || matrix.cols_ <= 0)
    return true;
  else
    return false;
}

bool S21Matrix::infNan(const S21Matrix *matrix) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::isinf(matrix->matrix_[i][j]) ||
          std::isnan(matrix->matrix_[i][j]))
        return true;
    }
  }
  return false;
}

bool S21Matrix::infNan(const S21Matrix &matrix) {
  for (int i = 0; i < matrix.rows_; i++) {
    for (int j = 0; j < matrix.cols_; j++) {
      if (std::isinf(matrix.matrix_[i][j]) || std::isnan(matrix.matrix_[i][j]))
        return true;
    }
  }
  return false;
}

bool S21Matrix::notDimension(const S21Matrix &other) {
  if (cols_ != other.rows_) return true;
  return false;
}

bool S21Matrix::allZero(double **matrix, int r, int c) {
  for (; r < rows_; r++)
    if (matrix[r][c] != 0) return false;
  return true;
}

int S21Matrix::notZero(double **matrix, int r, int c) {
  for (; r < rows_; r++) {
    if (matrix[r][c] != 0) return r;
  }

  return 0;
}

void S21Matrix::invertRows(double **matrix, int row1, int index_not_zero) {
  if (row1 == index_not_zero) return;
  double *tmp = matrix[row1];
  matrix[row1] = matrix[index_not_zero];
  matrix[index_not_zero] = tmp;
}

void S21Matrix::transformRow(double **matrix, int r, int j) {
  double delta = matrix[r][j] / matrix[j][j];
  for (int c = j; c < cols_; c++) {
    double tmp = matrix[j][c] * delta;
    matrix[r][c] -= tmp;
  }
}

void S21Matrix::recordDeterminantMatrix(S21Matrix &determinant, int minor_row,
                                        int minor_col) {
  for (int src_row = 0, det_rows = 0; src_row < rows_; src_row++) {
    for (int src_col = 0, det_col = 0; src_col < cols_; src_col++) {
      if (src_row != minor_row && src_col != minor_col) {
        determinant.matrix_[det_rows][det_col] = matrix_[src_row][src_col];
        det_col++;

        if (det_col == determinant.cols_) {
          det_rows++;
          det_col = 0;
        }
      }
    }
  }
}

void S21Matrix::algebraicComplements(S21Matrix &result) {
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      if ((n + m) % 2) {
        result.matrix_[m][n] *= -1;
      }
    }
  }
}

// для печати матрицы
// void S21Matrix::printMatrix() const {
//   for (int i = 0; i < rows_; ++i) {
//     for (int j = 0; j < cols_; ++j) {
//       cout << std::setw(12) << std::fixed << std::setprecision(6)
//            << matrix_[i][j] << " ";
//     }
//     cout << endl;
//   }
// }

void S21Matrix::setValue(int r, int c, double n) { matrix_[r][c] = n; }