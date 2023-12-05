#ifndef Graphite_Directed_Light
#define Graphite_Directed_Light

#include "algebrick/include/vec3d.hpp"
#include "light.hpp"

namespace Graphite::Light {

class Directed : public Source {
private:
  Intensity i;
  Algebrick::Vec3d decay;
  Algebrick::Vec3d direction;

public:
  Directed(Intensity base_intensity, Algebrick::Vec3d direction);

  Intensity get_intensity(const Object::Object &obj,
                          std::vector<Object::Object *> objs,
                          const Object::PointColor &inter,
                          const Algebrick::Ray &eye_ray) const override;
  void set_decay(double a, double b, double c);
  void transform(const Algebrick::Matrix &m) override;
};

} // namespace Graphite::Light

#endif // !Graphite_Directed_Light
