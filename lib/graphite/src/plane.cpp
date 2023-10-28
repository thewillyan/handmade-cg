#include "graphite/include/plane.hpp"
#include "algebrick/include/point3d.hpp"
#include <SDL2/SDL_pixels.h>
#include <utility>

using namespace Graphite;

Plane::Plane(Algebrick::Point3d p, Algebrick::Vec3d n, SDL_Color c, double s)
    : point{p}, norm{n}, color{c}, shine{s} {}

std::optional<PointColor> Plane::intersect(const Algebrick::Ray &ray) const {
  Algebrick::Vec3d w = ray.source() - point;
  double tInt = -(norm * w) / (norm * ray.direction());

  if (tInt >= 0)
    return {};

  Algebrick::Point3d pInt =
      ray.source() + Algebrick::Point3d(ray.direction() * tInt);
  return std::make_pair(pInt, color);
}

std::optional<Algebrick::Vec3d>
Plane::normal([[maybe_unused]] const Algebrick::Point3d &p) const {
  return norm;
}

double Plane::get_reflection() const { return shine; }
