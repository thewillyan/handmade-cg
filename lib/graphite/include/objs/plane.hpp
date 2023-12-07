#ifndef Graphite_Plane
#define Graphite_Plane

#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/texture.hpp"
#include "object.hpp"
#include <optional>

namespace Graphite::Object {

class Plane : public Object {
private:
  Algebrick::Point3d point;
  Algebrick::Vec3d norm;
  Algebrick::Vec3d paxis_x;
  Algebrick::Vec3d paxis_y;

  SDL_Color color;
  ObjectIntensity intensity;
  Texture *texture;

public:
  Plane(Algebrick::Point3d p, Algebrick::Vec3d n, SDL_Color c, double s);
  Plane(Algebrick::Point3d, Algebrick::Vec3d, SDL_Color, double,
        Light::Intensity, Light::Intensity, Light::Intensity);

  // implement object
  std::optional<RayLenObj> intersect(const Algebrick::Ray &ray) const override;
  std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const override;
  ObjectIntensity get_intensity(const Algebrick::Point3d &p) const override;

  // transformations
  void translate(const Algebrick::Vec3d &offset) override;
  void scale(double k) override;
  void transform(const Algebrick::Matrix &matrix) override;

  // setters
  void set_reflection(double k);
  void set_texture(Texture *t);
};
} // namespace Graphite::Object

#endif // Graphite_Plane
