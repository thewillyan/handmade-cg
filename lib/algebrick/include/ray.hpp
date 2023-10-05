#ifndef Algebrick_Ray_H
#define Algebrick_Ray_H

#include "point3d.hpp"
#include "vec3d.hpp"

namespace Algebrick {
class Ray {
private:
  // source
  Algebrick::Point3d src;
  // direction
  Algebrick::Vec3d dir;

public:
  Ray(Algebrick::Point3d s, const Algebrick::Vec3d &d);
  Ray(Algebrick::Point3d s, const Algebrick::Point3d &d);

  // getters
  Algebrick::Point3d source() const;
  Algebrick::Vec3d direction() const;
};

} // namespace Algebrick

#endif // !Algebrick_Ray_H
