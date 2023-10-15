#include "../include/space.hpp"
#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/ray.hpp"
#include "../include/object.hpp"
#include <SDL2/SDL_pixels.h>
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <optional>
#include <utility>
#include <vector>

using namespace Graphite;

Space::Space() : objs{std::vector<Object *>()}, ambient_light{1, 1, 1} {}
Space::Space(std::initializer_list<Object *> lst)
    : objs{std::vector(lst)}, ambient_light{1, 1, 1} {}
Space::~Space() {}

void Space::add_obj(Object *obj) { objs.push_back(obj); }
void Space::add_light(Light::Source *l) { lights.push_back(l); }
void Space::set_ambient_light(Light::Intensity i) { ambient_light = i; }

Light::Intensity Space::light_intensity(const Object &obj,
                                        const PointColor &inter,
                                        const Algebrick::Ray &eye_ray) const {
  Light::Intensity total = (ambient_light * Light::Intensity(inter.second));
  for (auto l : lights) {
    total = total + l->get_intensity(obj, inter, eye_ray);
  }
  return total;
}

std::optional<PointColor> Space::intersect(const Algebrick::Ray &ray) const {
  std::optional<PointColor> pc{};
  double op_len = INFINITY;
  Object *inter_obj = nullptr;
  for (Graphite::Object *obj : objs) {
    std::optional<PointColor> inter = obj->intersect(ray);
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
