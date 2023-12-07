#include "graphite/include/spotlight.hpp"
#include "algebrick/include/point3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"

using namespace Graphite::Light;

Spot::Spot(Algebrick::Point3d point, Intensity base_intensity,
           Algebrick::Vec3d direction, double angle)
    : p{point}, i{base_intensity}, direction{direction.norm()},
      aperture{angle} {}

Intensity Spot::get_intensity(const Object::Object &inter_obj,
                              std::vector<Object::Object *> objs,
                              const Algebrick::Point3d &inter_point,
                              const Algebrick::Ray &eye_ray) const {
  // check if the point is inside the cone
  Algebrick::Vec3d L = (p - inter_point);
  Algebrick::Vec3d l = L.norm();

  if (double angle = acos(l * direction * -1); angle > aperture / 2) {
    return {0, 0, 0};
  }

  // check other objects intersections
  double ray_len = L.length();

  Algebrick::Ray light_ray{p, inter_point};
  for (auto &obj : objs) {
    if (obj != &inter_obj) {
      auto other_inter = obj->intersect(light_ray);
      if (other_inter.has_value()) {
        if (ray_len >= other_inter->first) {
          return {0, 0, 0};
        }
      }
    }
  }

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

  return (i_dif + i_esp);
}

void Spot::transform(const Algebrick::Matrix &m) {
  Algebrick::Matrix point_4d = {{p.x}, {p.y}, {p.z}, {1.0}};
  Algebrick::Matrix new_point = m * point_4d;
  p = {new_point.get(0, 0), new_point.get(1, 0), new_point.get(2, 0)};
  Algebrick::Matrix dir_4d = {
      {direction.x}, {direction.y}, {direction.z}, {0.0}};
  Algebrick::Matrix new_dir = m * dir_4d;
  direction = {new_dir.get(0, 0), new_dir.get(1, 0), new_dir.get(2, 0)};
  direction = direction.norm();
}
