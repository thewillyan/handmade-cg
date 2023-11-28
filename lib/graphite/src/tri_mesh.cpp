#include "graphite/include/tri_mesh.hpp"
#include "algebrick/include/point3d.hpp"
#include "graphite/include/triangular_plane.hpp"
#include <utility>

using namespace Graphite::Mesh;

Vertex::Vertex(Algebrick::Point3d p) : point{p}, edge{nullptr} {}
Vertex::Vertex(Algebrick::Point3d p, HalfEdge *e) : point{p}, edge{e} {}

Algebrick::Point3d &Vertex::get_point() { return point; }
HalfEdge *Vertex::get_edge() { return edge; }

void Vertex::set_edge(HalfEdge *e) {
  delete edge;
  edge = e;
}

HalfEdge::HalfEdge(Vertex &o)
    : origin{&o}, face{new Face()}, next{nullptr}, twin{nullptr} {}

std::pair<HalfEdge *, HalfEdge *> HalfEdge::edge_pair(Vertex &v1, Vertex &v2) {
  HalfEdge *e1 = new HalfEdge(v1);
  HalfEdge *e2 = new HalfEdge(v2);
  e1->set_twin(e2);
  e2->set_twin(e1);
  return std::make_pair(e1, e2);
}

Vertex *HalfEdge::destination() {
  // must always have a twin (for the keep the datastructure safe)
  return twin->origin;
}
HalfEdge *HalfEdge::leaving_edge() {
  // must always have a twin (for the keep the datastructure safe)
  return twin->next;
}
Vertex *HalfEdge::get_origin() { return origin; }
Face *HalfEdge::get_face() { return face; }
HalfEdge *HalfEdge::get_next() { return next; }
HalfEdge *HalfEdge::get_twin() { return twin; }

void HalfEdge::set_face(Face *f) { face = f; }
void HalfEdge::set_next(HalfEdge *n) { next = n; }
void HalfEdge::set_twin(HalfEdge *t) { twin = t; }

Face::Face() : head{nullptr} {}
Face::Face(HalfEdge &e) : head{&e} {}
HalfEdge *Face::get_edge() { return head; }

TriMesh::TriMesh() {}

void TriMesh::add_face(Algebrick::Point3d points[3]) {
  // v0
  // | \
  // |f \
  // v1-v2
  Vertex *vers[3] = {nullptr, nullptr, nullptr};
  // verify which vertices are already in the mesh.
  for (Vertex *v : vertices) {
    const Algebrick::Point3d &p = v->get_point();
    if (points[0] == p) {
      vers[0] = v;
    } else if (points[1] == p) {
      vers[1] = v;
    } else if (points[2] == p) {
      vers[2] = v;
    }
  }
  // allocate new vertices.
  for (size_t i = 0; i < 3; ++i) {
    if (vers[i] == nullptr) {
      vers[i] = new Vertex(points[i]);
      vertices.emplace_back(vers[i]);
    }
  }

  // build edges
  HalfEdge *edges[3];
  for (size_t i = 0; i < 3; ++i) {
    // verify if the edge has already be allocated as a twin.
    //
    // this happens if, and only if, exists a vertex in the current insertion
    // such that it's source of an edge which the destination is also part of
    // the current insertion.
    HalfEdge *e = vers[i]->get_edge();
    HalfEdge *twin = nullptr;
    if (e != nullptr) {
      Vertex *v = e->destination();
      for (size_t j = 0; j < 3; ++j) {
        if (vers[i] == v) {
          twin = e->get_twin();
          break;
        }
      }
    }

    if (twin != nullptr) {
      edges[i] = twin;
    } else {
      // allocate new edge pair.
      edges[i] = HalfEdge::edge_pair(*vers[i], *vers[(i + 1) % 3]).first;
    }
  }
  // bind next edge to all edges.
  edges[0]->set_next(edges[1]);
  edges[1]->set_next(edges[2]);
  edges[2]->set_next(edges[0]);

  // bind vertices to edges
  for (size_t i = 0; i < 3; ++i) {
    vers[i]->set_edge(edges[i]);
  }
  // bind face to the edges
  Face *f = new Face(*edges[0]);
  for (HalfEdge *edge : edges) {
    edge->set_face(f);
  }
  faces.emplace_back(f);
};

std::vector<Graphite::TriangularPlane>
TriMesh::face_planes(double shiness, Light::Intensity env,
                     Light::Intensity espec, Light::Intensity diff) {
  std::vector<Graphite::TriangularPlane> planes;
  planes.reserve(faces.size());
  Algebrick::Point3d pbuff[3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  size_t curr_point;
  for (Face *f : faces) {
    HalfEdge *e = f->get_edge();
    curr_point = 0;
    do {
      pbuff[curr_point++] = e->get_origin()->get_point();
      e = e->get_next();
    } while (e->get_next() != f->get_edge());
    planes.push_back(Graphite::TriangularPlane{pbuff[0], pbuff[1], pbuff[2],
                                               shiness, env, espec, diff});
  }
  return planes;
}
