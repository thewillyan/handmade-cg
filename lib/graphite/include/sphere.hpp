#ifndef Graphite_Sphere_Obj
#define Graphite_Sphere_Obj

#include "../../algebrick/include/point3d.hpp"
#include "graphite/include/intensity.hpp"
#include "object.hpp"
#include <SDL2/SDL_pixels.h>

namespace Graphite {
class Sphere : public Object {
private:
  Algebrick::Point3d center;
  double radius;
  SDL_Color color;
  double reflect;
  Light::Intensity dif;
  Light::Intensity espec;
  Light::Intensity env;

public:
  Sphere(Algebrick::Point3d, double, SDL_Color);
  Sphere(Algebrick::Point3d, double, SDL_Color, Light::Intensity,
         Light::Intensity, Light::Intensity);

  // object implementations
  ~Sphere();
  std::optional<PointColor> intersect(const Algebrick::Ray &ray) const override;
  std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const override;
  double get_reflection() const override;
  Light::Intensity get_dif_int() const override;
  Light::Intensity get_espec_int() const override;
  Light::Intensity get_env_int() const override;

  // transformations
  void translate(const Algebrick::Vec3d &offset) override;
  void scale(double k) override;

  // setters
  void set_reflection(double k);
};
} // namespace Graphite

#endif // !Graphite_Sphere_Obj
