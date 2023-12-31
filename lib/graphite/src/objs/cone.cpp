#include "graphite/include/objs/cone.hpp"
#include "algebrick/include/matrix.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "cmath"
#include "graphite/include/intensity.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/object.hpp"
#include <algorithm>
#include <cmath>
#include <utility>

using namespace Graphite::Object;

Cone::Cone(double h, double r, Algebrick::Point3d base_center,
           Algebrick::Vec3d n)
    : radius{r}, height{h}, aperture{std::acos(h / std::sqrt(r * r + h * h))},
      norm{n.norm()}, center{base_center}, top{base_center + n.norm() * h},
      base{base_center, r, -n.norm()} {}

Cone::Cone(double h, double r, Algebrick::Point3d base_center,
           Algebrick::Vec3d n, double shiness, Light::Intensity env,
           Light::Intensity esp, Light::Intensity dif)
    : radius{r}, height{h}, aperture{0.2}, norm{n.norm()}, center{base_center},
      top{base_center + n.norm() * h}, base{base_center, r,   -n.norm(), env,
                                            esp,         dif, shiness},
      intensity{shiness, env, esp, dif} {}

std::optional<RayLenObj> Cone::intersect(const Algebrick::Ray &ray) const {
  Algebrick::Vec3d w = ray.source() - center;
  double beta = std::pow(height, 2) / std::pow(radius, 2);
  double dr_dc = ray.direction() * norm;
  double w_dr = w * ray.direction();
  double w_dc = w * norm;

  double a = beta - std::pow(dr_dc, 2) * (beta + 1);
  double b = 2 * (beta * (w_dr - w_dc * dr_dc) - w_dc * dr_dc + height * dr_dc);
  double c = beta * (w * w) - std::pow(w_dc, 2) * (beta + 1) -
             std::pow(height, 2) + 2 * height * w_dc;

  double delta = std::pow(b, 2) - 4 * a * c;
  if (delta < 0) {
    return {};
  }

  if (delta == 0) {
    double t1 = (-b) / (2 * a);
    double v_dc =
        (center * (-1) + (ray.source() + ray.direction() * t1)) * norm;
    if (v_dc < 0 || v_dc > height) {
      return {};
    }
    return std::make_pair(t1, (Object *)this);
  }

  double t1 = (-b + std::sqrt(delta)) / (2 * a);
  double t2 = (-b - std::sqrt(delta)) / (2 * a);

  double v_dc = (center * (-1) + (ray.source() + ray.direction() * t1)) * norm;
  if (v_dc < 0 || v_dc > height) {
    t1 = -1;
  }

  v_dc = (center * (-1) + (ray.source() + ray.direction() * t2)) * norm;
  if (v_dc < 0 || v_dc > height) {
    t2 = -1;
  }

  if (t1 < 0 && t2 < 0) {
    return {};
  }

  if (t1 >= 0 && t2 >= 0) {
    double max = std::min(t1, t2);
    return std::make_pair(max, (Object *)this);
  }

  auto int_base = base.intersect(ray);
  if (int_base.has_value()) {
    Algebrick::Point3d p_int_base =
        ray.source() + ray.direction() * int_base->first;
    double v = (p_int_base - center).length();
    if (v > radius) {
      int_base = {};
    }
  }

  if (int_base.has_value()) {
    double t_int = std::max(t1, t2);
    if (int_base->first < t_int) {
      return std::make_pair(int_base->first, (Object *)this);
    }
    return std::make_pair(t_int, (Object *)this);
  }
  return {};
}

std::optional<Algebrick::Vec3d>
Cone::normal(const Algebrick::Point3d &p) const {
  Algebrick::Vec3d v_p = top - p;
  Algebrick::Vec3d v = p - center;
  double v_dc = v * norm;
  Algebrick::Vec3d n;

  if (auto err = 1e-12; err < v_dc) {
    n = (v_p.cross(norm).cross(v_p)).norm();
  } else {
    n = norm * -1;
  }
  return n;
}

void Cone::translate(const Algebrick::Vec3d &offset) {
  center += offset;
  top += offset;
  base.translate(offset);
}

void Cone::transform(const Algebrick::Matrix &matrix) {
  Algebrick::Matrix to_transform = {
      {center.x, top.x, norm.x},
      {center.y, top.y, norm.y},
      {center.z, top.z, norm.z},
      {1, 1, 0},
  };

  Algebrick::Matrix transformed = matrix.mul(to_transform);

  center = Algebrick::Point3d{transformed.get(0, 0), transformed.get(1, 0),
                              transformed.get(2, 0)};
  top = Algebrick::Point3d{transformed.get(0, 1), transformed.get(1, 1),
                           transformed.get(2, 1)};
  norm = Algebrick::Vec3d{transformed.get(0, 2), transformed.get(1, 2),
                          transformed.get(2, 2)}
             .norm();
  base.transform(matrix);
}

void Cone::scale(double k) {
  height *= k;
  base.scale(k);
}

// getters
ObjectIntensity
Cone::get_intensity([[maybe_unused]] const Algebrick::Point3d &p) const {
  return intensity;
}
