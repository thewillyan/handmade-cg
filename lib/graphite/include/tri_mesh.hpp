#ifndef Graphite_TriMesh
#define Graphite_TriMesh

#include "algebrick/include/point3d.hpp"
#include <vector>

namespace Graphite::Mesh {

class Vertex {
private:
  Algebrick::Point3d point;
  class HalfEdge *edge;

public:
  Vertex(Algebrick::Point3d point);
  Vertex(Algebrick::Point3d point, HalfEdge *edge);

  Algebrick::Point3d &get_point();
  const Algebrick::Point3d &get_point() const;
  HalfEdge *get_edge();

  void set_edge(HalfEdge *e);
};

class HalfEdge {
private:
  Vertex *origin;
  class Face *face;
  HalfEdge *next;
  HalfEdge *twin;

public:
  // Creates an edge with the given origin.
  HalfEdge(Vertex &o);

  // Creates an edge e1: v1 -> v2 and an edge e2: v2 -> v1 where e1 and
  // e2 are twins. Returns [e1, e2].
  static std::pair<HalfEdge *, HalfEdge *> edge_pair(Vertex &v1, Vertex &v2);

  Vertex *destination();
  HalfEdge *leaving_edge();

  // gets edge face.
  Face *get_face();
  // gets next edge.
  HalfEdge *get_next();
  // gets edge twin.
  HalfEdge *get_twin();

  // sets edge face.
  void set_face(Face *f);
  // sets next edge.
  void set_next(HalfEdge *n);
  // sets edge twin.
  void set_twin(HalfEdge *t);
};

class Face {
private:
  HalfEdge *head;

public:
  // creates an "null" face.
  Face();
  // creates an face with the given edge as its head.
  Face(HalfEdge &e);
};

class TriMesh {
private:
  // list of vertices in the mesh.
  std::vector<Vertex *> vertices;
  // In this datastructure a face can be constructed by a arbitrary number of
  // points, however the only repersentation that we have is the
  // `TriangularPlane` so only three points faces can be used without
  // pre-process the faces vector.
  std::vector<Face *> faces;

public:
  TriMesh();

  // Creates a new triangular face with the given points.
  //
  // The points should be passed only in counterclockwise or clockwise, but
  // never both in the same populated datastructure.
  void add_face(Algebrick::Point3d points[3]);

  // TODO:
  //  - transform into multiple TriangularPlane's?
};
} // namespace Graphite::Mesh
#endif // !Graphite_TriMesh