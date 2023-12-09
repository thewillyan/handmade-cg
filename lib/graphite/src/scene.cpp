#include "../include/scene.hpp"
#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/ray.hpp"
#include "algebrick/include/matrix.hpp"
#include "algebrick/include/vec3d.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <cstddef>
#include <optional>

using namespace Graphite;

// constructors
FrameRef::FrameRef() : x{1, 0, 0}, y{0, 1, 0}, z{0, 0, 1}, o{0, 0, 0} {}
FrameRef::FrameRef(const Algebrick::Point3d &p, const Algebrick::Point3d &up,
                   const Algebrick::Point3d &look_at)
    : z{(p - look_at).norm()}, o{p} {
  Algebrick::Vec3d view_up = up - p;
  x = view_up.cross(z);
  if (x.length() == 0) {
    throw std::invalid_argument("Invalid up vector.");
  }
  x = x.norm();
  y = z.cross(x).norm();
};

// getters
const Algebrick::Vec3d &FrameRef::x_axis() const { return x; }
const Algebrick::Vec3d &FrameRef::y_axis() const { return y; }
const Algebrick::Vec3d &FrameRef::z_axis() const { return z; }
const Algebrick::Point3d &FrameRef::origin() const { return o; }

// special methods
Algebrick::Matrix FrameRef::perspective_matrix() const {
  auto origin = static_cast<Algebrick::Vec3d>(o);
  Algebrick::Matrix m = {{x.x, x.y, x.z, -(x * origin)},
                         {y.x, y.y, y.z, -(y * origin)},
                         {z.x, z.y, z.z, -(z * origin)},
                         {0, 0, 0, 1}};
  return m;
}

Scene::Scene(Space *s)
    : space{s}, bg{}, mode{RenderMode::PERSPECTIVE}, oblique_dir{0, 0, 0} {};
Scene::Scene(Space *s, RenderMode m)
    : space{s}, bg{}, mode{m}, oblique_dir{0, 0, 0} {};
Scene::~Scene() {}

// getters
Space &Scene::get_space() { return *space; }
std::optional<SDL_Color> Scene::get_bg_color() const { return bg; }

// setters
void Scene::set_space(Space *s) { space = s; }
void Scene::set_bg_color(SDL_Color color) { bg = color; }
void Scene::set_render_mode(const RenderMode m) { mode = m; }
void Scene::set_eye_pov(FrameRef &&pov) { eye_pov = pov; }
void Scene::set_oblique_dir(const Algebrick::Vec3d &vec) { oblique_dir = vec; }

void Scene::render(Canvas &c, double d) const {
  const double pov_w = c.get_pov_width();
  const double pov_h = c.get_pov_height();
  const double half_w = static_cast<double>(pov_w) / 2;
  const double half_h = static_cast<double>(pov_h) / 2;
  const double dx = pov_w / c.get_width();
  const double dy = pov_h / c.get_height();
  const double half_dx = dx / 2;
  const double half_dy = dy / 2;

  if (mode == RenderMode::PERSPECTIVE) {
    Algebrick::Matrix perspective = eye_pov.perspective_matrix();
    space->set_transform(perspective);
  }

  for (size_t i = 0; i < c.get_width(); ++i) {
    const double x = -half_w + half_dx + static_cast<double>(i) * dx;
    for (size_t j = 0; j < c.get_height(); ++j) {
      const double y = half_h - half_dy - static_cast<double>(j) * dy;
      // center point of an canvas "block"
      Algebrick::Ray const *ray;
      Algebrick::Point3d p{x, y, -d};

      switch (mode) {
      case RenderMode::PERSPECTIVE: {
        ray = new Algebrick::Ray{{0, 0, 0}, p};
        break;
      }
      case RenderMode::ORTHOGRAPHIC: {
        ray = new Algebrick::Ray{p, -eye_pov.z_axis()};
        break;
      }
      case RenderMode::OBLIQUE:
        ray = new Algebrick::Ray{p, oblique_dir};
        break;
      }
      std::optional<SDL_Color> point_color = space->intersect(*ray);

      SDL_Point canvas_point{static_cast<int>(i), static_cast<int>(j)};
      std::optional<SDL_Color> color =
          (point_color.has_value()) ? point_color : bg;

      if (color.has_value()) {
        c.set_pixel(canvas_point, *color);
      }
    }
  }
}
