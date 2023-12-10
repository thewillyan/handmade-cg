#include "graphite/include/light_point.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/ray.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/object.hpp"
#include <cmath>

using namespace Graphite::Light;

// constructor
Point::Point(Algebrick::Point3d point, Intensity light_int)
    : p{point}, i{light_int}, decay{1, 0, 0} {}

// setters
void Point::set_decay(double a, double b, double c) { decay = {a, b, c}; }

Intensity Point::get_intensity(const Object::Object &inter_obj,
                               std::vector<Object::Object *> objs,
                               const Algebrick::Point3d &inter_point,
                               const Algebrick::Ray &eye_ray) const {

  Algebrick::Vec3d L = (p - inter_point);
  double ray_len = L.length();

  Algebrick::Ray light_ray{p, inter_point};
  auto cont_obj = inter_obj.get_container_obj();
  for (auto &obj : objs) {
    if (cont_obj == nullptr && obj->get_id() != inter_obj.get_id()) {
      auto other_inter = obj->intersect(light_ray);
      if (other_inter.has_value() && ray_len >= other_inter->first) {
        return {0, 0, 0};
      }
    } else if (cont_obj != nullptr && obj->get_id() != cont_obj->get_id()) {
      auto other_inter = obj->intersect(light_ray);
      if (other_inter.has_value() && ray_len >= other_inter->first) {
        return {0, 0, 0};
      }
    }
  }

  Algebrick::Vec3d l = L.norm();
  auto n = inter_obj.normal(inter_point);
  if (!n.has_value())
    return {0, 0, 0};

  Object::ObjectIntensity oi = inter_obj.get_intensity(inter_point);

  Algebrick::Vec3d v = -eye_ray.direction();
  Algebrick::Vec3d r = ((*n) * ((*n) * l * 2)) - l;

  Intensity i_dif = (i * oi.get_diffuse_intensity()) * (l * (*n));
  double reflect = oi.get_shineness();
  double rv = r * v;

  Intensity i_esp{0, 0, 0};
  if (rv > 0) {
    i_esp = (i * oi.get_specular_intensity()) * std::pow(r * v, reflect);
  }

  double d =
      (decay.x * std::pow(L.length(), 2)) + (decay.y * L.length()) + decay.z;
  return (i_dif + i_esp) / d;
}

void Point::transform(const Algebrick::Matrix &m) {
  Algebrick::Matrix point_4d = {{p.x}, {p.y}, {p.z}, {1.0}};
  Algebrick::Matrix new_point = m * point_4d;
  p = {new_point.get(0, 0), new_point.get(1, 0), new_point.get(2, 0)};
}
