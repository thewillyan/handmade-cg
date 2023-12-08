#include "graphite/include/objs/tri_mesh.hpp"
#include <string>

#ifndef MESH_LOADER_HPP
#define MESH_LOADER_HPP

namespace Utils {
class MeshLoader {
public:
  MeshLoader();
  Graphite::Object::TriMesh load(const std::string &path) const;
};
}; // namespace Utils

#endif // !MESH_LOADER_HPP
