#ifndef Graphite_Scene
#define Graphite_Scene

#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/ray.hpp"
#include "../../algebrick/include/vec3d.hpp"
#include "../include/canvas.hpp"
#include "../include/space.hpp"

namespace Graphite {
class FrameRef {
private:
  Algebrick::Vec3d x;
  Algebrick::Vec3d y;
  Algebrick::Vec3d z;
  Algebrick::Point3d o;

public:
  FrameRef();
  FrameRef(const Algebrick::Point3d &, const Algebrick::Point3d &,
           const Algebrick::Point3d &);

  // getters
  const Algebrick::Vec3d &x_axis() const;
  const Algebrick::Vec3d &y_axis() const;
  const Algebrick::Vec3d &z_axis() const;
  const Algebrick::Point3d &origin() const;
};

class Scene {
private:
  const FrameRef space_ref;
  FrameRef eye_pov;
  Space *space;

public:
  Scene(Space *);
  Scene(Space *, FrameRef);
  ~Scene();

  Space &get_space();
  void render(Canvas &, double) const;
};
} // namespace Graphite

#endif // !Graphite_Scene