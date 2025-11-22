#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(Test_1, Default_constructor) {
  S21Matrix matrix;

  EXPECT_EQ(matrix.getRow(), 2);
  EXPECT_EQ(matrix.getCols(), 2);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 0.0);
}

TEST(Test_2, With_arguments) {
  S21Matrix matrix(3, 3);

  EXPECT_EQ(matrix.getRow(), 3);
  EXPECT_EQ(matrix.getCols(), 3);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 0.0);
}

TEST(Test_3, Constructor_copy) {
  S21Matrix matrix(3, 3);
  S21Matrix matrix2(matrix);

  EXPECT_EQ(matrix2.getRow(), 3);
  EXPECT_EQ(matrix2.getCols(), 3);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 0.0);
}

TEST(Test_4, Constructor_move) {
  S21Matrix original(2, 3);
  original(0, 0) = 10.5;
  original(1, 2) = -3.14;

  double val1 = original(0, 0);
  double val2 = original(1, 2);

  S21Matrix moved(std::move(original));

  EXPECT_EQ(moved.getRow(), 2);
  EXPECT_EQ(moved.getCols(), 3);
  EXPECT_DOUBLE_EQ(moved(0, 0), val1);
  EXPECT_DOUBLE_EQ(moved(1, 2), val2);
}

TEST(Test_5, Exception) { EXPECT_ANY_THROW(S21Matrix(-1, 99)); }

TEST(Test_6, Exception) { EXPECT_ANY_THROW(S21Matrix(2, -1)); }

TEST(Test_7, TestConstructorParams1) {
  S21Matrix matrix_check(5, 4);
  EXPECT_EQ(matrix_check.getRow(), 5);
  EXPECT_EQ(matrix_check.getCols(), 4);
}

TEST(Test_8, Assignment) {
  S21Matrix matrix(2, 2);

  matrix.setValue(1, 1, 5.0);

  matrix = matrix;
  EXPECT_EQ(matrix.getRow(), 2);
  EXPECT_EQ(matrix.getCols(), 2);

  EXPECT_DOUBLE_EQ(matrix(1, 1), 5.0);
}

TEST(Test_9, Assignment) {
  S21Matrix matrix(4, 4);

  matrix.setValue(1, 1, 5.0);
  S21Matrix matrix2(2, 2);

  matrix2 = matrix;
  EXPECT_EQ(matrix2.getRow(), 4);
  EXPECT_EQ(matrix2.getCols(), 4);

  EXPECT_DOUBLE_EQ(matrix(1, 1), 5.0);
}

TEST(Test_10, Assignment) {
  S21Matrix matrix(2, 2);

  matrix.setValue(1, 1, 5.0);
  S21Matrix matrix2(4, 4);

  matrix2 = matrix;
  EXPECT_EQ(matrix2.getRow(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);

  EXPECT_DOUBLE_EQ(matrix(1, 1), 5.0);
}

TEST(Test_11, Plus) {
  S21Matrix matrix(2, 2);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  S21Matrix matrix2(2, 2);
  matrix2.setValue(1, 1, 5.0);
  matrix2.setValue(0, 0, 3.0);

  S21Matrix matrix3(2, 2);
  matrix3 = matrix + matrix2;

  EXPECT_DOUBLE_EQ(matrix3(1, 1), 10.0);
  EXPECT_DOUBLE_EQ(matrix3(0, 0), 6.0);
}

TEST(Test_12, Minus) {
  S21Matrix matrix(2, 2);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  S21Matrix matrix2(2, 2);
  matrix2.setValue(1, 1, 6.0);
  matrix2.setValue(0, 0, 1.0);

  S21Matrix matrix3(2, 2);
  matrix3 = matrix - matrix2;

  EXPECT_DOUBLE_EQ(matrix3(1, 1), -1.0);
  EXPECT_DOUBLE_EQ(matrix3(0, 0), 2.0);
}

TEST(Test_13, Mul) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 4);
  S21Matrix result(3, 4);
  double data_A[9] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }
  double data_B[12] = {9., 8., 7., 2., 6., 5., 4., 3., 3., 2., 1., 3.};
  count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      B.setValue(i, j, data_B[count++]);
    }
  }
  double data_pattern[12] = {30., 24., 18.,  17.,  84., 69.,
                             54., 41., 138., 114., 90., 65.};
  result = A * B;
  count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_DOUBLE_EQ(result(i, j), data_pattern[count++]);
    }
  }
}

