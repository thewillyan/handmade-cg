#include "graphite/include/directed_light.hpp"
#include "algebrick/include/ray.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/object.hpp"
#include <cmath>
#include <stdexcept>

using namespace Graphite::Light;

Directed::Directed(Algebrick::Point3d point, Intensity light_int,
                   Algebrick::Vec3d direction)
    : p{point}, i{light_int}, decay{1, 0, 0}, direction{direction.norm()} {}

void Directed::set_decay(double a, double b, double c) { decay = {a, b, c}; }

Intensity Directed::get_intensity(const Object &inter_obj,
                                  std::vector<Object *> objs,
                                  const PointColor &inter,
                                  const Algebrick::Ray &eye_ray) const {

  // check if same direction
  Algebrick::Vec3d L = (p - inter.first);
  Algebrick::Vec3d l = L.norm();
  double angle = acos(l * direction * -1);

  if (angle > M_PI / 2) {
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

  // double d =
  //     (decay.x * std::pow(L.length(), 2)) + (decay.y * L.length()) + decay.z;
  return (i_dif + i_esp) / 1;
}

void Directed::transform(const Algebrick::Matrix &m) {
  //TODO: remove the point from the directed light
  Algebrick::Matrix direction_4d = {
      {direction.x}, {direction.y}, {direction.z}, {1.0}};
  Algebrick::Matrix new_direction = m * direction_4d;
  direction = {new_direction.get(0, 0), new_direction.get(1, 0),
               new_direction.get(2, 0)};
}
