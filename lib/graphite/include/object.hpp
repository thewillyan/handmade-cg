#ifndef Graphite_Object_H
#define Graphite_Object_H

#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/ray.hpp"
#include "../../algebrick/include/vec3d.hpp"
#include "graphite/include/intensity.hpp"
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

  unsigned long int get_id() const;
  virtual bool is_visible() const = 0;
  virtual double get_reflection() const = 0;
  virtual Light::Intensity get_dif_int() const = 0;
  virtual Light::Intensity get_espec_int() const = 0;
  virtual Light::Intensity get_env_int() const = 0;
};

} // namespace Graphite

#endif // !Graphite_Object_H
