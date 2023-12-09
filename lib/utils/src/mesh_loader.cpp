#include "utils/include/mesh_loader.hpp"
#include "array"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/tri_list.hpp"
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <cstddef>
#include <memory>

Utils::MeshLoader::MeshLoader() = default;

Graphite::Object::ObjectIntensity
Utils::MeshLoader::get_obj_intensity_from_material(
    const aiMaterial *material) const {
  aiColor3D color(0.f, 0.f, 0.f);
  material->Get(AI_MATKEY_COLOR_AMBIENT, color);
  auto ka = Graphite::Light::Intensity(color.r, color.g, color.b);

  material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
  auto kd = Graphite::Light::Intensity(color.r, color.g, color.b);

  material->Get(AI_MATKEY_COLOR_SPECULAR, color);
  auto ks = Graphite::Light::Intensity(color.r, color.g, color.b);

  float shineness = 1.0f;
  material->Get(AI_MATKEY_SHININESS, shineness);

  return Graphite::Object::ObjectIntensity(shineness, ka, ks, kd);
};

Algebrick::Point3d
Utils::MeshLoader::get_point3d_from_aiVector3D(const aiVector3D &vector) const {
  // std::cout << vector.x << ',' << vector.y << ',' << vector.z << std::endl;
  return Algebrick::Point3d(vector.x, vector.y, vector.z);
}

Graphite::Object::TriList *
Utils::MeshLoader::load(const std::string &path) const {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(
      path, aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

  if (scene == nullptr)
    return {};

  auto tri_mesh = new Graphite::Object::TriList();

  std::vector<std::shared_ptr<Graphite::Object::ObjectIntensity>> materials;
  for (size_t i = 0; i < scene->mNumMaterials; i++) {
    auto material = std::make_shared<Graphite::Object::ObjectIntensity>(
        get_obj_intensity_from_material(scene->mMaterials[i]));
    materials.push_back(material);
  }

  for (size_t i = 0; i < scene->mNumMeshes; i++) {
    auto mesh = scene->mMeshes[i];
    auto material = materials[mesh->mMaterialIndex];

    for (size_t j = 0; j < mesh->mNumFaces; j++) {
      auto face = mesh->mFaces[j];
      auto v1 = get_point3d_from_aiVector3D(mesh->mVertices[face.mIndices[0]]);
      auto v2 = get_point3d_from_aiVector3D(mesh->mVertices[face.mIndices[1]]);
      auto v3 = get_point3d_from_aiVector3D(mesh->mVertices[face.mIndices[2]]);
      tri_mesh->add_face(std::array{v1, v2, v3}, material);
    }
  }

  return tri_mesh;
}
