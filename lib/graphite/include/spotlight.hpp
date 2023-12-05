#ifndef Graphite_Spot_Light
#define Graphite_Spot_Light

#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/vec3d.hpp"
#include "light.hpp"

namespace Graphite::Light {

class Spot : public Source {
private:
  Algebrick::Point3d p;
  Intensity i;
  Algebrick::Vec3d direction;
  double aperture;

public:
  Spot(Algebrick::Point3d point, Intensity base_intensity,
       Algebrick::Vec3d direction, double aperture);

  Intensity get_intensity(const Object::Object &obj,
                          std::vector<Object::Object *> objs,
                          const Object::PointColor &inter,
                          const Algebrick::Ray &eye_ray) const override;
  void transform(const Algebrick::Matrix &m) override;
};

} // namespace Graphite::Light

#endif // !Graphite_Spot_Light
