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

  double ray_inter_scalar =
      std::min((-b + std::sqrt(delta)) / 2.0, (-b - std::sqrt(delta)) / 2.0);
  Algebrick::Point3d inter_point =
      Algebrick::Point3d(ray.direction() * ray_inter_scalar);
  return std::make_pair(std::move(inter_point), color);
}
std::optional<Algebrick::Vec3d>
Sphere::normal(const Algebrick::Point3d &p) const {
  auto v = (p - center);
  if (v.length() > radius) {
    return {};
  } else {
    return v.norm();
  }
}

double Sphere::get_reflection() const { return reflect; }
void Sphere::set_reflection(double k) { reflect = k; }
