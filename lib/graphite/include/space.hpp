#ifndef Graphite_Space_H
#define Graphite_Space_H

#include "algebrick/include/matrix.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/ray.hpp"
#include "intensity.hpp"
#include "light.hpp"
#include "objs/object.hpp"
#include <SDL2/SDL_pixels.h>
#include <initializer_list>
#include <optional>
#include <vector>

namespace Graphite {

class Space {
private:
  std::vector<Object::Object *> objs;
  std::vector<Light::Source *> lights;
  Light::Intensity ambient_light;
  Algebrick::Matrix transform;

public:
  Space();
  Space(std::initializer_list<Object::Object *>);
  ~Space();

  void add_obj(Object::Object *);
  void add_light(Light::Source *);
  void set_ambient_light(Light::Intensity i);
  void set_transform(Algebrick::Matrix m);
  void reset_transform();

  Light::Intensity light_intensity(const Object::Object &obj,
                                   const Algebrick::Point3d &inter_point,
                                   const Algebrick::Ray &eye_ray) const;
  std::optional<SDL_Color> intersect(const Algebrick::Ray &ray) const;
};

} // namespace Graphite
#endif // !Graphite_Space_H
