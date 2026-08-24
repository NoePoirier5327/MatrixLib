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
