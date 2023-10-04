#include "../include/vec3d.hpp"
#include <cmath>
#include <ostream>

using namespace Algebrick;

// constructors
Vec3d::Vec3d(double a, double b, double c) : x{a}, y{b}, z{c} {}

// plus
Vec3d &Vec3d::operator+=(const Vec3d &other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}
Vec3d Vec3d::operator+(const Vec3d &other) const {
  return {x + other.x, y + other.y, z + other.z};
}
// sub
Vec3d Vec3d::operator-() const { return {-x, -y, -z}; }
Vec3d Vec3d::operator-(const Vec3d &other) const { return *this + (-other); }
Vec3d &Vec3d::operator-=(const Vec3d &other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}
// mul
double Vec3d::operator*(const Vec3d &other) const {
  return (x * other.x) + (y * other.y) + (z * other.z);
}
// mul scalar
Vec3d Vec3d::operator*(double k) const { return {x * k, y * k, z * k}; }
Vec3d &Vec3d::operator*=(double k) {
  x *= k;
  y *= k;
  z *= k;
  return *this;
}
// div scalar
Vec3d Vec3d::operator/(double k) const { return {x / k, y / k, z / k}; }
Vec3d &Vec3d::operator/=(double k) {
  x /= k;
  y /= k;
  z /= k;
  return *this;
}
// other
Vec3d Vec3d::direct_mul(const Vec3d &other) const {
  return {x * other.x, y * other.y, z * other.z};
}
void Vec3d::direct_mul_assign(const Vec3d &other) {
  x *= other.x;
  y *= other.y;
  z *= other.z;
}

double Vec3d::length() const { return std::sqrt((*this) * (*this)); }
Vec3d Vec3d::norm() const { return (*this) / this->length(); }
void Vec3d::norm_assign() { *this /= (this->length()); }

std::ostream &Algebrick::operator<<(std::ostream &out, const Vec3d &v) {
  return out << '[' << v.x << ',' << v.y << ',' << v.z << ']';
}
