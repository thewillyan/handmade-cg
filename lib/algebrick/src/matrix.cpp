#include "../include/matrix.hpp"
#include "../include/vec3d.hpp"
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace Algebrick;

constexpr size_t Matrix::idx(size_t i, size_t j) const { return (i * n) + j; }

Matrix::Matrix(size_t size)
    : m{size}, n{size}, elems{std::vector<double>(size * size, 0.0)} {}
Matrix::Matrix(size_t lines, size_t cols)
    : m{lines}, n{cols}, elems{std::vector<double>(lines * cols, 0.0)} {}
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> &&lst)
    : m{lst.size()}, n{lst.begin()->size()}, elems{std::vector<double>(n * m)} {
  size_t i = 0;
  for (auto &line : lst) {
    if (line.size() != n) {
      throw std::invalid_argument("Initializer list is not a valid matrix.");
    }
    size_t j = 0;
    for (double num : line) {
      elems[idx(i, j++)] = num;
    }
    ++i;
  }
}
bool Matrix::is_identity() const {
  for (size_t i = 0; i < m; ++i) {
    for (size_t j = 0; j < n; ++j) {
      double x = this->get(i, j);
      if ((i == j && x != 1) || (i != j && x != 0)) {
        return false;
      }
    }
  }
  return true;
}

Matrix Matrix::transpose(Matrix matrix) {
  Matrix t = Matrix(matrix.get_cols(), matrix.get_lines());
  for (size_t i = 0; i < matrix.get_lines(); ++i) {
    for (size_t j = 0; j < matrix.get_cols(); ++j) {
      t.get(j, i) = matrix.get(i, j);
    }
  }
  return matrix;
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
      sum = 0;
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

  Matrix mul_mat = Matrix(m, 3);
  for (size_t i = 0; i < m; ++i) {
    mul_mat.get(i, 0) =
        (other.x * get(i, 0)) + (other.y * get(i, 1)) + (other.z * get(i, 2));
  }
  return mul_mat;
}
