#ifndef Graphite_Cilinder
#define Graphite_Cilinder

#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/intensity.hpp"
#include "object.hpp"
#include <optional>

namespace Graphite {

class Cilinder : public Object {
private:
  double shineness;
  double radius;
  double height;
  Algebrick::Vec3d dir;
  Algebrick::Point3d base_center;

  Light::Intensity dif;
  Light::Intensity spec;
  Light::Intensity env;

public:
  Cilinder(const Algebrick::Point3d &, const Algebrick::Vec3d &, double, double,
           double);
  Cilinder(const Algebrick::Point3d &, const Algebrick::Vec3d &, double, double,
           double, const Light::Intensity &, const Light::Intensity &,
           const Light::Intensity &);

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

#endif // Graphite_Cilinder
