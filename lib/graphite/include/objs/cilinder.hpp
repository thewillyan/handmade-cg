#ifndef Graphite_Cilinder
#define Graphite_Cilinder

#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/objs/circular_plane.hpp"
#include "object.hpp"
#include <optional>

namespace Graphite::Object {

class Cilinder : public Object {
private:
  double radius;
  double height;
  Algebrick::Vec3d dir;
  Algebrick::Point3d base_center;
  // TODO: Remove this and define the cylinder mathematically
  CircularPlane base;
  CircularPlane top;
  ObjectIntensity intensity;

public:
  Cilinder(const Algebrick::Point3d &, const Algebrick::Vec3d &, double, double,
           double);
  Cilinder(const Algebrick::Point3d &, const Algebrick::Vec3d &, double, double,
           double, const Light::Intensity &, const Light::Intensity &,
           const Light::Intensity &);

  std::optional<PointColor> intersect(const Algebrick::Ray &ray) const override;
  std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const override;
  ObjectIntensity get_intensity(const Algebrick::Point3d &p) const override;

  // transformations
  void translate(const Algebrick::Vec3d &offset) override;
  void scale(double k) override;
  void transform(const Algebrick::Matrix &) override;

  // setters
  void set_reflection(double k);
};
} // namespace Graphite::Object

#endif // Graphite_Cilinder
