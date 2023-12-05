#include "graphite/include/objs/sphere.hpp"
#include "algebrick/include/matrix.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/ray.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/objs/object.hpp"
#include <SDL2/SDL_pixels.h>
#include <algorithm>
#include <cmath>
#include <utility>

using namespace Graphite::Object;

Sphere::Sphere(Algebrick::Point3d c, double r, SDL_Color pcolor)
    : center{c}, radius{r}, color{pcolor}, reflect{1}, dif{1, 1, 1},
      espec{1, 1, 1}, env{1, 1, 1} {}

Sphere::Sphere(Algebrick::Point3d c, double r, SDL_Color pcolor,
               Light::Intensity d, Light::Intensity esp, Light::Intensity en)
    : center{c}, radius{r}, color{pcolor}, reflect{1}, dif{d}, espec{esp},
      env{en} {}
Sphere::~Sphere() {}

std::optional<PointColor> Sphere::intersect(const Algebrick::Ray &ray) const {
  Algebrick::Vec3d w = ray.source() - center;
  double w_dr = w * ray.direction();
  double b = 2 * w_dr;
  double c = (w * w) - (std::pow(radius, 2));
  double delta = std::pow(b, 2) - (4 * c);

  if (delta < 0)
    return {};

  double x1 = (-b + std::sqrt(delta)) / 2.0;
  double x2 = (-b - std::sqrt(delta)) / 2.0;
  double ray_inter_scalar;

  if (x1 < 0 && x2 < 0) {
    return {};
  } else if (x2 < 0) {
    ray_inter_scalar = x1;
  } else if (x1 < 0) {
    ray_inter_scalar = x2;
  } else {
    ray_inter_scalar = std::min(x1, x2);
  }

  Algebrick::Point3d inter_point =
      ray.source() + Algebrick::Point3d(ray.direction() * ray_inter_scalar);
  return std::make_pair(std::move(inter_point), color);
}

std::optional<Algebrick::Vec3d>
Sphere::normal(const Algebrick::Point3d &p) const {
  return (p - center).norm();
}

double Sphere::get_reflection() const { return reflect; }
void Sphere::set_reflection(double k) { reflect = k; }
Graphite::Light::Intensity Sphere::get_dif_int() const { return dif; }
Graphite::Light::Intensity Sphere::get_espec_int() const { return espec; }
Graphite::Light::Intensity Sphere::get_env_int() const { return env; }

void Sphere::translate(const Algebrick::Vec3d &offset) { center += offset; }
void Sphere::scale(double k) { radius *= k; }
void Sphere::transform(const Algebrick::Matrix &matrix) {
  Algebrick::Matrix center_4d = {{center.x}, {center.y}, {center.z}, {1.0}};
  Algebrick::Matrix new_center = matrix * center_4d;
  center = {new_center.get(0, 0), new_center.get(1, 0), new_center.get(2, 0)};
}
