#ifndef Graphite_CircularPlane
#define Graphite_CircularPlane

#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/objs/object.hpp"

namespace Graphite::Object {

class CircularPlane : public Object {
private:
  Algebrick::Point3d center;
  double radius;
  Algebrick::Vec3d norm;
  ObjectIntensity intensity;

public:
  CircularPlane(Algebrick::Point3d, double, Algebrick::Vec3d);
  CircularPlane(Algebrick::Point3d, double, Algebrick::Vec3d, Light::Intensity,
                Light::Intensity, Light::Intensity, double);

  virtual std::optional<PointColor> intersect(const Algebrick::Ray &ray) const;
  virtual std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const;

  // transformtions
  void translate(const Algebrick::Vec3d &offset);
  void scale(double k);
  void transform(const Algebrick::Matrix &matrix) override;

  // getters
  ObjectIntensity get_intensity(const Algebrick::Point3d &p) const override;
};

} // namespace Graphite::Object

#endif // !Graphite_CircularPlane
