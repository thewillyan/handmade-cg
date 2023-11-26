#ifndef Graphite_PolygonMesh
#define Graphite_PolygonMesh

#include "algebrick/include/point3d.hpp"
#include <vector>

namespace Graphite::Mesh {

class Vertex {
private:
  Algebrick::Point3d point;
  class Edge *edge;

public:
  Vertex(Algebrick::Point3d point);
  Vertex(Algebrick::Point3d point, Edge *edge);

  Algebrick::Point3d &get_point();
  Edge *get_edge();

  void set_edge(Edge *e);
};

class Edge {
private:
  Vertex *origin;
  class Face *face;
  Edge *next;
  Edge *twin;

public:
  // Creates an edge with the given origin.
  Edge(Vertex &o);

  // Creates an edge e1: v1 -> v2 and an edge e2: v2 -> v1 where e1 and
  // e2 are twins.
  static std::pair<Edge *, Edge *> edge_pair(Vertex &v1, Vertex &v2);

  Vertex *destination();
  Edge *leaving_edge();

  // sets edge face.
  void set_face(Face *f);
  // sets next edge.
  void set_next(Edge *n);
  // sets edge twin.
  void set_twin(Edge *t);
};

class Face {
private:
  Edge *head;

public:
  // creates an "null" face.
  Face();
  // creates an face with the given edge as its head.
  Face(Edge &e);
};

class PolygonMesh {
private:
  std::vector<Vertex *> vertices;
  std::vector<Face *> faces;

public:
  PolygonMesh();

  // A face can constructed by a arbitrary number of points, but
  // as the only repersentation that we have is the `TriangularPlane`
  // only three can be used without preprocess the faces vector.
  void add_face(Algebrick::Point3d points[3]);

  // TODO:
  //  - transform into multiple TriangularPlane's?
  //  - if is necessary to locate a specific `*Vertex` by a `Point3d`
  //    replace `std::vector` by a `std::set` in `vercices`. It's rbtree
  //    implementation should turn this more fast and erghonomic. (rembember
  //    to implement an O(1) hash using bit shift)
};
} // namespace Graphite::Mesh
#endif // !Graphite_PolygonMesh
