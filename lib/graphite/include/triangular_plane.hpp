#ifndef Graphite_TriangularPlane
#define Graphite_TriangularPlane

#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/object.hpp"

namespace Graphite {

class TriangularPlane : public Object {
private:
  Algebrick::Point3d p0;
  Algebrick::Point3d p1;
  Algebrick::Point3d p2;
  Algebrick::Vec3d norm;
  double shiness;
  Light::Intensity env;
  Light::Intensity espec;
  Light::Intensity diff;

public:
  TriangularPlane(Algebrick::Vec3d p0, Algebrick::Vec3d p1,
                  Algebrick::Vec3d p2);
  TriangularPlane(Algebrick::Vec3d, Algebrick::Vec3d, Algebrick::Vec3d,
                  double shiness, Light::Intensity env, Light::Intensity espec,
                  Light::Intensity diff);

  virtual std::optional<PointColor> intersect(const Algebrick::Ray &ray) const;

  virtual std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const;

  // transformations
  void translate(const Algebrick::Vec3d &offset);

  // getters
  virtual double get_reflection() const;
  virtual Light::Intensity get_dif_int() const;
  virtual Light::Intensity get_espec_int() const;
  virtual Light::Intensity get_env_int() const;
};

} // namespace Graphite

#endif // !Graphite_TriangularPlane
