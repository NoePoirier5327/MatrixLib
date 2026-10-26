#include <gtest/gtest.h>
#include "../src/matrix/matrix.hpp"

TEST(MatrixTest, IsEqual) {
  Matrix A = Matrix(3, 3);
  Matrix B = Matrix(3, 3);

  EXPECT_TRUE(A == B);
}

TEST(MatrixTest, IsNotEqual) {
  Matrix A = Matrix(3, 3);
  Matrix B = Matrix(3, 3);
  A(1,1) = 9;

  EXPECT_FALSE(A == B);
}

TEST(MatrixTest, SumWithNull) {
  Matrix A = Matrix(3, 3);
  Matrix B = Matrix(3, 3);

  for (size_t i = 1; i <= A.get_nb_line(); ++i) {
    for (size_t j = 1; j <= A.get_nb_col(); ++j) {
      A(i, j) = static_cast<double>(i + j);
    }
  }

  // A + 0 = A
  EXPECT_EQ(A + B, A);
}

TEST(MatrixTest, SumWithNonNull) {
  Matrix A = Matrix(3, 3);
  Matrix B = Matrix(3, 3);
  Matrix C = Matrix(3, 3);

  for (size_t i = 1; i <= A.get_nb_line(); ++i) {
    for (size_t j = 1; j <= A.get_nb_col(); ++j) {
      A(i, j) = static_cast<double>(i+j);
      B(i, j) = static_cast<double>(i*i);
      C(i, j) = static_cast<double>((i + j) + (i * i));
    }
  }

  EXPECT_EQ(A + B, C);
}

TEST(MatrixTest, ProductWithNull) {
  Matrix A = Matrix(4, 4);
  Matrix B = Matrix(4, 2);
  Matrix C = Matrix(4, 2);

  for (size_t i = 1; i <= B.get_nb_line(); ++i)
    for (size_t j = 1; j <= B.get_nb_col(); ++j)
      B(i, j) = 8;

  EXPECT_EQ(A * B, C);
}

TEST(MatrixTest, ProductWithIdentity) {
  Matrix A = Matrix(2, 2);
  Matrix I = new_identity_matrix(2);

  for (size_t i = 1; i <= A.get_nb_line(); ++i)
    for (size_t j = 1; j <= A.get_nb_col(); ++j)
      A(i, j) = static_cast<double>(i * i + j);

  EXPECT_EQ(A * I, A);
  EXPECT_EQ(I * A, A);
}

TEST(MatrixTest, ProductWithScalar) {
  int a = 8; // Scalaire
  Matrix A = Matrix(5, 7);
  Matrix B = Matrix(5, 7);

  for (size_t i = 1; i <= A.get_nb_line(); ++i) {
    for (size_t j = 1; j <= A.get_nb_col(); ++j) {
      A(i, j) = static_cast<double>(i + j);
      B(i, j) = static_cast<double>(i + j) * a;
    }
  }

  EXPECT_EQ(A * a, B);
  EXPECT_EQ(a * A, B);
}

TEST(MatrixTest, AssignMatrices) {
  Matrix A = Matrix(8, 1);
  Matrix B = Matrix(5, 19);

  for (size_t i = 1; i <= B.get_nb_line(); ++i)
    for (size_t j = 1; j <= B.get_nb_col(); ++j)
      B(i, j) = static_cast<double>((j * 8) * (j * 8));

  A = B;
  EXPECT_EQ(A, B);
}
