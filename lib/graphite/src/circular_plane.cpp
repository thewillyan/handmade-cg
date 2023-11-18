#include "graphite/include/circular_plane.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include <utility>

using namespace Graphite;

CircularPlane::CircularPlane(Algebrick::Point3d c, double r, Algebrick::Vec3d n)
    : center{c}, radius{r}, norm{n}, env{1, 1, 1}, dif{1, 1, 1}, espec{1, 1, 1},
      shiness{1} {}

CircularPlane::CircularPlane(Algebrick::Point3d c, double r, Algebrick::Vec3d n,
                             Light::Intensity e, Light::Intensity d,
                             Light::Intensity es, double s)

    : center{c}, radius{r}, norm{n}, env{e}, dif{d}, espec{es}, shiness{s} {}

std::optional<PointColor>
CircularPlane::intersect(const Algebrick::Ray &ray) const {
  double denom = norm * ray.direction();
  if (denom == 0)
    return {};

  double tInt = (center - ray.source()) * (norm / denom);

  if (tInt <= 0)
    return {};

  Algebrick::Vec3d p = ray.source() + (ray.direction() * tInt);
  Algebrick::Vec3d v = p - static_cast<Algebrick::Vec3d>(center);

  if (v.length() > radius)
    return {};

  return std::make_pair(Algebrick::Point3d(p), SDL_Color{0, 0, 0, 0});
}

std::optional<Algebrick::Vec3d>
CircularPlane::normal([[maybe_unused]] const Algebrick::Point3d &p) const {
  return norm;
}

// getters
double CircularPlane::get_reflection() const { return shiness; }
Light::Intensity CircularPlane::get_dif_int() const { return dif; }
Light::Intensity CircularPlane::get_espec_int() const { return espec; }
Light::Intensity CircularPlane::get_env_int() const { return env; }

void CircularPlane::translate(const Algebrick::Vec3d &offset) {
  center += offset;
}
