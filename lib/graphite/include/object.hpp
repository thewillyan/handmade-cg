#ifndef Graphite_Object_H
#define Graphite_Object_H

#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/ray.hpp"
#include "../../algebrick/include/vec3d.hpp"
#include <SDL2/SDL_pixels.h>
#include <optional>
#include <utility>

namespace Graphite {

using PointColor = std::pair<Algebrick::Point3d, SDL_Color>;

class Object {
public:
  virtual std::optional<PointColor>
  intersect(const Algebrick::Ray &ray) const = 0;
  virtual std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const = 0;
  virtual ~Object(){};
  virtual double get_reflection() const = 0;
};

} // namespace Graphite

#endif // !Graphite_Object_H
