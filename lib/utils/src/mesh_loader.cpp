#include "utils/include/mesh_loader.hpp"
#include "graphite/include/objs/tri_mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

Utils::MeshLoader::MeshLoader() = default;

Graphite::Object::TriMesh
Utils::MeshLoader::load(const std::string &path) const {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(
      path, aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

  if (scene == nullptr)
    return {};
  printf("number of meshes: %d\n", scene->mNumMeshes);

  return {};
}
