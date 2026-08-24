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
