#include "../include/light_point.hpp"
#include "../../algebrick/include/point3d.hpp"
#include "../include/object.hpp"
#include <cmath>
#include <stdexcept>

using namespace Graphite::Light;

// constructor
Point::Point(Algebrick::Point3d point, Intensity light_int)
    : p{point}, i{light_int}, decay{1, 0, 0} {}

// setters
void Point::set_decay(double a, double b, double c) { decay = {a, b, c}; }

Intensity Point::get_intensity(const Object &obj, const PointColor &inter,
                               const Algebrick::Ray &eye_ray) const {
  auto n = obj.normal(inter.first);
  if (!n.has_value())
    throw std::invalid_argument("Invalid intesection point!");

  Algebrick::Vec3d v = -eye_ray.direction();
  Algebrick::Vec3d L = (p - inter.first);
  Algebrick::Vec3d l = L.norm();
  Algebrick::Vec3d r = ((*n) * ((*n) * l) * 2) - l;
  Intensity k = Intensity(inter.second);

  Intensity i_dif = (i * k) * (l * (*n));
  double reflect = obj.get_reflection();
  Intensity i_esp = (i * k) * std::pow(r * v, reflect);

  double d =
      (decay.x * std::pow(L.length(), 2)) + (decay.y * L.length()) + decay.z;
  return (i_dif + i_esp) / d;
}
