#ifndef Graphite_Directed_Light
#define Graphite_Directed_Light

#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/vec3d.hpp"
#include "light.hpp"

namespace Graphite::Light {

class Directed : public Source {
private:
  Algebrick::Point3d p;
  Intensity i;
  Algebrick::Vec3d decay;
  Algebrick::Vec3d direction;

public:
  Directed(Algebrick::Point3d point, Intensity base_intensity,
           Algebrick::Vec3d direction);

  Intensity get_intensity(const Object &obj, std::vector<Object *> objs,
                          const PointColor &inter,
                          const Algebrick::Ray &eye_ray) const override;
  void set_decay(double a, double b, double c);
  void transform(const Algebrick::Matrix &m) override;
};

} // namespace Graphite::Light

#endif // !Graphite_Directed_Light
