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
  Light::Intensity dif;
  Light::Intensity espec;
  Light::Intensity env;

public:
  Plane(Algebrick::Point3d p, Algebrick::Vec3d n, SDL_Color c, double s);
  Plane(Algebrick::Point3d, Algebrick::Vec3d, SDL_Color, double,
        Light::Intensity, Light::Intensity, Light::Intensity);

  // implement object
  std::optional<PointColor> intersect(const Algebrick::Ray &ray) const override;
  std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const override;
  double get_reflection() const override;
  Light::Intensity get_dif_int() const override;
  Light::Intensity get_espec_int() const override;
  Light::Intensity get_env_int() const override;

  // setters
  void set_reflection(double k);
};
} // namespace Graphite

#endif // Graphite_Plane
