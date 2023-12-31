#ifndef Algebrick_Matrix
#define Algebrick_Matrix

#include "vec3d.hpp"
#include <cstddef>
#include <initializer_list>
#include <vector>

namespace Algebrick {
class Matrix {
private:
  size_t m;
  size_t n;
  std::vector<double> elems;

  constexpr size_t idx(size_t, size_t) const;

public:
  Matrix(size_t);
  Matrix(size_t, size_t);
  Matrix(std::initializer_list<std::initializer_list<double>> &&);

  size_t get_lines() const;
  size_t get_cols() const;
  double &get(size_t, size_t);
  const double &get(size_t, size_t) const;
  bool is_identity() const;

  // special matrices
  static Matrix transpose(Matrix);
  static Matrix inv(Matrix);
  static Matrix identity(size_t);
  static Matrix translation(const Vec3d &offset);
  static Matrix scale(const Vec3d &k);

  Matrix operator*(const Matrix &) const;
  Matrix operator*(const Vec3d &) const;

  // fast matrix multiplication
  Matrix mul(const Matrix &) const;
};
} // namespace Algebrick

#endif // !Algebrick_Matrix
