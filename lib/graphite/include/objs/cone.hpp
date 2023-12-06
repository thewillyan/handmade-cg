#ifndef Graphite_Cone
#define Graphite_Cone

#include "algebrick/include/matrix.hpp"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/objs/circular_plane.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/object.hpp"

namespace Graphite::Object {

class Cone : public Object {
private:
  double radius;
  double height;
  double aperture;
  Algebrick::Vec3d norm;
  Algebrick::Point3d center;
  Algebrick::Point3d top;
  CircularPlane base;
  ObjectIntensity intensity;

public:
  Cone(double h, double radius, Algebrick::Point3d base_center,
       Algebrick::Vec3d n);
  Cone(double h, double radius, Algebrick::Point3d base_center,
       Algebrick::Vec3d n, double shiness, Light::Intensity env,
       Light::Intensity esp, Light::Intensity dif);

  std::optional<PointColor> intersect(const Algebrick::Ray &ray) const override;

  std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const override;
  void translate(const Algebrick::Vec3d &offset) override;
  void scale(double k) override;
  void transform(const Algebrick::Matrix &) override;

  // getters
  ObjectIntensity get_intensity(const Algebrick::Point3d &p) const override;
};
} // namespace Graphite::Object

#endif // !Graphite_Cone
