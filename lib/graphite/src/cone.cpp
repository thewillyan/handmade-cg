#include "graphite/include/cone.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "cmath"
#include "graphite/include/intensity.hpp"
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

using namespace Graphite;

Cone::Cone(double h, double r, Algebrick::Point3d base_center,
           Algebrick::Vec3d n)
    : radius{r}, height{h}, aperture{std::acos(h / std::sqrt(r * r + h * h))},
      norm{n.norm()}, center{base_center}, top{base_center + n.norm() * h},
      base{base_center, r, n.norm()}, shiness{1}, env{1, 1, 1}, espec{1, 1, 1},
      dif{1, 1, 1} {}

Cone::Cone(double h, double r, Algebrick::Point3d base_center,
           Algebrick::Vec3d n, double shiness, Light::Intensity env,
           Light::Intensity esp, Light::Intensity dif)
    : radius{r}, height{h}, aperture{0.2}, norm{n.norm()}, center{base_center},
      top{base_center + n.norm() * h}, base{base_center, r, n.norm()},
      shiness{shiness}, env{env}, espec{esp}, dif{dif} {}

std::optional<PointColor> Cone::intersect(const Algebrick::Ray &ray) const {
  Algebrick::Vec3d v =
      (ray.source() - center) - norm * ((ray.source() - center) * norm);

  double cos_sqr = std::pow(std::cos(aperture), 2);
  double a = std::pow(ray.direction() * norm, 2) -
             (ray.direction() * ray.direction()) * cos_sqr;
  double b = ((ray.direction() * v) * cos_sqr) -
             ((v * norm) * (ray.direction() * norm));
  double c = std::pow(v * norm, 2) - ((v * v) * cos_sqr);

  double delta = std::pow(b, 2) - (4 * a * c);

  // No intersection
  if (delta < 0)
    return {};

  std::vector<std::pair<double, Algebrick::Point3d>> valid_points;

  double t1 = (-b + sqrt(delta)) / (2 * a);
  if (t1 >= 0) {
    Algebrick::Point3d p1 = ray.source() + ray.direction() * t1;
    double inside_p1 = (p1 - center) * norm;

    if (inside_p1 >= 0 && inside_p1 <= height)
      valid_points.push_back(std::make_pair(t1, p1));
  }

  double t2 = (-b - sqrt(delta)) / (2 * a);
  if (t2 >= 0) {
    Algebrick::Point3d p2 = ray.source() + ray.direction() * t2;
    double inside_p2 = (p2 - center) * norm;

    if (inside_p2 >= 0 && inside_p2 <= height)
      valid_points.push_back(std::make_pair(t2, p2));
  }

  auto intersected_base = base.intersect(ray);

  if (intersected_base.has_value()) {
    double t = (intersected_base->first - ray.source()).length();
    valid_points.push_back(std::make_pair(t, intersected_base->first));
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
Cone::normal(const Algebrick::Point3d &p) const {
  auto pi = p - top;
  auto normal = ((norm.cross(pi)).cross(pi)).norm();
  return normal;
}

// getters
double Cone::get_reflection() const { return shiness; };
Light::Intensity Cone::get_dif_int() const { return dif; };
Light::Intensity Cone::get_espec_int() const { return espec; }
Light::Intensity Cone::get_env_int() const { return env; }
