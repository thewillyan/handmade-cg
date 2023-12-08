#ifndef Graphite_TriMesh
#define Graphite_TriMesh

#include "algebrick/include/point3d.hpp"
#include "graphite/include/objs/obj_intensity.hpp"
#include "graphite/include/objs/object.hpp"
#include "graphite/include/objs/triangular_plane.hpp"
#include <algorithm>
#include <array>
#include <memory>
#include <vector>

namespace Graphite::Object {

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

  // gets edge origin vertex.
  Vertex *get_origin();
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
  std::shared_ptr<ObjectIntensity> intensity;

public:
  // creates an "null" face.
  Face();
  // creates an face with the given edge as its head.
  explicit Face(HalfEdge &e, std::shared_ptr<ObjectIntensity> intensity);

  // gets the head edge
  HalfEdge *get_edge();
  std::shared_ptr<ObjectIntensity> get_intensity() const;
};

class TriMesh : public Object {
private:
  // list of vertices in the mesh.
  std::vector<Vertex *> vertices;
  // In this datastructure a face can be constructed by a arbitrary number of
  // points, however the only repersentation that we have is the
  // `TriangularPlane` so only three points faces can be used without
  // pre-process the faces vector.
  std::vector<Face *> faces;
  ObjectIntensity default_intensity;

public:
  TriMesh();
  TriMesh(double shiness, Light::Intensity dif, Light::Intensity spec,
          Light::Intensity env);

  // Creates a new triangular face with the given points.
  //
  // The points should be passed only in counterclockwise or clockwise, but
  // never both in the same populated datastructure.
  void add_face(std::array<Algebrick::Point3d, 3>,
                std::shared_ptr<ObjectIntensity> intensity);

  // Get each face plane as a `TriangularPlane`.
  std::vector<TriangularPlane> face_planes(double shiness, Light::Intensity env,
                                           Light::Intensity espec,
                                           Light::Intensity diff);

  std::optional<RayLenObj> intersect(const Algebrick::Ray &ray) const override;
  std::optional<Algebrick::Vec3d>
  normal(const Algebrick::Point3d &p) const override;

  // getters
  ObjectIntensity get_intensity(const Algebrick::Point3d &) const override;

  // transformations
  void translate(const Algebrick::Vec3d &offset) override;
  void scale(double k) override;
  void transform(const Algebrick::Matrix &matrix) override;
};
} // namespace Graphite::Object
#endif // !Graphite_TriMesh
