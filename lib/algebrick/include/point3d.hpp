#ifndef Algebrick_Point_H
#define Algebrick_Point_H

#include "vec3d.hpp"
#include <iostream>

namespace Algebrick {

class Point3d {
public:
  double x;
  double y;
  double z;

  Point3d(double a, double b, double c);
  Point3d(const Vec3d &);
  Vec3d operator-(const Point3d &other) const;
  Vec3d operator+(const Point3d &other) const;
  Vec3d operator*(double k) const;
  Point3d &operator+=(const Point3d &other);
  Point3d &operator-=(const Point3d &other);
  Point3d &operator*=(double k);
  explicit operator Vec3d() const;
};

std::ostream &operator<<(std::ostream &out, const Point3d &p);

};     // namespace Algebrick
#endif // !Algebrick_Point_H
