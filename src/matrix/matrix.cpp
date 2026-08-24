#include "matrix.hpp"

#include <stdexcept>
#include <iostream>

Matrix::Matrix(size_t _width, size_t _height) {
  this->width = _width;
  this->height = _height;

  this->content = nullptr;
  this->content = new double [_width * _height];
  for (size_t i = 0; i < _width * _height; ++i) {
    this->content[i] = 0;
  }
}

Matrix::Matrix(const Matrix& m) {
  this->width = m.width;
  this->height = m.height;

  size_t total_size = m.width * m.height;
  this->content = new double [total_size];
  for (size_t i = 0; i < total_size; ++i) {
    this->content[i] = m.content[i];
  }
}

Matrix::Matrix(Matrix&& m) noexcept {
  this->width = m.width;
  this->height = m.height;
  this->content = m.content;

  m.width = 0;
  m.height = 0;
  m.content = nullptr;
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
  if (x >= this->width) {
    throw std::out_of_range("X index is out of range.");
  }

  if (y >= this->height) {
    throw std::out_of_range("Y index is out of range.");
  }

  return this->content[y * this->width + x];
}

double Matrix::operator()(size_t x, size_t y) const {
  if (x >= this->width) {
    throw std::out_of_range("X index is out of range.");
  }

  if (y >= this->height) {
    throw std::out_of_range("Y index is out of range.");
  }

  return this->content[y * this->width + x];
}

bool Matrix::operator==(const Matrix& m) const {
  if (this->width != m.width || this->height != m.height) {
    return false;
  }

  bool is_equal = true;

  for (size_t i = 0; i < this->width * this->height; ++i) {
    is_equal = (this->content[i] == m.content[i]) && is_equal;
  }

  return is_equal;
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

Matrix Matrix::operator*(double a) const {
  Matrix result = Matrix(this->width, this->height);

  size_t total_size = this->width * this->height;
  for (size_t i = 0; i < total_size; ++i) {
    result.content[i] = this->content[i] * a;
  }

  return result;
}

Matrix Matrix::operator+(const Matrix& m) const {
  if (this->width != m.width || this->height != m.height) {
    throw std::invalid_argument("Invalid dimensions for matrice sum.");
  }

  Matrix result = Matrix(this->width, this->height);

  for (size_t i = 0; i < this->width * this->height; ++i) {
    result.content[i] = this->content[i] + m.content[i];
  }

  return result;
}

Matrix& Matrix::operator=(const Matrix& m) {
  if (this == &m) {
    return *this;
  }

  // On créer un nouveau tableau
  delete[] this->content;
  size_t total_size = m.width * m.height;
  this->content = new double [total_size];

  // On copie le tableau en paramètre dans notre nouveau tableau
  for (size_t i = 0; i < total_size; ++i) {
    this->content[i] = m.content[i];
  }

  this->width = m.width;
  this->height = m.height;

  return *this;
}

Matrix& Matrix::operator=(Matrix&& m) noexcept {
  if (this == &m) {
    return *this;
  }

  delete[] this->content;

  this->width = m.width;
  this->height = m.height;
  this->content = m.content;

  m.width = 0;
  m.height = 0;
  m.content = nullptr;

  return *this;
}

void Matrix::display() const {
  for (size_t i = 0; i < this->width * this->height; ++i) {
    if (i % this->width == 0) {
      std::cout << std::endl;
    }

    std::cout << this->content[i] << " ";
  }

  std::cout << std::endl;
}

Matrix new_identity_matrix(size_t n) {
  Matrix I = Matrix(n, n);

  for (size_t i = 0; i < n; ++i) {
    I(i, i) = 1.0f;
  }

  return I;
}
