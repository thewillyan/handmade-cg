#include "graphite/include/objs/box.hpp"
#include "algebrick/include/point3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/tri_list.hpp"
#include <array>
#include <memory>

using namespace Graphite::Object;

TriList *Cube::create_cube(Algebrick::Point3d center, double side_size,
                           std::shared_ptr<ObjectIntensity> intensity) {
  auto mesh = new TriList();
  double half_side = side_size / 2.0;
  std::array<Algebrick::Point3d, 8> points = {
      center + Algebrick::Point3d{-half_side, half_side, -half_side},
      center + Algebrick::Point3d{half_side, -half_side, -half_side},
      center + Algebrick::Point3d{-half_side, -half_side, -half_side},
      center + Algebrick::Point3d{half_side, half_side, -half_side},
      center + Algebrick::Point3d{-half_side, half_side, half_side},
      center + Algebrick::Point3d{half_side, -half_side, half_side},
      center + Algebrick::Point3d{-half_side, -half_side, half_side},
      center + Algebrick::Point3d{half_side, half_side, half_side},
  };
  // front face
  mesh->add_face({points[0], points[1], points[2]}, intensity);
  mesh->add_face({points[0], points[3], points[1]}, intensity);
  // back face
  mesh->add_face({points[4], points[5], points[6]}, intensity);
  mesh->add_face({points[4], points[7], points[5]}, intensity);
  // left face
  mesh->add_face({points[0], points[6], points[2]}, intensity);
  mesh->add_face({points[0], points[4], points[6]}, intensity);
  // right face
  mesh->add_face({points[3], points[5], points[1]}, intensity);
  mesh->add_face({points[3], points[7], points[5]}, intensity);
  // bottom face
  mesh->add_face({points[2], points[6], points[1]}, intensity);
  mesh->add_face({points[1], points[6], points[5]}, intensity);
  // top face
  mesh->add_face({points[0], points[4], points[3]}, intensity);
  mesh->add_face({points[3], points[4], points[7]}, intensity);

  return mesh;
}
