#include "graphite/include/cilinder.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include <cmath>
#include <vector>

using namespace Graphite;

Cilinder::Cilinder(const Algebrick::Point3d &base_center,
                   const Algebrick::Vec3d &dir, double radius, double height,
                   double shineness)
    : shineness{shineness}, radius{radius}, height{height}, dir{dir.norm()},
      base_center{base_center}, base{base_center, radius, dir.norm() * -1},
      top{base_center + dir.norm() * height, radius, dir.norm()}, dif{1, 1, 1},
      spec{1, 1, 1}, env{1, 1, 1} {}

Cilinder::Cilinder(const Algebrick::Point3d &base_center,
                   const Algebrick::Vec3d &dir, double radius, double height,
                   double shineness, const Light::Intensity &dif,
                   const Light::Intensity &spec, const Light::Intensity &env)
    : shineness{shineness}, radius{radius}, height{height}, dir{dir.norm()},
      base_center{base_center}, base{base_center, radius, dir.norm() * -1, dif,
                                     spec,        env,    shineness},
      top{base_center + dir.norm() * height,
          radius,
          dir.norm(),
          dif,
          spec,
          env,
          shineness},
      dif{dif}, spec{spec}, env{env} {}

std::optional<PointColor> Cilinder::intersect(const Algebrick::Ray &ray) const {
  Algebrick::Vec3d v =
      (ray.source() - base_center) - dir * ((ray.source() - base_center) * dir);
  Algebrick::Vec3d w = ray.direction() - dir * (ray.direction() * dir);
  double a = w * w;
  double b = 2 * (v * w);
  double delta = b * b - 4 * a * (v * v - radius * radius);

  // No intersection
  if (delta < 0)
    return {};

  std::vector<std::pair<double, Algebrick::Point3d>> valid_points;

  double t1 = (-b + sqrt(delta)) / (2 * a);
  if (t1 >= 0) {
    Algebrick::Point3d p1 = ray.source() + ray.direction() * t1;
    double inside_p1 = (p1 - base_center) * dir;

    if (inside_p1 >= 0 && inside_p1 <= height)
      valid_points.push_back(std::make_pair(t1, p1));
  }

  double t2 = (-b - sqrt(delta)) / (2 * a);
  if (t2 >= 0) {
    Algebrick::Point3d p2 = ray.source() + ray.direction() * t2;
    double inside_p2 = (p2 - base_center) * dir;

    if (inside_p2 >= 0 && inside_p2 <= height)
      valid_points.push_back(std::make_pair(t2, p2));
  }

  auto intersected_base = base.intersect(ray);
  auto intersected_top = top.intersect(ray);

  if (intersected_top.has_value() && intersected_base.has_value()) {
    double cap1 = (intersected_base->first - ray.source()).length();
    double cap2 = (intersected_top->first - ray.source()).length();

    if (cap1 < cap2) {
      valid_points.push_back(std::make_pair(cap1, intersected_base->first));
    } else {
      valid_points.push_back(std::make_pair(cap2, intersected_top->first));
    }
  } else if (intersected_base.has_value()) {
    double t = (intersected_base->first - ray.source()).length();
    valid_points.push_back(std::make_pair(t, intersected_base->first));
  } else if (intersected_top.has_value()) {
    double t = (intersected_top->first - ray.source()).length();
    valid_points.push_back(std::make_pair(t, intersected_top->first));
  }

  double min = INFINITY;
  Algebrick::Point3d best_point = ray.source();

  for (auto const &p : valid_points) {
    if (p.first < min) {
      min = p.first;
      best_point = p.second;
    }
  }

  return min == INFINITY ? std::optional<PointColor>{}
                         : std::make_pair(best_point, SDL_Color{0, 0, 0, 0});
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
double Cilinder::get_reflection() const { return shineness; }
Light::Intensity Cilinder::get_dif_int() const { return dif; }
Light::Intensity Cilinder::get_espec_int() const { return spec; }
Light::Intensity Cilinder::get_env_int() const { return env; }

void Cilinder::translate(const Algebrick::Vec3d &offset) {
  base_center += offset;
  base.translate(offset);
  top.translate(offset);
}
void Cilinder::scale(double k) {
  height *= k;
  radius *= k;
  base.scale(k);
  top.scale(k);
}
