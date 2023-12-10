#ifndef Graphite_Object_TriBsp
#define Graphite_Object_TriBsp

#include "algebrick/include/ray.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/objs/object.hpp"
#include "graphite/include/objs/triangular_plane.hpp"
#include <memory>
#include <optional>
#include <vector>

namespace Graphite::Object {

enum NodeDir { OnNode, OnFront, OnBack };

class TriBspNode {
private:
  std::vector<TriangularPlane> objs;
  std::shared_ptr<TriBspNode> parent;
  std::shared_ptr<TriBspNode> front;
  std::shared_ptr<TriBspNode> back;
  bool ray_casted;

public:
  TriBspNode();
  TriBspNode(const std::shared_ptr<TriBspNode> &parent,
             const std::shared_ptr<TriBspNode> &front,
             const std::shared_ptr<TriBspNode> &back);

  void add_obj(TriangularPlane &&tri);
  std::optional<RayLenObj> raycast(const Algebrick::Ray &ray) const;
  bool is_done() const;
  bool has_objs() const;
  void set_undone();

  // getters
  const std::vector<TriangularPlane> &get_objs() const;
  std::shared_ptr<TriBspNode> get_parent() const;
  std::shared_ptr<TriBspNode> get_front() const;
  std::shared_ptr<TriBspNode> get_back() const;

  // setters
  void set_parent(const std::shared_ptr<TriBspNode> &node);
  void set_front(const std::shared_ptr<TriBspNode> &node);
  void set_back(const std::shared_ptr<TriBspNode> &node);
};

class TriBsp {
private:
  std::shared_ptr<TriBspNode> root;

  std::optional<RayLenObj> raycast_node(const std::shared_ptr<TriBspNode> &node,
                                        const Algebrick::Ray &ray) const;

public:
  TriBsp();

  void add_obj(TriangularPlane &&tri);
  std::pair<std::shared_ptr<TriBspNode>, NodeDir>
  search(const Algebrick::Vec3d &v) const;
  std::optional<RayLenObj> raycast(const Algebrick::Ray &ray) const;
};

} // namespace Graphite::Object

#endif // !Graphite_Object_TriBsp
