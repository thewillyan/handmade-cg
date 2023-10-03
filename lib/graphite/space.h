#ifndef Graphite_Space_H
#define Graphite_Space_H

#include "../algebrick/point3d.h"
#include "object.h"
#include "ray.h"
#include <SDL2/SDL_pixels.h>
#include <initializer_list>
#include <optional>
#include <utility>
#include <vector>

namespace Graphite {

class Space {
private:
  std::vector<Object *> objs;

public:
  Space();
  Space(std::initializer_list<Object *>);
  ~Space();

  void add_obj(Object *);
  std::optional<PointColor> intersect(Ray ray) const;
};

} // namespace Graphite
#endif // !Graphite_Space_H
