#include "graphite/include/objs/plane.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/object.hpp"
#include <SDL2/SDL_pixels.h>
#include <utility>

using namespace Graphite::Object;

std::pair<Algebrick::Vec3d, Algebrick::Vec3d> get_axis(Algebrick::Vec3d &norm) {
  double norm_vals[3]{norm.x, norm.y, norm.z};
  size_t min_idx = 0;
  for (size_t i = 1; i < 3; ++i) {
    if (norm_vals[min_idx] > norm_vals[i]) {
      min_idx = i;
    }
  }

  Algebrick::Vec3d paxis_x{};

  switch (min_idx) {
  case 0:
    paxis_x = {0, -norm.z, norm.y};
    break;
  case 1:
    paxis_x = {-norm.z, 0, norm.x};
    break;
  default:
    paxis_x = {-norm.y, norm.x, 0};
    break;
  }
  paxis_x = paxis_x.norm();
  Algebrick::Vec3d paxis_y = norm.cross(paxis_x).norm();
  return std::make_pair(paxis_x, paxis_y);
}

Plane::Plane(Algebrick::Point3d p, Algebrick::Vec3d n, SDL_Color c, double s)
    : point{p}, norm{n}, color{c} {
  auto axis = get_axis(norm);
  paxis_x = axis.first;
  paxis_y = axis.second;
  intensity.set_shineness(s);
}

Plane::Plane(Algebrick::Point3d p, Algebrick::Vec3d n, SDL_Color c, double s,
             Light::Intensity d, Light::Intensity e, Light::Intensity en)
    : point{p}, norm{n}, color{c}, intensity{s, en, e, d} {
  auto axis = get_axis(norm);
  paxis_x = axis.first;
  paxis_y = axis.second;
}

std::optional<RayLenObj> Plane::intersect(const Algebrick::Ray &ray) const {
  double denom = norm * ray.direction();
  if (denom == 0)
    return {};

  double tInt = (point - ray.source()) * (norm / denom);

  if (tInt <= 0)
    return {};

  return std::make_pair(tInt, (Object *)this);
}

std::optional<Algebrick::Vec3d>
Plane::normal([[maybe_unused]] const Algebrick::Point3d &p) const {
  return norm;
}

void Plane::set_reflection(double k) { intensity.set_shineness(k); }
ObjectIntensity Plane::get_intensity(const Algebrick::Point3d &p) const {
  if (texture == nullptr) {
    return intensity;
  }

  int i = static_cast<int>(paxis_x * (p - point));
  int j = static_cast<int>(paxis_y * (p - point));
  return {texture->get_color(i, j), intensity.get_shineness()};
}
void Plane::set_texture(Texture *t) { texture = t; }

void Plane::translate(const Algebrick::Vec3d &offset) { point += offset; }
void Plane::scale([[maybe_unused]] double k) {
  // This method is empty because a plane is infinite and cannot be scaled.
}
void Plane::transform(const Algebrick::Matrix &matrix) {
  Algebrick::Matrix to_transform = {
      {point.x, norm.x},
      {point.y, norm.y},
      {point.z, norm.z},
      {1.0, 0.0},
  };
  Algebrick::Matrix transformed = matrix.mul(to_transform);
  point = Algebrick::Point3d{transformed.get(0, 0), transformed.get(1, 0),
                             transformed.get(2, 0)};

  norm = Algebrick::Vec3d{transformed.get(0, 1), transformed.get(1, 1),
                          transformed.get(2, 1)}
             .norm();
}
