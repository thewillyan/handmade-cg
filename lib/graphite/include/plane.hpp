#ifndef Graphite_Plane
#define Graphite_Plane

#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/intensity.hpp"
#include "object.hpp"
#include <optional>

namespace Graphite {

class Plane : public Object {
private:
  Algebrick::Point3d point;
  Algebrick::Vec3d norm;
  SDL_Color color;
  double shine;

public:
  Plane(Algebrick::Point3d p, Algebrick::Vec3d n, SDL_Color c, double s);

  // implement object
  std::optional<PointColor> intersect(const Algebrick::Ray &ray) const;
  std::optional<Algebrick::Vec3d> normal(const Algebrick::Point3d &p) const;
  double get_reflection() const;
};
} // namespace Graphite

#endif // Graphite_Plane
