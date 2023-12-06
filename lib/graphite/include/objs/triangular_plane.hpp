#ifndef Graphite_TriangularPlane
#define Graphite_TriangularPlane

#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/object.hpp"

namespace Graphite::Object {

class TriangularPlane : public Object {
private:
  Algebrick::Point3d p0;
  Algebrick::Point3d p1;
  Algebrick::Point3d p2;
  Algebrick::Vec3d norm;
  ObjectIntensity intensity;

public:
  TriangularPlane(Algebrick::Point3d p0, Algebrick::Point3d p1,
                  Algebrick::Point3d p2);
  TriangularPlane(Algebrick::Point3d, Algebrick::Point3d, Algebrick::Point3d,
                  double shiness, Light::Intensity env, Light::Intensity espec,
                  Light::Intensity diff);

  virtual std::optional<PointColor> intersect(const Algebrick::Ray &ray) const;

  virtual std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const;

  // transformations
  void translate(const Algebrick::Vec3d &offset);
  void scale(double k);
  void transform(const Algebrick::Matrix &matrix);

  // getters
  ObjectIntensity get_intensity(const Algebrick::Point3d &) const override;
};

} // namespace Graphite::Object
#endif // !Graphite_TriangularPlane