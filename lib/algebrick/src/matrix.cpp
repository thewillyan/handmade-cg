#include "../include/matrix.hpp"
#include "../include/vec3d.hpp"
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

using namespace Algebrick;

constexpr size_t Matrix::idx(size_t i, size_t j) const { return (i * n) + j; }

Matrix::Matrix(size_t lines, size_t cols)
    : m{lines}, n{cols}, elems{std::vector<double>(m * n)} {}
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst)
    : m{lst.size()}, n{lst.begin()->size()}, elems{std::vector<double>(m * n)} {
  size_t i = 0, j = 0;
  for (auto &line : lst) {
    for (double num : line) {
      elems[idx(i, j++)] = num;
    }
    ++i;
  }
}
Matrix::Matrix(std::initializer_list<Vec3d> lst)
    : m{lst.size()}, n{3}, elems{std::vector<double>(m * n)} {
  size_t i = 0;
  for (auto &v : lst) {
    elems[idx(i, 0)] = v.x;
    elems[idx(i, 1)] = v.y;
    elems[idx(i, 2)] = v.z;
    ++i;
  }
}
Matrix::Matrix(std::initializer_list<Point3d> lst)
    : m{lst.size()}, n{3}, elems{std::vector<double>(m * n)} {
  size_t i = 0;
  for (auto &p : lst) {
    elems[idx(i, 0)] = p.x;
    elems[idx(i, 1)] = p.y;
    elems[idx(i, 2)] = p.z;
    ++i;
  }
}

Matrix Matrix::translation(const Vec3d &offset) {
  return {{1, 0, 0, offset.x},
          {0, 1, 0, offset.y},
          {0, 0, 1, offset.z},
          {0, 0, 0, 1}};
}

size_t Matrix::get_lines() const { return m; }
size_t Matrix::get_cols() const { return n; }
double &Matrix::get(size_t i, size_t j) {
  if (i > m || j > n)
    throw std::out_of_range("Invalid Matrix range!");
  return elems[Matrix::idx(i, j)];
}
const double &Matrix::get(size_t i, size_t j) const {
  if (i > m || j > n)
    throw std::out_of_range("Invalid Matrix range!");
  return elems[Matrix::idx(i, j)];
}

Matrix Matrix::operator*(const Matrix &other) const {
  if (n != other.get_lines())
    throw std::out_of_range("The number of columns of the first matrix is \
        not equal to the number of lines of the second one.");

  Matrix mul_mat = Matrix(n, other.get_lines());
  double sum;
  for (size_t i = 0; i < m; ++i) {
    for (size_t j = 0; i < other.get_cols(); ++j) {
      sum = 0;
      for (size_t k = 0; k < n; ++k) {
        sum += get(i, k) * other.get(k, j);
      }
      mul_mat.get(i, j) = sum;
    }
  }
  return mul_mat;
}

Matrix Matrix::operator*(const Vec3d &other) const {
  if (n != 3)
    throw std::out_of_range("The number of columns of the first matrix is \
        not equal to 3.");

  Matrix mul_mat = Matrix(n, 3);
  for (size_t i = 0; i < m; ++i) {
    mul_mat.get(i, 0) =
        (other.x * get(i, 0)) + (other.y * get(i, 1)) + (other.z * get(i, 2));
  }
  return mul_mat;
}
