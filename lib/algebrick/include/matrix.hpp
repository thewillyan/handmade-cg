#ifndef Algebrick_Matrix
#define Algebrick_Matrix

#include "point3d.hpp"
#include "vec3d.hpp"
#include <cstddef>
#include <initializer_list>
#include <optional>
#include <vector>

namespace Algebrick {
class Matrix {
private:
  const size_t m;
  const size_t n;
  std::vector<double> elems;

  constexpr size_t idx(size_t, size_t) const;

public:
  Matrix(size_t, size_t);
  Matrix(std::initializer_list<std::initializer_list<double>>);
  Matrix(std::initializer_list<Vec3d>);
  Matrix(std::initializer_list<Point3d>);

  size_t get_lines() const;
  size_t get_cols() const;
  double &get(size_t, size_t);
  const double &get(size_t, size_t) const;

  // special matrices
  static Matrix translation(const Vec3d &offset);

  Matrix operator*(const Matrix &) const;
  Matrix operator*(const Vec3d &) const;
};
} // namespace Algebrick

#endif // !Algebrick_Matrix
