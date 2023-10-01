#ifndef Algebrick_Vec3d_H
#define Algebrick_Vec3d_H
#include <ostream>
namespace Algebrick {

class Vec3d {
public:
  double x;
  double y;
  double z;

  // constructors
  Vec3d(double x, double y, double z);

  // basic operators
  Vec3d &operator+=(const Vec3d &other);
  Vec3d operator+(const Vec3d &other) const;
  Vec3d operator-() const;
  Vec3d operator-(const Vec3d &other) const;
  Vec3d &operator-=(const Vec3d &other);
  double operator*(const Vec3d &other) const;
  Vec3d operator*(double k) const;
  Vec3d &operator*=(double k);
  Vec3d operator/(double k) const;
  Vec3d &operator/=(double k);

  // custom operator
  Vec3d direct_mul(const Vec3d &other) const;
  void direct_mul_assign(const Vec3d &other);

  // vector operations
  double length() const;
  Vec3d norm() const;
  void norm_assign();
};

std::ostream &operator<<(std::ostream &, const Vec3d &);
} // namespace Algebrick

#endif // !Algebrick_Vec3d_H
