#include "graphite/include/objs/circular_plane.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include <utility>

using namespace Graphite::Object;

CircularPlane::CircularPlane(Algebrick::Point3d c, double r, Algebrick::Vec3d n)
    : center{c}, radius{r}, norm{n} {}

CircularPlane::CircularPlane(Algebrick::Point3d c, double r, Algebrick::Vec3d n,
                             Light::Intensity e, Light::Intensity d,
                             Light::Intensity es, double s)
    : center{c}, radius{r}, norm{n}, intensity{s, e, d, es} {}

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
ObjectIntensity CircularPlane::get_intensity(
    [[maybe_unused]] const Algebrick::Point3d &p) const {
  return intensity;
};

void CircularPlane::translate(const Algebrick::Vec3d &offset) {
  center += offset;
}
void CircularPlane::scale(double k) { radius *= k; }
void CircularPlane::transform(const Algebrick::Matrix &matrix) {
  Algebrick::Matrix center_4d = {{center.x}, {center.y}, {center.z}, {1}};
  Algebrick::Matrix new_center = matrix * center_4d;
  center = {new_center.get(0, 0), new_center.get(1, 0), new_center.get(2, 0)};

  Algebrick::Matrix norm_4d = {{norm.x}, {norm.y}, {norm.z}, {0}};
  Algebrick::Matrix new_norm = matrix * norm_4d;
  norm = {new_norm.get(0, 0), new_norm.get(1, 0), new_norm.get(2, 0)};
  norm = norm.norm();
}