TEST(Test_14, Mul_Digit) {
  S21Matrix A(3, 3);

  S21Matrix result(3, 3);
  double data_A[9] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }

  result = A * 2.0;
  count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(result(i, j), (data_A[count++] * 2.0));
    }
  }
}

TEST(Test_15, Plus_Assignment) {
  S21Matrix matrix(2, 2);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  S21Matrix matrix2(2, 3);
  matrix2.setValue(1, 1, 5.0);
  matrix2.setValue(0, 0, 3.0);

  EXPECT_ANY_THROW(matrix += matrix2);
}

TEST(Test_16, Ravno) {
  S21Matrix matrix(2, 2);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  S21Matrix matrix2(2, 2);
  matrix2.setValue(1, 1, 5.0);
  matrix2.setValue(0, 0, 3.0);
  EXPECT_DOUBLE_EQ((matrix == matrix2), 1);
}
TEST(Test_17, Ravno_2) {
  S21Matrix matrix(2, 2);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  S21Matrix matrix2(2, 2);
  matrix2.setValue(1, 1, 5.0);
  matrix2.setValue(0, 1, 3.0);
  EXPECT_DOUBLE_EQ((matrix == matrix2), 0);
}

TEST(Test_18, Minus_Assignment) {
  S21Matrix matrix(2, 2);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  S21Matrix matrix2(2, 3);
  matrix2.setValue(1, 1, 5.0);
  matrix2.setValue(0, 0, 3.0);

  EXPECT_ANY_THROW(matrix -= matrix2);
}

TEST(Test_19, Mul_Assignment) {
  S21Matrix matrix(2, 2);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  S21Matrix matrix2(3, 3);
  matrix2.setValue(1, 1, 5.0);
  matrix2.setValue(0, 0, 3.0);

  EXPECT_ANY_THROW(matrix *= matrix2);
}

TEST(Test_20, Index_1) {
  S21Matrix matrix(3, 3);

  matrix(1, 1) = 2.0;
  EXPECT_DOUBLE_EQ(matrix(1, 1), 2.0);
}

TEST(Test_21, Index_2) {
  S21Matrix matrix(3, 3);

  EXPECT_ANY_THROW(matrix(1, 5) = 2.0);
}

TEST(Test_22, Index_3) {
  S21Matrix matrix(3, 3);
  matrix(1, 1) = 2.0;
  double res = matrix(1, 1);
  EXPECT_DOUBLE_EQ(res, 2.0);
}

TEST(Test_23, SumMatrix) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix2(2, 2);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  matrix2.setValue(1, 1, 5.0);
  matrix2.setValue(0, 0, 3.0);

  matrix.SumMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix(1, 1), 10.0);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 6.0);
}

TEST(Test_24, SumMatrixThrow) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix2(5, 5);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  matrix2.setValue(1, 1, 5.0);
  matrix2.setValue(0, 0, 3.0);

  EXPECT_ANY_THROW(matrix.SumMatrix(matrix2));
}

TEST(Test_25, SubMatrix) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix2(2, 2);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  matrix2.setValue(1, 1, 6.0);
  matrix2.setValue(0, 0, 2.0);

  matrix.SubMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix(1, 1), -1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
}

TEST(Test_26, SubMatrixThrow) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix2(5, 5);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  matrix2.setValue(1, 1, 5.0);
  matrix2.setValue(0, 0, 3.0);

  EXPECT_ANY_THROW(matrix.SubMatrix(matrix2));
}

TEST(Test_27, SubNumber) {
  S21Matrix matrix(2, 2);

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  matrix.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(matrix(1, 1), 10.0);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 6.0);
}

TEST(Test_28, SubNumberThrow) {
  S21Matrix matrix(2, 2);

  matrix(1, 0) = NAN;

  matrix.setValue(1, 1, 5.0);
  matrix.setValue(0, 0, 3.0);

  EXPECT_ANY_THROW(matrix.MulNumber(2.0));
}

TEST(Test_29, MulMatrix) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 4);

  double data_A[9] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }
  double data_B[12] = {9., 8., 7., 2., 6., 5., 4., 3., 3., 2., 1., 3.};
  count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      B.setValue(i, j, data_B[count++]);
    }
  }
  double data_pattern[12] = {30., 24., 18.,  17.,  84., 69.,
                             54., 41., 138., 114., 90., 65.};
  A.MulMatrix(B);
  count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_DOUBLE_EQ(A(i, j), data_pattern[count++]);
    }
  }
}

