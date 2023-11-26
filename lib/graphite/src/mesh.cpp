#include "graphite/include/mesh.hpp"
#include "algebrick/include/point3d.hpp"
#include <utility>

using namespace Graphite::Mesh;

Vertex::Vertex(Algebrick::Point3d p) : point{p}, edge{nullptr} {}
Vertex::Vertex(Algebrick::Point3d p, Edge *e) : point{p}, edge{e} {}

Algebrick::Point3d &Vertex::get_point() { return point; }
Edge *Vertex::get_edge() { return edge; }

void Vertex::set_edge(Edge *e) {
  delete edge;
  edge = e;
}

Edge::Edge(Vertex &o)
    : origin{&o}, face{new Face()}, next{nullptr}, twin{nullptr} {}

std::pair<Edge *, Edge *> Edge::edge_pair(Vertex &v1, Vertex &v2) {
  Edge *e1 = new Edge(v1);
  Edge *e2 = new Edge(v2);
  e1->set_twin(e2);
  e2->set_twin(e1);
  return std::make_pair(e1, e2);
}

Vertex *Edge::destination() {
  if (twin == nullptr) {
    return nullptr;
  }
  return twin->origin;
}
Edge *Edge::leaving_edge() {
  if (twin == nullptr) {
    return nullptr;
  }
  return twin->next;
}

void Edge::set_face(Face *f) { face = f; }
void Edge::set_next(Edge *n) { next = n; }
void Edge::set_twin(Edge *t) { twin = t; }

Face::Face() : head{nullptr} {}
Face::Face(Edge &e) : head{&e} {}

PolygonMesh::PolygonMesh() {}

void PolygonMesh::add_face(Algebrick::Point3d points[3]) {
  // v0
  // | \
  // |f \
  // v1-v2
  Vertex *v0 = new Vertex(points[0]);
  Vertex *v1 = new Vertex(points[1]);
  Vertex *v2 = new Vertex(points[2]);

  // v0 -> v1
  Edge *e0 = Edge::edge_pair(*v0, *v1).first;
  // v1 -> v2
  Edge *e1 = Edge::edge_pair(*v1, *v2).first;
  // v2 -> v0
  Edge *e2 = Edge::edge_pair(*v2, *v0).first;

  Face *f = new Face(*e0);
  e0->set_face(f);
  e1->set_face(f);
  e2->set_face(f);

  vertices.emplace_back(v0);
  vertices.emplace_back(v1);
  vertices.emplace_back(v2);
  faces.emplace_back(f);
};
