#include "matrix.hpp"

#include <stdexcept>
#include <iostream>
#include <iomanip>

Matrix::Matrix(size_t nb_line, size_t nb_col) {
  this->_nb_col = nb_col;
  this->_nb_line = nb_line;

  this->_content = nullptr;
  size_t total_size = nb_line * nb_col;
  this->_content = new double [total_size];
  for (size_t i = 0; i < total_size; ++i) {
    this->_content[i] = 0;
  }
}

Matrix::Matrix(const Matrix& m) {
  this->_nb_col = m._nb_col;
  this->_nb_line = m._nb_line;

  size_t total_size = m._nb_line * m._nb_col;
  this->_content = new double [total_size];
  for (size_t i = 0; i < total_size; ++i) {
    this->_content[i] = m._content[i];
  }
}

Matrix::Matrix(Matrix&& m) noexcept {
  this->_nb_line = m._nb_line;
  this->_nb_col = m._nb_col;
  this->_content = m._content;

  m._nb_line = 0;
  m._nb_col = 0;
  m._content = nullptr;
}

Matrix::~Matrix() {
  if (this->_content != nullptr) {
    delete[] this->_content;
    this->_content = nullptr;
  }
}

size_t Matrix::get_nb_line() const {
  return this->_nb_line;
}

size_t Matrix::get_nb_col() const {
  return this->_nb_col;
}

double& Matrix::operator()(size_t line, size_t col) {
  return this->_content[this->to_linear_coordinate(line, col)];
}

double Matrix::operator()(size_t line, size_t col) const {
  return this->_content[this->to_linear_coordinate(line, col)];
}

bool Matrix::operator==(const Matrix& m) const {
  if (this->_nb_col != m._nb_col || this->_nb_line != m._nb_line) {
    return false;
  }

  bool is_equal = true;

  size_t total_size = this->_nb_col * this->_nb_line;
  for (size_t i = 0; i < total_size; ++i) {
    is_equal = (this->_content[i] == m._content[i]) && is_equal;
  }

  return is_equal;
}

// TODO Trouver une version plus optimisée que O(n^3)
Matrix Matrix::operator*(const Matrix& m) const {
  if (this->get_nb_col() != m.get_nb_line()) {
    throw std::invalid_argument("Invalid dimensions for matrice product.");
  }

  Matrix result = Matrix(this->get_nb_line(), m.get_nb_col());

  for (size_t i = 1; i <= result.get_nb_line(); ++i) {
    for (size_t j = 1; j <= result.get_nb_col(); ++j) {
      for (size_t k = 1; k <= this->get_nb_col(); ++k) {
        result(i, j) += (*this)(i, k) * m(k, j);
      }
    }
  }

  return result;
}

Matrix Matrix::operator+(const Matrix& m) const {
  if (this->get_nb_line() != m.get_nb_line() || this->get_nb_col() != m.get_nb_col()) {
    throw std::invalid_argument("Invalid dimensions for matrice sum.");
  }

  Matrix result = Matrix(this->get_nb_line(), this->get_nb_col());

  size_t total_size = this->get_nb_line() * this->get_nb_col();
  for (size_t i = 0; i < total_size; ++i) {
    result._content[i] = this->_content[i] + m._content[i];
  }

  return result;
}

Matrix& Matrix::operator=(const Matrix& m) {
  if (this == &m) {
    return *this;
  }

  // On créer un nouveau tableau
  delete[] this->_content;
  size_t total_size = m.get_nb_col() * m.get_nb_line();
  this->_content = new double [total_size];

  // On copie le tableau en paramètre dans notre nouveau tableau
  for (size_t i = 0; i < total_size; ++i) {
    this->_content[i] = m._content[i];
  }

  this->_nb_line = m._nb_line;
  this->_nb_col = m._nb_col;

  return *this;
}

Matrix& Matrix::operator=(Matrix&& m) noexcept {
  if (this == &m) {
    return *this;
  }

  delete[] this->_content;

  this->_nb_col = m._nb_col;
  this->_nb_line = m._nb_line;
  this->_content = m._content;

  m._nb_col = 0;
  m._nb_line = 0;
  m._content = nullptr;

  return *this;
}

void Matrix::display() const {
  size_t total_size = this->_nb_line * this->_nb_col;
  for (size_t i = 0; i < total_size; ++i) {
    if (i % this->_nb_col == 0) {
      std::cout << std::endl;
    }

    std::cout << std::fixed << std::setprecision(6) << this->_content[i] << " ";
  }

  std::cout << std::endl;
}

size_t Matrix::to_linear_coordinate(size_t line, size_t col) const {
  if (line > this->_nb_line || line < 1)
    throw std::invalid_argument("Line index out of range.");

  if (col > this->_nb_col || col < 1)
    throw std::invalid_argument("Column index out of range.");

  return (line - 1) * this->_nb_col + (col - 1);
}

Matrix new_identity_matrix(size_t n) {
  Matrix I = Matrix(n, n);

  for (size_t i = 1; i <= n; ++i) {
    I(i, i) = 1;
  }

  return I;
}

Matrix operator*(const Matrix &m, double a) {
  Matrix result = Matrix(m.get_nb_line(), m.get_nb_col());

  for (size_t i = 1; i <= result.get_nb_line(); ++i)
    for (size_t j = 1; j <= result.get_nb_col(); ++j)
      result(i, j) = m(i, j) * a;

  return result;
}

Matrix operator*(double a, const Matrix &m) {
  return m * a;
}
