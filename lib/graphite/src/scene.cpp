#include "../include/scene.hpp"
#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/ray.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <cstddef>
#include <optional>

using namespace Graphite;

// constructors
FrameRef::FrameRef() : x{1, 0, 0}, y{0, 1, 0}, z{0, 0, -1}, o{0, 0, 0} {}
FrameRef::FrameRef(const Algebrick::Point3d &p, const Algebrick::Point3d &up,
                   const Algebrick::Point3d &look_at)
    : y{(up - p).norm()}, z{(look_at - p).norm()}, o{p} {
  x = y.cross(z);
};

// getters
const Algebrick::Vec3d &FrameRef::x_axis() const { return x; }
const Algebrick::Vec3d &FrameRef::y_axis() const { return y; }
const Algebrick::Vec3d &FrameRef::z_axis() const { return z; }
const Algebrick::Point3d &FrameRef::origin() const { return o; }

Scene::Scene(Space *s) : space{s}, bg{} {};
Scene::Scene(Space *s, FrameRef e) : eye_pov{e}, space{s}, bg{} {};
Scene::~Scene() {}

// getters
Space &Scene::get_space() { return *space; }
std::optional<SDL_Color> Scene::get_bg_color() const { return bg; }

// setters
void Scene::set_space(Space *s) { space = s; }
void Scene::set_bg_color(SDL_Color color) { bg = color; }

void Scene::render(Canvas &c, double d) const {
  const double half_w = static_cast<double>(c.get_width()) / 2;
  const double half_h = static_cast<double>(c.get_height()) / 2;

  for (size_t i = 0; i < c.get_width(); ++i) {
    const double x = static_cast<double>(i) + (1.0 / 2.0) - half_w;
    for (size_t j = 0; j < c.get_height(); ++j) {
      const double y = static_cast<double>(j) + (1.0 / 2.0) - half_h;
      // center point of an canvas "block"
      Algebrick::Point3d p{x, y, -d};
      auto ray = Algebrick::Ray(eye_pov.origin(), p);
      std::optional<PointColor> point_color = space->intersect(ray);

      SDL_Point canvas_point{static_cast<int>(i), static_cast<int>(j)};
      std::optional<SDL_Color> color =
          (point_color.has_value()) ? point_color->second : bg;

      if (color.has_value()) {
        c.set_pixel(canvas_point, *color);
      }
    }
  }
}
