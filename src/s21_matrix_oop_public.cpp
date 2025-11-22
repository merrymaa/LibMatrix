#include "s21_matrix_oop.h"

int S21Matrix::getRow() { return rows_; }

int S21Matrix::getCols() { return cols_; }

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (!sizeEq(other)) return false;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double compare = fabs(matrix_[i][j] - other.matrix_[i][j]);
      if (compare > 0.0000001) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!sizeEq(other) || infNan(this) || infNan(other) || negativeSize(this) ||
      negativeSize(other))
    throw std::logic_error(
        "S21Matrix: the matrices are not equivalent or one of the values is "
        "equal to infinity");

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!sizeEq(other) || infNan(this) || infNan(other) || negativeSize(this) ||
      negativeSize(other))
    throw std::logic_error(
        "S21Matrix: the matrices are not equivalent or one of the values is "
        "equal to infinity");

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (infNan(this) || negativeSize(this))
    throw std::logic_error(
        "S21Matrix: One of the values is equal to infinity or error in size "
        "matrix");

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (notDimension(other) || infNan(this) || infNan(other))
    throw std::invalid_argument(
        "Different matrix dimensions or one of the values is equal to "
        "infinity");

  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix matrixTranspose(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrixTranspose.matrix_[j][i] = matrix_[i][j];
    }
  }
  return matrixTranspose;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_ || infNan(this))
    throw std::invalid_argument(
        "S21Matrix: the matrix is not square or one of the values is equal to "
        "infinity");

  double determinant = 0;
  int sign = 1;

  double **copy = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    copy[i] = new double[cols_];
  }

  for (int i = 0; i < rows_; ++i) {
    memcpy(copy[i], matrix_[i], cols_ * sizeof(double));
  }

  // transform matrix to triangular
  for (int i = 0, j = 0; i < rows_; i++, j++) {
    if (allZero(copy, i, j)) {
      for (int i = 0; i < rows_; i++) delete[] copy[i];
      delete[] copy;
      determinant = 0;
      return determinant;
    } else {
      if (copy[i][j] == 0) {
        int index_not_zero = notZero(copy, i, j);
        invertRows(copy, i, index_not_zero);
        sign *= -1;
      }

      for (int r = i; r < rows_; r++) {
        if (r > j && copy[i][j] != 0) {
          transformRow(copy, r, j);
        }
      }
    }
  }

  // calculate determinant
  determinant = 1.;
  for (int i = 0; i < rows_; i++) {
    determinant *= copy[i][i];
  }
  determinant *= sign;

  for (int i = 0; i < rows_; i++) delete[] copy[i];
  delete[] copy;

  return determinant;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_ || infNan(this))
    throw std::invalid_argument(
        "S21Matrix: the matrix is not square or one of the values is equal to "
        "infinity");
  S21Matrix result(rows_, cols_);

  if (rows_ == 1) {
    result.matrix_[0][0] = 1.;
    return result;
  }

  S21Matrix determinant(rows_ - 1, cols_ - 1);

  for (int minor_row = 0; minor_row < rows_ && rows_ > 1; minor_row++) {
    for (int minor_col = 0; minor_col < cols_; minor_col++) {
      recordDeterminantMatrix(determinant, minor_row, minor_col);
      result.matrix_[minor_row][minor_col] = determinant.Determinant();
    }
  }
  if (rows_ > 1) {
    algebraicComplements(result);
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) throw std::logic_error("Incorrect matrix");
  S21Matrix result(rows_, cols_);
  double determinant = this->Determinant();

  if (determinant) {
    result = CalcComplements();
    result = result.Transpose();
    double k = 1 / determinant;
    result.MulNumber(k);
  }
  // else // exception

  return result;
}