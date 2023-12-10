#ifndef Graphite_Object_Cube
#define Graphite_Object_Cube

#include "algebrick/include/point3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/object.hpp"
#include "graphite/include/objs/tri_list.hpp"
#include <memory>

namespace Graphite::Object {

class Cube : public Object {
private:
  Algebrick::Point3d center;
  double side_size;
  TriList mesh;

public:
  Cube(Algebrick::Point3d center, double side_size,
       std::shared_ptr<ObjectIntensity> intensity);

  // getters
  Algebrick::Point3d get_center() const;
  double get_side_size() const;

  std::optional<RayLenObj> intersect(const Algebrick::Ray &ray) const;
  std::optional<Algebrick::Vec3d> normal(const Algebrick::Point3d &p) const;

  // getters
  ObjectIntensity get_intensity(const Algebrick::Point3d &) const;

  // transformations
  void translate(const Algebrick::Vec3d &offset);
  void scale(double k);
  void transform(const Algebrick::Matrix &matrix);
};
} // namespace Graphite::Object

#endif // !Graphite_Object_Cube
