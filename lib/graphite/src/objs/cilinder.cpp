#include "graphite/include/objs/cilinder.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/objs/object.hpp"
#include <cmath>
#include <vector>

using namespace Graphite::Object;

Cilinder::Cilinder(const Algebrick::Point3d &base_center,
                   const Algebrick::Vec3d &dir, double radius, double height,
                   double shineness)
    : radius{radius}, height{height}, dir{dir.norm()}, base_center{base_center},
      base{base_center, radius, dir.norm() * -1},
      top{base_center + dir.norm() * height, radius, dir.norm()} {
  intensity.set_shineness(shineness);
};

Cilinder::Cilinder(const Algebrick::Point3d &base_center,
                   const Algebrick::Vec3d &dir, double radius, double height,
                   double shineness, const Light::Intensity &dif,
                   const Light::Intensity &spec, const Light::Intensity &env)
    : radius{radius}, height{height}, dir{dir.norm()}, base_center{base_center},
      base{base_center, radius, dir.norm() * -1, dif, spec, env, shineness},
      top{base_center + dir.norm() * height,
          radius,
          dir.norm(),
          dif,
          spec,
          env,
          shineness},
      intensity{shineness, dif, spec, env} {};

std::optional<RayLenObj> Cilinder::intersect(const Algebrick::Ray &ray) const {
  Algebrick::Vec3d v =
      (ray.source() - base_center) - dir * ((ray.source() - base_center) * dir);
  Algebrick::Vec3d w = ray.direction() - dir * (ray.direction() * dir);
  double a = w * w;
  double b = 2 * (v * w);
  double delta = b * b - 4 * a * (v * v - radius * radius);

  // No intersection
  if (delta < 0)
    return {};

  std::vector<std::pair<double, Object *>> valid_points;

  double t1 = (-b + sqrt(delta)) / (2 * a);
  if (t1 >= 0) {
    Algebrick::Point3d p1 = ray.source() + ray.direction() * t1;
    double inside_p1 = (p1 - base_center) * dir;

    if (inside_p1 >= 0 && inside_p1 <= height)
      valid_points.push_back(std::make_pair(t1, (Object *)this));
  }

  double t2 = (-b - sqrt(delta)) / (2 * a);
  if (t2 >= 0) {
    Algebrick::Point3d p2 = ray.source() + ray.direction() * t2;
    double inside_p2 = (p2 - base_center) * dir;

    if (inside_p2 >= 0 && inside_p2 <= height)
      valid_points.push_back(std::make_pair(t2, (Object *)this));
  }

  auto intersected_base = base.intersect(ray);
  auto intersected_top = top.intersect(ray);

  if (intersected_top.has_value() && intersected_base.has_value()) {
    double cap1 = intersected_base->first;
    double cap2 = intersected_top->first;

    if (cap1 < cap2) {
      valid_points.push_back(std::make_pair(cap1, intersected_base->second));
    } else {
      valid_points.push_back(std::make_pair(cap2, intersected_top->second));
    }
  } else if (intersected_base.has_value()) {
    valid_points.push_back(
        std::make_pair(intersected_base->first, intersected_base->second));
  } else if (intersected_top.has_value()) {
    valid_points.push_back(
        std::make_pair(intersected_top->first, intersected_top->second));
  }

  double min = INFINITY;
  Object *best_obj = nullptr;

  for (auto const &p : valid_points) {
    if (p.first < min) {
      min = p.first;
      best_obj = p.second;
    }
  }

  return min == INFINITY ? std::optional<RayLenObj>{}
                         : std::make_pair(min, best_obj);
}

std::optional<Algebrick::Vec3d>
Cilinder::normal(const Algebrick::Point3d &p) const {
  Algebrick::Vec3d normal;
  Algebrick::Vec3d top_base = base_center + dir * height;

  if ((p - top_base).length() < radius) {
    normal = dir;
  } else if ((p - base_center).length() < radius) {
    normal = dir * -1;
  } else {
    double t = (p - base_center) * dir;
    Algebrick::Vec3d pt = base_center + dir * t;
    normal = (p - pt).norm();
  }
  return normal;
}

// Getters
Graphite::Object::ObjectIntensity
Cilinder::get_intensity([[maybe_unused]] const Algebrick::Point3d &p) const {
  return intensity;
}

void Cilinder::translate(const Algebrick::Vec3d &offset) {
  base_center += offset;
  base.translate(offset);
  top.translate(offset);
}

void Cilinder::transform(const Algebrick::Matrix &matrix) {
  Algebrick::Matrix base_center_4d = {
      {this->base_center.x}, {this->base_center.y}, {this->base_center.z}, {1}};
  Algebrick::Matrix new_center = matrix * base_center_4d;
  base_center = {new_center.get(0, 0), new_center.get(1, 0),
                 new_center.get(2, 0)};

  Algebrick::Matrix dir_4d = {{dir.x}, {dir.y}, {dir.z}, {0}};
  Algebrick::Matrix new_dir = matrix * dir_4d;
  dir = {new_dir.get(0, 0), new_dir.get(1, 0), new_dir.get(2, 0)};
  dir = dir.norm();

  base.transform(matrix);
  top.transform(matrix);
}
void Cilinder::scale(double k) {
  height *= k;
  radius *= k;
  base.scale(k);
  top.scale(k);
}
