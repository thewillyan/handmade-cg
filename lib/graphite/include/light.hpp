#ifndef Graphite_Light_Source
#define Graphite_Light_Source

#include "algebrick/include/ray.hpp"
#include "intensity.hpp"
#include "objs/object.hpp"
#include <vector>

namespace Graphite::Light {

class Source {
public:
  virtual Intensity get_intensity(const Graphite::Object::Object &inter_obj,
                                  std::vector<Graphite::Object::Object *> objs,
                                  const Graphite::Object::PointColor &inter,
                                  const Algebrick::Ray &eye_ray) const = 0;
  virtual void transform(const Algebrick::Matrix &matrix) = 0;
};
} // namespace Graphite::Light

#endif // !Graphite_Light_Source
