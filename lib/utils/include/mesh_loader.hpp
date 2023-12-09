#include "algebrick/include/point3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/tri_list.hpp"
#include <assimp/material.h>
#include <string>

#ifndef MESH_LOADER_HPP
#define MESH_LOADER_HPP

namespace Utils {
class MeshLoader {
public:
  MeshLoader();

  Graphite::Object::ObjectIntensity
  get_obj_intensity_from_material(const aiMaterial *) const;

  Algebrick::Point3d get_point3d_from_aiVector3D(const aiVector3D &) const;

  Graphite::Object::TriList *load(const std::string &path) const;
};
}; // namespace Utils

#endif // !MESH_LOADER_HPP
