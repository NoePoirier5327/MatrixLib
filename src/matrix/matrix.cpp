#include "matrix.hpp"

#include <stdexcept>

Matrix::Matrix(size_t _width, size_t _height) {
  this->width = _width;
  this->height = _height;

  this->content = nullptr;
  this->content = new double [_width * _height];
  for (size_t i = 0; i < _width * _height; ++i) {
    this->content[i] = 0;
  }
}

Matrix::~Matrix() {
  if (this->content != nullptr) {
    delete[] this->content;
    this->content = nullptr;
  }
}

size_t Matrix::get_width() const {
  return this->width;
}

size_t Matrix::get_height() const {
  return this->height;
}

double& Matrix::operator()(size_t x, size_t y) {
  if (x < this->width) {
    throw std::out_of_range("X index is out of range.");
  }

  if (y < this->height) {
    throw std::out_of_range("Y index is out of range.");
  }

  return this->content[y * this->width + x];
}

double Matrix::operator()(size_t x, size_t y) const {
  if (x < this->width) {
    throw std::out_of_range("X index is out of range.");
  }

  if (y < this->height) {
    throw std::out_of_range("Y index is out of range.");
  }

  return this->content[y * this->width + x];
}

// TODO Trouver une version plus optimisée que O(n^3)
Matrix Matrix::operator*(const Matrix& m) const {
  if (this->height != m.width) {
    throw std::invalid_argument("Invalid dimensions for matrice product.");
  }

  Matrix result = Matrix(this->width, m.height);

  for (size_t i = 0; i < this->width; ++i) {
    for (size_t j = 0; j < m.height; ++j) {
      for (size_t k = 0; k < this->height; ++k) {
        result(i, j) += (*this)(i, k) * m(k, j);
      }
    }
  }

  return result;
}
