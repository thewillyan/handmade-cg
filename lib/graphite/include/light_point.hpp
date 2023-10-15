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
  Intensity get_intensity(const Object &obj, const PointColor &inter,
                          const Algebrick::Ray &eye_ray) const;
  // setters
  void set_decay(double a, double b, double c);
};

} // namespace Graphite::Light

#endif // !Graphite_Light_Point