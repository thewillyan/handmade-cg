#include "graphite/include/cone.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "cmath"
#include "graphite/include/intensity.hpp"
#include <algorithm>
#include <cmath>
#include <utility>

using namespace Graphite;

// double radius;
// double height;
// double aperture;
// Algebrick::Vec3d norm;
// Algebrick::Point3d center;
// Algebrick::Point3d top;
// CircularPlane base;
Cone::Cone(double h, double r, Algebrick::Point3d base_center,
           Algebrick::Vec3d n)
    : radius{r}, height{h}, aperture{std::acos(h / std::sqrt(r * r + h * h))},
      norm{n.norm()}, center{base_center}, top{base_center + n.norm() * h},
      base{base_center, r, n.norm()}, shiness{1}, env{1, 1, 1}, espec{1, 1, 1},
      dif{1, 1, 1} {}

Cone::Cone(double h, double r, Algebrick::Point3d base_center,
           Algebrick::Vec3d n, double shiness, Light::Intensity env,
           Light::Intensity esp, Light::Intensity dif)
    : radius{r}, height{h}, aperture{std::acos(h / std::sqrt(r * r + h * h))},
      norm{n.norm()}, center{base_center}, top{base_center + n.norm() * h},
      base{base_center, r, n.norm()}, shiness{shiness}, env{env}, espec{esp},
      dif{dif} {}

std::optional<PointColor> Cone::intersect(const Algebrick::Ray &ray) const {
  Algebrick::Vec3d v = top - ray.source();
  double cos_sqr_theta = std::pow(std::cos(aperture), 2);
  double a = std::pow(ray.direction() * norm, 2) -
             (ray.direction() * ray.direction()) * cos_sqr_theta;
  double b = ((v * ray.direction()) * cos_sqr_theta) -
             (v * norm) * (ray.direction() * norm);
  double c = std::pow(v * norm, 2) - (v * v) * cos_sqr_theta;

  double delta = std::pow(b, 2) - (4 * a * c);

  if (delta < 0) {
    return {};
  }

  if (delta == 0) {
    double tInt = -b / (2 * a);
    if (tInt < 0)
      return {};
    Algebrick::Point3d pInt = ray.source() + ray.direction() * tInt;

    double height_limit = (top - pInt) * norm;
    if (height_limit < 0 || height_limit > height) {
      return {};
    }
    return std::make_pair(pInt, SDL_Color{0, 0, 0, 0});
  } else {
    double tInt1 = (-b + std::sqrt(delta)) / (2 * a);
    Algebrick::Point3d pInt1 = ray.source() + ray.direction() * tInt1;
    double height_limit1 = (top - pInt1) * norm;
    bool limit1_in_range = height_limit1 >= 0 && height_limit1 <= height;

    double tInt2 = (-b - std::sqrt(delta)) / (2 * a);
    Algebrick::Point3d pInt2 = ray.source() + ray.direction() * tInt2;
    double height_limit2 = (top - pInt2) * norm;
    bool limit2_in_range = height_limit2 >= 0 && height_limit2 <= height;

    if (!limit1_in_range && !limit2_in_range) {
      return {};
    }

    std::optional<double> tInt;
    if (tInt1 < 0 && tInt2 >= 0) {
      if (limit2_in_range) {
        tInt = tInt2;
      }
    } else if (tInt1 >= 0 && tInt2 < 0) {
      if (limit1_in_range) {
        tInt = tInt1;
      }
    } else if (tInt1 >= 0 && tInt2 >= 0) {
      if (limit1_in_range && !limit2_in_range) {
        tInt = tInt1;
      } else if (limit2_in_range && !limit1_in_range) {
        tInt = tInt2;
      } else {
        tInt = std::min(tInt1, tInt2);
      }
    }

    if (!tInt.has_value())
      return {};

    Algebrick::Point3d pInt = ray.source() + ray.direction() * tInt.value();
    double height_limit = (top - pInt) * norm;
    if (height_limit < 0 || height_limit > height) {
      return {};
    }
    return std::make_pair(pInt, SDL_Color{0, 0, 0, 0});
  }
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
