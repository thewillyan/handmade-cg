#include "graphite/include/objs/tri_bsp.hpp"
#include <array>
#include <memory>
#include <optional>
#include <utility>

using namespace Graphite::Object;

// -- node --
TriBspNode::TriBspNode()
    : objs{}, parent{nullptr}, front{nullptr}, back{nullptr}, ray_casted{
                                                                  false} {}
TriBspNode::TriBspNode(const std::shared_ptr<TriBspNode> &parent,
                       const std::shared_ptr<TriBspNode> &front,
                       const std::shared_ptr<TriBspNode> &back)
    : objs{}, parent{parent}, front{front}, back{back}, ray_casted{false} {}

void TriBspNode::add_obj(TriangularPlane &&tri) { objs.emplace_back(tri); }
bool TriBspNode::is_done() const { return ray_casted; }
bool TriBspNode::has_objs() const { return !objs.empty(); }
void TriBspNode::set_undone() { ray_casted = false; }
const std::vector<TriangularPlane> &TriBspNode::get_objs() const {
  return objs;
}
std::shared_ptr<TriBspNode> TriBspNode::get_parent() const { return parent; }
std::shared_ptr<TriBspNode> TriBspNode::get_front() const { return front; }
std::shared_ptr<TriBspNode> TriBspNode::get_back() const { return back; }

std::optional<RayLenObj> TriBspNode::raycast(const Algebrick::Ray &ray) const {
  double min_len = INFINITY;
  std::optional<RayLenObj> res;
  for (const TriangularPlane &t : objs) {
    auto inter = t.intersect(ray);
    if (inter.has_value() && inter->first < min_len) {
      min_len = inter->first;
      res = std::move(inter);
    }
  }
  return res;
}

void TriBspNode::set_parent(const std::shared_ptr<TriBspNode> &node) {
  parent = node;
}
void TriBspNode::set_front(const std::shared_ptr<TriBspNode> &node) {
  front = node;
}
void TriBspNode::set_back(const std::shared_ptr<TriBspNode> &node) {
  back = node;
};

// -- tree --
TriBsp::TriBsp() : root{} {}

std::pair<std::shared_ptr<TriBspNode>, NodeDir>
TriBsp::search(const Algebrick::Vec3d &v) const {
  std::shared_ptr<TriBspNode> curr_node = root;
  if (curr_node == nullptr)
    return std::make_pair(curr_node, OnNode);
  double dot;

  while (curr_node != nullptr) {
    dot = v * (*curr_node->get_objs().front().normal({0, 0, 0}));
    if (dot < 0.0) {
      curr_node = curr_node->get_front();
    } else {
      curr_node = curr_node->get_back();
    }
  }

  NodeDir dir;
  if (dot == 1.0) {
    dir = OnNode;
  } else if (dot < 0.0) {
    dir = OnFront;
  } else {
    dir = OnBack;
  }
  return std::make_pair(curr_node->get_parent(), dir);
}

void TriBsp::add_obj(TriangularPlane &&tri) {
  auto [target_node, dir] = search(*tri.normal({0, 0, 0}));
  switch (dir) {
  case OnNode:
    target_node->add_obj(std::move(tri));
    break;
  case OnFront: {
    auto new_node = TriBspNode{target_node, nullptr, nullptr};
    new_node.add_obj(std::move(tri));
    target_node->set_front(std::make_shared<TriBspNode>(new_node));
    break;
  }
  case OnBack: {
    auto new_node = TriBspNode{target_node, nullptr, nullptr};
    new_node.add_obj(std::move(tri));
    target_node->set_back(std::make_shared<TriBspNode>(new_node));
    break;
  }
  }
}

std::optional<RayLenObj>
TriBsp::raycast_node(const std::shared_ptr<TriBspNode> &node,
                     const Algebrick::Ray &ray) const {
  if (node == nullptr) {
    return raycast_node(node->get_parent(), ray);
  }
  double dot = (ray.source() + ray.direction()) *
               (*node->get_objs().front().normal({0, 0, 0}));
  // default order: viewer is on the front
  std::array<std::shared_ptr<TriBspNode>, 3> raycast_order = {
      node->get_front(), node->get_parent(), node->get_back()};

  // change order if viewer is on the back.
  if (dot >= 0.0) {
    std::swap(raycast_order[0], raycast_order[2]);
  }

  std::optional<RayLenObj> inter{};
  for (size_t i = 0; i < 3 && !inter.has_value(); ++i) {
    if (raycast_order[i]->is_done()) {
      // do nothing
    } else if (i == 1) {
      inter = raycast_order[i]->raycast(ray);
    } else {
      inter = raycast_node(raycast_order[i], ray);
    }
  }
  return inter;
}

std::optional<RayLenObj> TriBsp::raycast(const Algebrick::Ray &ray) const {
  std::shared_ptr<TriBspNode> viewer_node =
      search(ray.source() + ray.direction()).first;
  return raycast_node(viewer_node, ray);
}
