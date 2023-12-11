#ifndef Graphite_Object_Cube
#define Graphite_Object_Cube

#include "algebrick/include/point3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/tri_list.hpp"
#include <memory>

namespace Graphite::Object {

class Box {
public:
  static TriList *create_cube(Algebrick::Point3d center, double side_size,
                              std::shared_ptr<ObjectIntensity> intensity);
  static TriList *
  create_paralellepiped(Algebrick::Point3d center, double side_size1,
                        double side_size2, double side_size3,
                        std::shared_ptr<ObjectIntensity> intensity);
};
} // namespace Graphite::Object

#endif // !Graphite_Object_Cube
