#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <cstring>
#include <iostream>
// #include <iomanip>  // для отладки

using std::cin;
using std::cout;
using std::endl;

class S21Matrix {
 private:
  // Attributes
  int rows_{1}, cols_{1};
  double **matrix_;

  // приватные методы
  bool sizeEq(const S21Matrix &other);
  bool negativeSize(const S21Matrix *matrix);
  bool negativeSize(const S21Matrix &matrix);
  bool infNan(const S21Matrix *matrix);
  bool infNan(const S21Matrix &matrix);
  bool notDimension(const S21Matrix &other);
  bool allZero(double **matrix, int r, int c);
  int notZero(double **matrix, int r, int c);
  void invertRows(double **matrix, int row1, int index_not_zero);
  void transformRow(double **matrix, int r, int j);
  void recordDeterminantMatrix(S21Matrix &determinant, int minor_row,
                               int minor_col);
  void algebraicComplements(S21Matrix &result);

 public:
  // конструкторы
  S21Matrix();
  S21Matrix(int rows, int col);

  // конструктор копирования
  S21Matrix(const S21Matrix &other);

  // конструктор перемещения
  S21Matrix(S21Matrix &&other);

  // деструктор
  ~S21Matrix();

  // публичные методы

  int getRow();
  int getCols();
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // операторы
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double digit);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  double &operator()(int i, int j);

  // для отладки
  void printMatrix() const;
  void setValue(int r, int c, double n);
};

#endif