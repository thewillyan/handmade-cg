#ifndef Graphite_Object_H
#define Graphite_Object_H

#include "../algebrick/point3d.h"
#include "ray.h"
#include <SDL2/SDL_pixels.h>
#include <optional>
#include <utility>

namespace Graphite {

using PointColor = std::pair<Algebrick::Point3d, SDL_Color>;

class Object {
public:
  virtual std::optional<PointColor> intersect(Ray ray) const;
  ~Object();
};

} // namespace Graphite

#endif // !Graphite_Object_H
