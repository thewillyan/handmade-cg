#include "graphite/include/objs/triangular_plane.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include <memory>
#include <stdexcept>
#include <utility>

using namespace Graphite::Object;

TriangularPlane::TriangularPlane(
    std::array<std::shared_ptr<Algebrick::Point3d>, 3> ps)
    : points{ps} {
  Algebrick::Vec3d r1 = *points[1] - *points[0];
  Algebrick::Vec3d r2 = *points[2] - *points[0];
  norm = -r1.cross(r2).norm();
}

TriangularPlane::TriangularPlane(
    std::array<std::shared_ptr<Algebrick::Point3d>, 3> ps,
    std::shared_ptr<ObjectIntensity> i)
    : points{ps}, intensity{i} {
  Algebrick::Vec3d r1 = *points[1] - *points[0];
  Algebrick::Vec3d r2 = *points[2] - *points[0];
  norm = -r1.cross(r2).norm();
}

std::optional<RayLenObj>
TriangularPlane::intersect(const Algebrick::Ray &ray) const {
  double k = -((ray.source() - *points[0]) * norm) / (ray.direction() * norm);
  if (k < 0) {
    return {};
  }

  Algebrick::Point3d p_int = ray.source() + (ray.direction() * k);

  Algebrick::Vec3d r1 = *points[1] - *points[0];
  Algebrick::Vec3d r2 = *points[2] - *points[0];
  Algebrick::Vec3d v = p_int - *points[0];
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

  return std::make_pair(k, (Object *)this);
}

std::optional<Algebrick::Vec3d>
TriangularPlane::normal([[maybe_unused]] const Algebrick::Point3d &p) const {
  return norm;
}

// getters
ObjectIntensity TriangularPlane::get_intensity(
    [[maybe_unused]] const Algebrick::Point3d &p) const {
  return *intensity;
}
void TriangularPlane::translate(const Algebrick::Vec3d &offset) {
  for (std::shared_ptr<Algebrick::Point3d> &p : points) {
    *p += offset;
  }
}
void TriangularPlane::scale(double k) {
  if (k <= 0) {
    throw std::invalid_argument("Scale factor less than 0");
  } else if (k < 1) {
    k = -(1.0 / k);
  }

  Algebrick::Point3d center = {(points[0]->x + points[1]->x + points[2]->x) / 3,
                               (points[0]->y + points[1]->y + points[2]->y) / 3,
                               (points[0]->z + points[1]->z + points[2]->z) /
                                   3};

  for (std::shared_ptr<Algebrick::Point3d> p_ptr : points) {
    // distance to the center of the triangle.
    Algebrick::Vec3d distc = (*p_ptr - center);
    Algebrick::Vec3d offset = distc.norm() * k;
    *p_ptr += offset;
  }
}
void TriangularPlane::transform(const Algebrick::Matrix &matrix) {
  Algebrick::Matrix points_matrix = {{points[0]->x, points[1]->x, points[2]->x},
                                     {points[0]->y, points[1]->y, points[2]->y},
                                     {points[0]->z, points[1]->z, points[2]->z},
                                     {1, 1, 1}};

  Algebrick::Matrix new_points = matrix.mul(points_matrix);
  *points[0] = {new_points.get(0, 0), new_points.get(1, 0),
                new_points.get(2, 0)};
  *points[1] = {new_points.get(0, 1), new_points.get(1, 1),
                new_points.get(2, 1)};
  *points[2] = {new_points.get(0, 2), new_points.get(1, 2),
                new_points.get(2, 2)};
  transform_norm(matrix);
}

void TriangularPlane::transform_norm(const Algebrick::Matrix &matrix) {
  Algebrick::Matrix transf_norm =
      matrix.mul(Algebrick::Matrix{{norm.x}, {norm.y}, {norm.z}, {0}});
  Algebrick::Vec3d new_norm = Algebrick::Vec3d{
      transf_norm.get(0, 0), transf_norm.get(1, 0), transf_norm.get(2, 0)};
  norm = new_norm.norm();
}
