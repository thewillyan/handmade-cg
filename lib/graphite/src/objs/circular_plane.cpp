#include "graphite/include/objs/circular_plane.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/objs/object.hpp"
#include <utility>

using namespace Graphite::Object;

CircularPlane::CircularPlane(Algebrick::Point3d c, double r, Algebrick::Vec3d n)
    : center{c}, radius{r}, norm{n} {}

CircularPlane::CircularPlane(Algebrick::Point3d c, double r, Algebrick::Vec3d n,
                             Light::Intensity e, Light::Intensity d,
                             Light::Intensity es, double s)
    : center{c}, radius{r}, norm{n}, intensity{s, e, d, es} {}

std::optional<RayLenObj>
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

  return std::make_pair(tInt, (Object *)this);
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
  Algebrick::Matrix to_transform = {
      {center.x, norm.x},
      {center.y, norm.y},
      {center.z, norm.z},
      {1.0, 0.0},
  };
  Algebrick::Matrix transformed = matrix.mul(to_transform);
  center = Algebrick::Point3d{transformed.get(0, 0), transformed.get(1, 0),
                              transformed.get(2, 0)};
  norm = Algebrick::Vec3d{transformed.get(0, 1), transformed.get(1, 1),
                          transformed.get(2, 1)}
             .norm();
}
