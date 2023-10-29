#include "graphite/include/plane.hpp"
#include "algebrick/include/point3d.hpp"
#include <SDL2/SDL_pixels.h>
#include <utility>

using namespace Graphite;

Plane::Plane(Algebrick::Point3d p, Algebrick::Vec3d n, SDL_Color c, double s)
    : point{p}, norm{n}, color{c}, shine{s}, dif{1, 1, 1}, espec{1, 1, 1},
      env{1, 1, 1} {}

Plane::Plane(Algebrick::Point3d p, Algebrick::Vec3d n, SDL_Color c, double s,
             Light::Intensity d, Light::Intensity e, Light::Intensity en)
    : point{p}, norm{n}, color{c}, shine{s}, dif{d}, espec{e}, env{en} {}

std::optional<PointColor> Plane::intersect(const Algebrick::Ray &ray) const {
  double denom = norm * ray.direction();
  if (denom == 0)
    return {};
  double tInt = (point - ray.source()) * (norm / denom);

  if (tInt <= 0)
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
void Plane::set_reflection(double k) { shine = k; }
Light::Intensity Plane::get_dif_int() const { return dif; }
Light::Intensity Plane::get_espec_int() const { return espec; }
Light::Intensity Plane::get_env_int() const { return env; }
