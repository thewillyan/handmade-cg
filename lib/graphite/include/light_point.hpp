#ifndef Graphite_Light_Point
#define Graphite_Light_Point

#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/vec3d.hpp"
#include "light.hpp"

namespace Graphite::Light {

class Point : public Source {
private:
  Algebrick::Point3d p;
  Intensity i;
  Algebrick::Vec3d decay;

public:
  // constructor
  Point(Algebrick::Point3d point, Intensity base_intensity);

  // source definitions
  Intensity get_intensity(const Object::Object &obj,
                          std::vector<Object::Object *> objs,
                          const Algebrick::Point3d &inter_point,
                          const Algebrick::Ray &eye_ray) const override;
  // setters
  void set_decay(double a, double b, double c);
  void transform(const Algebrick::Matrix &m) override;
};

} // namespace Graphite::Light

#endif // !Graphite_Light_Point
