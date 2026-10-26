#include "matrix/matrix.hpp"

int main() {
  Matrix A = Matrix(3, 3);

  for (size_t i = 1; i <= 3; ++i)
    A(i, i) = 3.14;
  A.display();

  return 0;
}
