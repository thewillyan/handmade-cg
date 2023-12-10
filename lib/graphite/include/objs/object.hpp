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

class Object;

using RayLenObj = std::pair<double, Object *>;

class Object {

private:
  bool visible;
  unsigned long int id;
  static unsigned long int id_counter;
  class Object *container_obj = nullptr;

public:
  Object();
  virtual std::optional<RayLenObj>
  intersect(const Algebrick::Ray &ray) const = 0;
  virtual std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const = 0;
  virtual ~Object(){};

  // getters
  unsigned long int get_id() const;
  bool is_visible() const;
  virtual ObjectIntensity get_intensity(const Algebrick::Point3d &) const = 0;
  Object *get_container_obj() const;

  // transformations
  virtual void translate(const Algebrick::Vec3d &offset) = 0;
  virtual void scale(double k) = 0;
  virtual void transform(const Algebrick::Matrix &matrix) = 0;

  void rotate_x(double angle);
  void rotate_y(double angle);
  void rotate_z(double angle);

  // setters
  void set_visible(bool v);
  void set_container_obj(Object *obj);
};

} // namespace Graphite::Object

#endif // !Graphite_Object_H
