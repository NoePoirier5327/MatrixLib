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
  A(0,0) = 9;

  EXPECT_FALSE(A == B);
}

TEST(MatrixTest, SumWithNull) {
  Matrix A = Matrix(3, 3);
  Matrix B = Matrix(3, 3);

  for (size_t i = 0; i < A.get_width(); ++i) {
    for (size_t j = 0; j < A.get_height(); ++j) {
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

  for (size_t i = 0; i < A.get_width(); ++i) {
    for (size_t j = 0; j < A.get_height(); ++j) {
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

  for (size_t i = 0; i < B.get_width(); ++i) {
    for (size_t j = 0; j < B.get_height(); ++j) {
      B(i, j) = 8;
    }
  }

  EXPECT_EQ(A * B, C);
}

TEST(MatrixTest, ProductWithIdentity) {
  Matrix A = Matrix(2, 2);
  Matrix I = new_identity_matrix(2);

  for (size_t i = 0; i < A.get_width(); ++i) {
    for (size_t j = 0; j < A.get_height(); ++j) {
      A(i, j) = static_cast<double>(i * i + j);
    }
  }

  EXPECT_EQ(A * I, A);
  EXPECT_EQ(I * A, A);
}
