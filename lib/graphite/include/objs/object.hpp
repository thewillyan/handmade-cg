#ifndef Graphite_Object_H
#define Graphite_Object_H

#include "algebrick/include/matrix.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/ray.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include <SDL2/SDL_pixels.h>
#include <optional>
#include <utility>

namespace Graphite::Object {

using PointColor = std::pair<Algebrick::Point3d, SDL_Color>;

class Object {

private:
  bool visible;
  unsigned long int id;
  static unsigned long int id_counter;

public:
  Object() : visible{true}, id{id_counter++} {};
  // TODO: replace return value by a tuple of the format (double, *Object).
  virtual std::optional<PointColor>
  intersect(const Algebrick::Ray &ray) const = 0;
  virtual std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const = 0;
  virtual ~Object(){};

  // getters
  unsigned long int get_id() const { return id; };
  bool is_visible() const { return visible; };
  virtual ObjectIntensity get_intensity(const Algebrick::Point3d &) const = 0;

  // transformations
  virtual void translate(const Algebrick::Vec3d &offset) = 0;
  virtual void scale(double k) = 0;
  virtual void transform(const Algebrick::Matrix &matrix) = 0;
  // TODO: rotation

  // setters
  void set_visible(bool v) { visible = v; };
};

} // namespace Graphite::Object

#endif // !Graphite_Object_H
