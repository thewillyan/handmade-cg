#ifndef Graphite_TriangularPlane
#define Graphite_TriangularPlane

#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/object.hpp"
#include <array>
#include <memory>

namespace Graphite::Object {

class TriangularPlane : public Object {
private:
  std::array<std::shared_ptr<Algebrick::Point3d>, 3> points;
  Algebrick::Vec3d norm;
  std::shared_ptr<ObjectIntensity> intensity;

public:
  TriangularPlane(std::array<std::shared_ptr<Algebrick::Point3d>, 3>);
  TriangularPlane(std::array<std::shared_ptr<Algebrick::Point3d>, 3>,
                  std::shared_ptr<ObjectIntensity>);

  std::optional<RayLenObj> intersect(const Algebrick::Ray &ray) const override;

  std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const override;

  // transformations
  void translate(const Algebrick::Vec3d &offset) override;
  void scale(double k) override;
  void transform(const Algebrick::Matrix &matrix) override;

  // getters
  ObjectIntensity get_intensity(const Algebrick::Point3d &) const override;

  // others
  void transform_norm(const Algebrick::Matrix &matrix);
};

} // namespace Graphite::Object
#endif // !Graphite_TriangularPlane
