#include "../include/light_point.hpp"
#include "../../algebrick/include/point3d.hpp"
#include "../include/object.hpp"
#include "algebrick/include/ray.hpp"
#include "algebrick/include/vec3d.hpp"
#include <cmath>
#include <stdexcept>

using namespace Graphite::Light;

// constructor
Point::Point(Algebrick::Point3d point, Intensity light_int)
    : p{point}, i{light_int}, decay{1, 0, 0} {}

// setters
void Point::set_decay(double a, double b, double c) { decay = {a, b, c}; }

Intensity Point::get_intensity(const Object &inter_obj,
                               std::vector<Object *> objs,
                               const PointColor &inter,
                               const Algebrick::Ray &eye_ray) const {

  Algebrick::Vec3d L = (p - inter.first);
  double ray_len = L.length();

  Algebrick::Ray light_ray{p, inter.first};
  for (auto &obj : objs) {
    if (obj != &inter_obj) {
      auto other_inter = obj->intersect(light_ray);
      if (other_inter.has_value()) {
        Algebrick::Vec3d other_inter_vec = (other_inter->first - p);
        double other_inter_len = other_inter_vec.length();
        if (ray_len >= other_inter_len) {
          return {0, 0, 0};
        }
      }
    }
  }

  Algebrick::Vec3d l = L.norm();
  auto n = inter_obj.normal(inter.first);
  if (!n.has_value())
    return {0, 0, 0};

  Algebrick::Vec3d v = -eye_ray.direction();
  Algebrick::Vec3d r = ((*n) * ((*n) * l * 2)) - l;

  Intensity i_dif = (i * inter_obj.get_dif_int()) * (l * (*n));
  double reflect = inter_obj.get_reflection();
  Intensity i_esp = (i * inter_obj.get_espec_int()) * std::pow(r * v, reflect);

  double d =
      (decay.x * std::pow(L.length(), 2)) + (decay.y * L.length()) + decay.z;
  return (i_dif + i_esp) / d;
}
