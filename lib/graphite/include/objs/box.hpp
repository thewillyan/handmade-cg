#ifndef Graphite_Object_Cube
#define Graphite_Object_Cube

#include "algebrick/include/point3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/tri_list.hpp"
#include <memory>

namespace Graphite::Object {

class Cube {
public:
  static TriList *create_cube(Algebrick::Point3d center, double side_size,
                              std::shared_ptr<ObjectIntensity> intensity);
};
} // namespace Graphite::Object

#endif // !Graphite_Object_Cube
