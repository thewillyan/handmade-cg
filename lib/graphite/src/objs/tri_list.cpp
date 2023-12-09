#include "graphite/include/objs/tri_list.hpp"
#include "algebrick/include/point3d.hpp"
#include "graphite/include/objs/object.hpp"
#include "graphite/include/objs/triangular_plane.hpp"
#include <cmath>
#include <memory>

using namespace Graphite::Object;

TriList::TriList() {}

void TriList::add_face(std::array<Algebrick::Point3d, 3> ps,
                       std::shared_ptr<ObjectIntensity> i) {
  std::array<std::shared_ptr<Algebrick::Point3d>, 3> p_ptrs = {nullptr, nullptr,
                                                               nullptr};
  for (auto v : vertex_list) {
    for (size_t i = 0; i < 3; ++i) {
      if (ps[i] == *v) {
        p_ptrs[i] = v;
      }
    }
  }

  for (size_t i = 0; i < 3; ++i) {
    if (p_ptrs[i] == nullptr) {
      p_ptrs[i] = std::make_shared<Algebrick::Point3d>(ps[i]);
      vertex_list.emplace_back(p_ptrs[i]);
    }
  }

  auto face = TriangularPlane{p_ptrs, i};
  faces.emplace_back(face);
}

std::optional<RayLenObj> TriList::intersect(const Algebrick::Ray &ray) const {
  double min_len = INFINITY;
  std::optional<RayLenObj> res;
  for (TriangularPlane const &f : faces) {
    auto inter = f.intersect(ray);
    if (inter.has_value() && inter->first < min_len) {
      min_len = inter->first;
      res = std::move(inter);
    }
  }
  return res;
}

std::optional<Algebrick::Vec3d>
TriList::normal(const Algebrick::Point3d &) const {
  return {};
}

// getters
ObjectIntensity TriList::get_intensity(const Algebrick::Point3d &) const {
  return {};
}

// transformations
void TriList::translate(const Algebrick::Vec3d &offset) {
  for (auto &v : vertex_list) {
    *v += offset;
  }
}

void TriList::scale(double k) {
  for (auto &v : vertex_list) {
    *v *= k;
  }
}

void TriList::transform(const Algebrick::Matrix &matrix) {
  Algebrick::Matrix vertex_matrix{4, vertex_list.size()};

  for (size_t i = 0; i < vertex_list.size(); ++i) {
    vertex_matrix.get(0, i) = vertex_list[i]->x;
    vertex_matrix.get(1, i) = vertex_list[i]->y;
    vertex_matrix.get(2, i) = vertex_list[i]->z;
    vertex_matrix.get(3, i) = 1;
  }
  Algebrick::Matrix transf = matrix * vertex_matrix;
  for (size_t i = 0; i < vertex_list.size(); ++i) {
    *vertex_list[i] = {vertex_matrix.get(0, i), vertex_matrix.get(1, i),
                       vertex_matrix.get(2, i)};
  }

  for (TriangularPlane &f : faces) {
    f.transform_norm(matrix);
  }
}
