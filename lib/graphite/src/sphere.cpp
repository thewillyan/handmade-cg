#include "../include/sphere.hpp"
#include <SDL2/SDL_pixels.h>
#include <cmath>
#include <utility>

using namespace Graphite;

Sphere::Sphere(Algebrick::Point3d c, double r, SDL_Color pcolor)
    : center{c}, radius{r}, color{pcolor} {}
Sphere::~Sphere() {}

std::optional<PointColor> Sphere::intersect(const Algebrick::Ray &ray) const {
  Algebrick::Vec3d w = ray.source() - center;
  double w_dr = w * ray.direction();
  double b = 2 * w_dr;
  double delta = std::pow(w_dr, 2) - ((w * w) - std::pow(radius, 2));
  if (delta < 0)
    return {};

  double ray_inter_scalar = (-b + std::sqrt(delta)) / 2;
  Algebrick::Point3d inter_point =
      Algebrick::Point3d(ray.direction() * ray_inter_scalar);
  return std::make_pair(std::move(inter_point), color);
}
