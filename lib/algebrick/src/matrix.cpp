#include "../include/matrix.hpp"
#include "../include/vec3d.hpp"
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

using namespace Algebrick;

constexpr size_t Matrix::idx(size_t i, size_t j) const { return (i * m) + j; }

Matrix::Matrix(size_t size)
    : m{size}, n{size}, elems{std::vector<double>(n * n, 0.0)} {}
Matrix::Matrix(size_t lines, size_t cols)
    : m{lines}, n{cols}, elems{std::vector<double>(m * n, 0.0)} {}
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst)
    : m{lst.size()}, n{lst.begin()->size()}, elems{std::vector<double>(m * n,
                                                                       0.0)} {
  size_t i = 0;
  for (auto &line : lst) {
    if (line.size() != m) {
      throw std::invalid_argument("Initializer list is not a valid matrix.");
    }
    size_t j = 0;
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

Matrix Matrix::inv(Matrix matrix) {
  if (matrix.get_lines() != matrix.get_cols()) {
    throw std::invalid_argument(
        "Can't calculate the invert of an non-square matrix.");
  }
  size_t size = matrix.get_lines();
  Matrix inv = Matrix::identity(size);

  // turns `matrix` into upper triangular
  for (size_t p = 0; p < size; ++p) {
    double pivot = matrix.get(p, p);
    for (size_t i = p + 1; i < size; ++i) {
      double x = matrix.get(i, p);
      if (x == 0) {
        continue;
      }

      double k = x / pivot;
      for (size_t j = 0; j < size; ++j) {
        matrix.get(i, j) -= matrix.get(p, j) * k;
        inv.get(i, j) -= inv.get(p, j) * k;
      }
    }

    for (size_t j = 0; j < size; ++j) {
      matrix.get(p, j) /= pivot;
      inv.get(p, j) /= pivot;
    }
  }

  // turns upper triangular version of `matrix` into an identity.
  for (size_t p = 1; p < size; ++p) {
    double pivot = matrix.get(p, p);
    for (size_t i = 0; i < p; ++i) {
      double &x = matrix.get(i, p);
      if (x == 0) {
        continue;
      }

      double k = x / pivot;
      for (size_t j = 0; j < size; ++j) {
        matrix.get(i, j) -= matrix.get(p, j) * k;
        inv.get(i, j) -= inv.get(p, j) * k;
      }
    }
  }

  return inv;
}

Matrix Matrix::identity(size_t size) {
  Matrix m{size};
  for (size_t i = 0; i < size; ++i) {
    m.get(i, i) = 1;
  }
  return m;
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

  Matrix mul_mat = Matrix(m, other.get_cols());
  for (size_t i = 0; i < m; ++i) {
    for (size_t j = 0; j < other.get_cols(); ++j) {
      double &sum = mul_mat.get(i, j);
      for (size_t k = 0; k < other.get_lines(); ++k) {
        sum += get(i, k) * other.get(k, j);
      }
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
