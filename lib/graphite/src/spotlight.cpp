#include "graphite/include/spotlight.hpp"

using namespace Graphite::Light;

Spot::Spot(Algebrick::Point3d point, Intensity base_intensity,
           Algebrick::Vec3d direction, double angle)
    : p{point}, i{base_intensity}, direction{direction.norm()},
      aperture{angle} {}

Intensity Spot::get_intensity(const Object &inter_obj,
                              std::vector<Object *> objs,
                              const PointColor &inter,
                              const Algebrick::Ray &eye_ray) const {
  // check if the point is inside the cone
  Algebrick::Vec3d L = (p - inter.first);
  Algebrick::Vec3d l = L.norm();

  double angle = acos(l * direction * -1);
  if (angle > aperture / 2) {
    return {0, 0, 0};
  }

  // check other objects intersections
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

  auto n = inter_obj.normal(inter.first);
  if (!n.has_value())
    return {0, 0, 0};

  Algebrick::Vec3d v = -eye_ray.direction();
  Algebrick::Vec3d r = ((*n) * ((*n) * l * 2)) - l;

  Intensity i_dif = (i * inter_obj.get_dif_int()) * (l * (*n));
  double reflect = inter_obj.get_reflection();
  double rv = r * v;

  Intensity i_esp{0, 0, 0};
  if (rv > 0) {
    i_esp = (i * inter_obj.get_espec_int()) * std::pow(r * v, reflect);
  }

  return (i_dif + i_esp);
}