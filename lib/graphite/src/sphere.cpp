#include "../include/sphere.hpp"
#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/ray.hpp"
#include <SDL2/SDL_pixels.h>
#include <algorithm>
#include <cmath>
#include <utility>

using namespace Graphite;

Sphere::Sphere(Algebrick::Point3d c, double r, SDL_Color pcolor)
    : center{c}, radius{r}, color{pcolor}, reflect{1} {}
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
      Algebrick::Point3d(ray.direction() * ray_inter_scalar);
  return std::make_pair(std::move(inter_point), color);
}
std::optional<Algebrick::Vec3d>
Sphere::normal(const Algebrick::Point3d &p) const {
  return (p - center).norm();
}

double Sphere::get_reflection() const { return reflect; }
void Sphere::set_reflection(double k) { reflect = k; }
