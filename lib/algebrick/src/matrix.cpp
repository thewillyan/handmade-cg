#include "../include/matrix.hpp"
#include "../include/vec3d.hpp"
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

using namespace Algebrick;

constexpr size_t Matrix::idx(size_t i, size_t j) const { return (i * n) + j; }

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

size_t Matrix::get_lines() const { return m; }
size_t Matrix::get_cols() const { return n; }
double &Matrix::get(size_t i, size_t j) {
  if (i > m || j > n)
    throw std::out_of_range("Invalid Matrix range!");
  return elems[Matrix::idx(i, j)];
}
