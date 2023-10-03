#include "space.h"
#include "../algebrick/point3d.h"
#include "object.h"
#include "ray.h"
#include <SDL2/SDL_pixels.h>
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <optional>
#include <utility>
#include <vector>

using namespace Graphite;

Space::Space() : objs{std::vector<Object *>()} {}
Space::Space(std::initializer_list<Object *> lst) : objs{std::vector(lst)} {}
void Space::add_obj(Object *obj) { objs.push_back(obj); }

std::optional<PointColor> Space::intersect(Ray ray) const {
  std::optional<PointColor> pc{};
  double op_len = INFINITY;
  for (Graphite::Object *obj : objs) {
    std::optional<PointColor> inter = obj->intersect(ray);
    if (inter.has_value()) {
      double ray_len = (inter->first - ray.source()).length();
      if (op_len > ray_len) {
        pc = std::move(inter);
        op_len = ray_len;
      }
    }
  }
  return pc;
}
