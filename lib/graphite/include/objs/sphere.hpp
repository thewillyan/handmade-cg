#ifndef Graphite_Sphere_Obj
#define Graphite_Sphere_Obj

#include "algebrick/include/matrix.hpp"
#include "algebrick/include/point3d.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "object.hpp"
#include <SDL2/SDL_pixels.h>

namespace Graphite::Object {
class Sphere : public Object {
private:
  Algebrick::Point3d center;
  double radius;
  SDL_Color color;
  ObjectIntensity intensity;

public:
  Sphere(Algebrick::Point3d, double, SDL_Color);
  Sphere(Algebrick::Point3d, double, SDL_Color, Light::Intensity,
         Light::Intensity, Light::Intensity);

  // object implementations
  ~Sphere();
  std::optional<RayLenObj> intersect(const Algebrick::Ray &ray) const override;
  std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const override;
  ObjectIntensity get_intensity(const Algebrick::Point3d &p) const override;

  // transformations
  void translate(const Algebrick::Vec3d &offset) override;
  void scale(double k) override;
  void transform(const Algebrick::Matrix &matrix) override;

  // setters
  void set_reflection(double k);
};
} // namespace Graphite::Object

#endif // !Graphite_Sphere_Obj
