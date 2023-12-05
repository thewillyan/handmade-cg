#include "graphite/include/directed_light.hpp"
#include "algebrick/include/ray.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/objs/object.hpp"
#include <cmath>

using namespace Graphite::Light;

Directed::Directed(Intensity light_int, Algebrick::Vec3d direction)
    : i{light_int}, decay{1, 0, 0}, direction{direction.norm()} {}

void Directed::set_decay(double a, double b, double c) { decay = {a, b, c}; }

Intensity Directed::get_intensity(const Object::Object &inter_obj,
                                  std::vector<Object::Object *> objs,
                                  const Object::PointColor &inter,
                                  const Algebrick::Ray &eye_ray) const {

  // check if same direction
  Algebrick::Vec3d L = -direction;
  Algebrick::Vec3d l = L.norm();

  // check other objects intersections
  double light_length = 0;
  Algebrick::Ray light_ray{inter.first, -direction};
  for (auto &obj : objs) {
    if (obj != &inter_obj) {
      auto other_inter = obj->intersect(light_ray);
      if (other_inter.has_value()) {
        Algebrick::Vec3d other_inter_vec = (other_inter->first - inter.first);
        double other_inter_len = other_inter_vec.length();
        if (other_inter_len >= light_length) {
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
  // TODO: remove the point from the directed light
  Algebrick::Matrix direction_4d = {
      {direction.x}, {direction.y}, {direction.z}, {1.0}};
  Algebrick::Matrix new_direction = m * direction_4d;
  direction = {new_direction.get(0, 0), new_direction.get(1, 0),
               new_direction.get(2, 0)};
}