TEST(Test_30, MulMatrixThrow) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 2);

  double data_A[9] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }
  double data_B[4] = {9., 8., 7., 2.};
  count = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      B.setValue(i, j, data_B[count++]);
    }
  }

  EXPECT_ANY_THROW(A.MulMatrix(B));
}

TEST(Test_31, Transpose) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);

  double data_A[9] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }

  double data_pattern[9] = {1., 4., 7., 2., 5., 8., 3., 6., 9.};

  B = A.Transpose();
  count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(B(i, j), data_pattern[count++]);
    }
  }
}

TEST(Test_32, Determinant_1) {
  S21Matrix A(3, 3);

  double data_A[9] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }

  double pattern = 0;
  double result = A.Determinant();

  EXPECT_DOUBLE_EQ(result, pattern);
}

TEST(Test_33, Determinant_2) {
  S21Matrix A(3, 2);

  double data_A[9] = {1., 2., 3., 4., 5., 6.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }

  EXPECT_ANY_THROW(A.Determinant());
}

TEST(Test_34, Determinant_3) {
  S21Matrix A(3, 3);

  double data_A[9] = {1., 2., 3., 0, 5., 6., 0., 8., 9.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }

  double pattern = -3.0000000000000071;
  double result = A.Determinant();

  EXPECT_DOUBLE_EQ(result, pattern);
}

TEST(Test_35, Determinant_4) {
  S21Matrix A(3, 3);

  double data_A[9] = {1., 2., 3., 0, 5., 6., 0., 0., 9.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }

  double pattern = 45;
  double result = A.Determinant();

  EXPECT_DOUBLE_EQ(result, pattern);
}

TEST(Test_36, Determinant_5) {
  S21Matrix A(3, 3);

  double data_A[9] = {0., 1., 2., 3., 4., 5., 6., 7., 8.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }

  double pattern = 0;
  double result = A.Determinant();

  EXPECT_DOUBLE_EQ(result, pattern);
}

TEST(Test_37, Complements_1) {
  S21Matrix A(4, 4);
  S21Matrix result(4, 4);

  double data_A[16] = {112.0, 243.0, 3.0,  -8.0, 47.0,  51.0, -66.0, 99.0,
                       -74.0, 85.0,  97.0, 63.0, -13.0, 79.0, -99.0, -121.0};
  int count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }

  double data_pattern[16] = {-2879514.0, -1236631.0, -1685096.0, 880697.0,
                             1162090.0,  -714015.0,  4046255.0,  -3901600.0,
                             4362897.0,  -2049432.0, -532912.0,  -1370781.0,
                             3412773.0,  -1569493.0, 3144517.0,  1284666.0};

  result = A.CalcComplements();
  count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_DOUBLE_EQ(result(i, j), data_pattern[count++]);
    }
  }
}

TEST(Test_38, Complements_2) {
  S21Matrix A(4, 2);
  S21Matrix result(4, 2);

  double data_A[16] = {112.0, 243.0, 3.0, -8.0, 47.0, 51.0, -66.0, 99.0};
  int count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  };

  EXPECT_ANY_THROW(A.CalcComplements());
}

TEST(Test_39, Complements_1) {
  S21Matrix A(1, 1);
  A.CalcComplements();

  EXPECT_DOUBLE_EQ(A(0, 0), 0);
}

TEST(Test_40, InverseMatrix_1) {
  const double tolerance = 1e-6;
  S21Matrix A(3, 3);
  S21Matrix result(3, 3);

  double data_A[9] = {21., 2., 3., 34., 55., 6., 7., 8., 9.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }

  double data_pattern[9] = {0.052465,  0.000704,  -0.017958,
                            -0.030986, 0.019718,  -0.002817,
                            -0.013263, -0.018075, 0.127582};

  result = A.InverseMatrix();
  count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_NEAR(result(i, j), data_pattern[count++], tolerance);
    }
  }
}

TEST(Test_41, InverseMatrix_2) {
  S21Matrix A(3, 2);

  double data_A[6] = {21., 2., 3., 34., 55., 6.};
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      A.setValue(i, j, data_A[count++]);
    }
  }

  EXPECT_ANY_THROW(A.InverseMatrix());
}