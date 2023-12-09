#ifndef Graphite_Obj_TriList
#define Graphite_Obj_TriList

#include "algebrick/include/point3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/triangular_plane.hpp"
#include <memory>
#include <vector>

namespace Graphite::Object {

class TriList : public Object {
private:
  std::vector<std::shared_ptr<Algebrick::Point3d>> vertex_list;
  std::vector<TriangularPlane> faces;

public:
  TriList();
  void add_face(std::array<Algebrick::Point3d, 3>,
                std::shared_ptr<ObjectIntensity>);

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

#endif // !Graphite_Obj_TriList
