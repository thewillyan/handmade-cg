#include "graphite/include/objs/triangular_plane.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include <stdexcept>
#include <utility>

using namespace Graphite::Object;

TriangularPlane::TriangularPlane(Algebrick::Point3d p0, Algebrick::Point3d p1,
                                 Algebrick::Point3d p2)
    : p0{p0}, p1{p1}, p2{p2}, shiness{1}, env{1, 1, 1}, espec{1, 1, 1}, diff{
                                                                            1,
                                                                            1,
                                                                            1} {
  Algebrick::Vec3d r1 = p1 - p0;
  Algebrick::Vec3d r2 = p2 - p0;
  norm = r1.cross(r2).norm();
}

TriangularPlane::TriangularPlane(Algebrick::Point3d p0, Algebrick::Point3d p1,
                                 Algebrick::Point3d p2, double shiness,
                                 Light::Intensity env, Light::Intensity espec,
                                 Light::Intensity diff)
    : p0{p0}, p1{p1}, p2{p2}, shiness{shiness}, env{env}, espec{espec},
      diff{diff} {

  Algebrick::Vec3d r1 = p1 - p0;
  Algebrick::Vec3d r2 = p2 - p0;
  norm = r1.cross(r2).norm();
}

std::optional<PointColor>
TriangularPlane::intersect(const Algebrick::Ray &ray) const {
  double k = -((ray.source() - p0) * norm) / (ray.direction() * norm);
  if (k < 0) {
    return {};
  }

  Algebrick::Point3d p_int = ray.source() + (ray.direction() * k);

  Algebrick::Vec3d r1 = p1 - p0;
  Algebrick::Vec3d r2 = p2 - p0;
  Algebrick::Vec3d v = p_int - p0;
  double denom = r1.cross(r2) * norm;

  double c1 = (v.cross(r2) * norm) / denom;
  if (c1 < 0) {
    return {};
  }

  double c2 = (r1.cross(v) * norm) / denom;
  if (c2 < 0) {
    return {};
  }

  double c3 = 1 - c1 - c2;
  if (c3 < 0) {
    return {};
  }

  return std::make_pair(p_int, SDL_Color{0, 0, 0, 255});
}

std::optional<Algebrick::Vec3d>
TriangularPlane::normal([[maybe_unused]] const Algebrick::Point3d &p) const {
  return norm;
}

// getters
double TriangularPlane::get_reflection() const { return shiness; }
Graphite::Light::Intensity TriangularPlane::get_dif_int() const { return diff; }
Graphite::Light::Intensity TriangularPlane::get_espec_int() const {
  return espec;
}
Graphite::Light::Intensity TriangularPlane::get_env_int() const { return env; }

void TriangularPlane::translate(const Algebrick::Vec3d &offset) {
  p0 += offset;
  p1 += offset;
  p2 += offset;
}
void TriangularPlane::scale(double k) {
  if (k <= 0) {
    throw std::invalid_argument("Scale factor less than 0");
  } else if (k < 1) {
    k = -(1.0 / k);
  }

  Algebrick::Point3d center = {(p0.x + p1.x + p2.x) / 3,
                               (p0.y + p1.y + p2.y) / 3,
                               (p0.z + p1.z + p2.z) / 3};

  for (Algebrick::Point3d *p_ptr : {&p0, &p1, &p2}) {
    // distance to the center of the triangle.
    Algebrick::Vec3d distc = (*p_ptr - center);
    Algebrick::Vec3d offset = distc.norm() * k;
    *p_ptr += offset;
  }
}
void TriangularPlane::transform(const Algebrick::Matrix &matrix) {
  Algebrick::Matrix new_p0 = matrix * Algebrick::Matrix{{p0.x, p0.y, p0.z, 1}};
  Algebrick::Matrix new_p1 = matrix * Algebrick::Matrix{{p1.x, p1.y, p1.z, 1}};
  Algebrick::Matrix new_p2 = matrix * Algebrick::Matrix{{p2.x, p2.y, p2.z, 1}};

  p0 = {new_p0.get(0, 0), new_p0.get(1, 0), new_p0.get(2, 0)};
  p1 = {new_p1.get(0, 0), new_p1.get(1, 0), new_p1.get(2, 0)};
  p2 = {new_p2.get(0, 0), new_p2.get(1, 0), new_p2.get(2, 0)};

  Algebrick::Matrix new_norm =
      matrix * Algebrick::Matrix{{norm.x, norm.y, norm.z}};
  norm = Algebrick::Vec3d{new_norm.get(0, 0), new_norm.get(1, 0),
                          new_norm.get(2, 0)}
             .norm();
}
