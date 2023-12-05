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
  Light::Intensity env;
  Light::Intensity dif;
  Light::Intensity espec;
  double shiness;

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
  virtual double get_reflection() const;
  virtual Light::Intensity get_dif_int() const;
  virtual Light::Intensity get_espec_int() const;
  virtual Light::Intensity get_env_int() const;
};

} // namespace Graphite::Object

#endif // !Graphite_CircularPlane
