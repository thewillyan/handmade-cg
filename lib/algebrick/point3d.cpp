#include "point3d.h"
#include "vec3d.h"
#include <iostream>

using namespace Algebrick;

Point3d::Point3d(double a, double b, double c) : x{a}, y{b}, z{c} {}
Vec3d Point3d::operator-(const Point3d &other) const {
  return {x - other.x, y - other.y, z - other.z};
}
Point3d::operator Vec3d() const { return Vec3d(x, y, z); }

std::ostream &Algebrick::operator<<(std::ostream &out, const Point3d &p) {
  return out << '(' << p.x << ',' << p.y << ',' << p.z << ')';
}
