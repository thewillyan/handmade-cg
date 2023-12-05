#include "graphite/include/space.hpp"
#include "algebrick/include/matrix.hpp"
#include "algebrick/include/ray.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/object.hpp"
#include <SDL2/SDL_pixels.h>
#include <cmath>
#include <initializer_list>
#include <optional>
#include <utility>
#include <vector>

using namespace Graphite;

Space::Space()
    : objs{std::vector<Object::Object *>()}, ambient_light{1, 1, 1},
      transform{Algebrick::Matrix::identity(4)} {}
Space::Space(std::initializer_list<Object::Object *> lst)
    : objs{std::vector(lst)}, ambient_light{1, 1, 1},
      transform{Algebrick::Matrix::identity(4)} {}
Space::~Space() {}

void Space::add_obj(Object::Object *obj) { objs.push_back(obj); }
void Space::add_light(Light::Source *l) { lights.push_back(l); }
void Space::set_ambient_light(Light::Intensity i) { ambient_light = i; }

Light::Intensity Space::light_intensity(const Object::Object &obj,
                                        const Object::PointColor &inter,
                                        const Algebrick::Ray &eye_ray) const {
  Object::ObjectIntensity oi = obj.get_intensity(inter.first);
  Light::Intensity total = (ambient_light * oi.get_ambient_intensity());
  for (auto l : lights) {
    total = total + l->get_intensity(obj, objs, inter, eye_ray);
  }
  return total;
}
void Space::set_transform(Algebrick::Matrix m) {
  // TODO: invert transform
  for (Object::Object *obj : objs) {
    obj->transform(m);
  }
  for (Light::Source *l : lights) {
    l->transform(m);
  }
}
void Space::reset_transform() {
  Algebrick::Matrix inv = Algebrick::Matrix::inv(transform);
  for (Object::Object *obj : objs) {
    obj->transform(inv);
  }
}

std::optional<Object::PointColor>
Space::intersect(const Algebrick::Ray &ray) const {
  std::optional<Object::PointColor> pc{};
  double op_len = INFINITY;
  Object::Object *inter_obj = nullptr;
  for (Graphite::Object::Object *obj : objs) {
    std::optional<Object::PointColor> inter = obj->intersect(ray);
    if (inter.has_value()) {
      double ray_len = (inter->first - ray.source()).length();
      if (op_len > ray_len) {
        pc = std::move(inter);
        op_len = ray_len;
        inter_obj = obj;
      }
    }
  }
  if (!pc.has_value()) {
    return {};
  }

  SDL_Color color =
      static_cast<SDL_Color>(light_intensity(*inter_obj, *pc, ray));
  return std::make_pair(pc->first, color);
}
