#include "s21_matrix_oop.h"

// constructors, destructor
S21Matrix::S21Matrix() : rows_(2), cols_(2) {
  matrix_ = new double *[rows_];

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{0.0};
  }
}

S21Matrix::S21Matrix(int row, int col) : rows_(row), cols_(col) {
  if (row < 0 || col < 0)
    throw std::invalid_argument(
        "S21Matrix: col, row must not be less than zero");

  matrix_ = new double *[rows_];

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{0.0};
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  // cout << "конструктор копирования" << endl;

  matrix_ = new double *[rows_];

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)  // конструктор перемещения
{
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  // cout << "вызов деструктора объекта" << endl;
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}
