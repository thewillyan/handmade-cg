#ifndef Graphite_Light_Source
#define Graphite_Light_Source

#include "../../algebrick/include/ray.hpp"
#include "intensity.hpp"
#include "object.hpp"
#include <vector>

namespace Graphite::Light {

class Source {
public:
  virtual Intensity get_intensity(const Object &inter_obj, std::vector<Object *> objs,
                                  const PointColor &inter,
                                  const Algebrick::Ray &eye_ray) const = 0;
};
} // namespace Graphite::Light

#endif // !Graphite_Light_Source
