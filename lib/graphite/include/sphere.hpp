#ifndef Graphite_Sphere_Obj
#define Graphite_Sphere_Obj

#include "../../algebrick/include/point3d.hpp"
#include "object.hpp"
#include <SDL2/SDL_pixels.h>

namespace Graphite {
class Sphere : public Object {
private:
  Algebrick::Point3d center;
  double radius;
  SDL_Color color;

public:
  Sphere(Algebrick::Point3d, double, SDL_Color);
  ~Sphere();
  std::optional<PointColor> intersect(const Algebrick::Ray &ray) const;
  std::optional<Algebrick::Vec3d> normal(const Algebrick::Point3d &p) const;
};
} // namespace Graphite

#endif // !Graphite_Sphere_Obj
