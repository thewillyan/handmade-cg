#include "graphite/include/cilinder.hpp"
#include "algebrick/include/vec3d.hpp"

using namespace Graphite;

Cilinder::Cilinder(const Algebrick::Point3d &base_center,
                   const Algebrick::Vec3d &dir, double radius, double height,
                   double shineness)
    : shineness{shineness}, radius{radius}, height{height}, dir{dir.norm()},
      base_center{base_center}, dif{1, 1, 1}, spec{1, 1, 1}, env{1, 1, 1} {}

Cilinder::Cilinder(const Algebrick::Point3d &base_center,
                   const Algebrick::Vec3d &dir, double radius, double height,
                   double shineness, const Light::Intensity &dif,
                   const Light::Intensity &spec, const Light::Intensity &env)
    : shineness{shineness}, radius{radius}, height{height}, dir{dir.norm()},
      base_center{base_center}, dif{dif}, spec{spec}, env{env} {}

std::optional<PointColor> Cilinder::intersect(const Algebrick::Ray &ray) const {
  Algebrick::Vec3d v =
      (ray.source() - base_center) - dir * ((ray.source() - base_center) * dir);
  Algebrick::Vec3d w = ray.direction() - dir * (ray.direction() * dir);
  double a = w * w;
  double b = 2 * (v * w);
  double delta = b * b - 4 * a * (v * v - radius * radius);

  if (a == 0 || delta < 0)
    return {};

  double x1 = (-b + sqrt(delta)) / (2 * a);
  double x2 = (-b - sqrt(delta)) / (2 * a);
  double ray_dist;

  if (x1 < 0 && x2 < 0) {
    return {};
  } else if (x2 < 0) {
    ray_dist = x1;
  } else if (x1 < 0) {
    ray_dist = x2;
  } else {
    ray_dist = std::min(x1, x2);
  }

  Algebrick::Point3d inter_point = ray.source() + ray.direction() * ray_dist;
  return std::make_pair(std::move(inter_point), SDL_Color{0, 0, 0, 0});
}

std::optional<Algebrick::Vec3d>
Cilinder::normal(const Algebrick::Point3d &p) const {
  return {};
}

// Getters
double Cilinder::get_reflection() const { return shineness; }
Light::Intensity Cilinder::get_dif_int() const { return dif; }
Light::Intensity Cilinder::get_espec_int() const { return spec; }
Light::Intensity Cilinder::get_env_int() const { return env; }
