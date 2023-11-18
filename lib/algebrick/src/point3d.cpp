#include "../include/point3d.hpp"
#include "../include/vec3d.hpp"
#include <iostream>

using namespace Algebrick;

Point3d::Point3d(double a, double b, double c) : x{a}, y{b}, z{c} {}
Point3d::Point3d(const Vec3d &v) : x{v.x}, y{v.y}, z{v.z} {}
Vec3d Point3d::operator+(const Point3d &other) const {
  return {x + other.x, y + other.y, z + other.z};
}
Vec3d Point3d::operator-(const Point3d &other) const {
  return {x - other.x, y - other.y, z - other.z};
}

Point3d &Point3d::operator+=(const Point3d &other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Point3d::operator Vec3d() const { return Vec3d(x, y, z); }

std::ostream &Algebrick::operator<<(std::ostream &out, const Point3d &p) {
  return out << '(' << p.x << ',' << p.y << ',' << p.z << ')';
}
