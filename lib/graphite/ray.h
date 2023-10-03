#ifndef Graphite_Ray_H
#define Graphite_Ray_H

#include "../algebrick/point3d.h"
#include "../algebrick/vec3d.h"

namespace Graphite {
class Ray {
private:
  // source
  Algebrick::Point3d src;
  // direction
  Algebrick::Vec3d dir;

public:
  Ray(Algebrick::Point3d s, const Algebrick::Vec3d &d)
      : src{s}, dir{d.norm()} {}

  // getters
  const Algebrick::Point3d &source() { return src; }
  const Algebrick::Vec3d &direction() { return dir; }
};

} // namespace Graphite

#endif // !Graphite_Ray_H
