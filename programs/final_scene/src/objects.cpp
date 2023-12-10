#include "algebrick/include/point3d.hpp"
#include "graphite/include/objs/cilinder.hpp"
#include "graphite/include/objs/cone.hpp"
#include "graphite/include/objs/object.hpp"
#include "graphite/include/objs/sphere.hpp"

void get_santa_tree(std::vector<Graphite::Object::Object *> *objects) {
  double z_distance = 180;
  double x_distance = 120;
  double radius = 10;
  Algebrick::Point3d center{x_distance, 0, z_distance};
  SDL_Color color{0, 0, 0, 255};
  Graphite::Light::Intensity ball_k{1, 0.749, 0};
  auto orange_ball = new Graphite::Object::Sphere(center, radius, color, ball_k,
                                                  ball_k, ball_k);
  orange_ball->set_reflection(10);
  objects->push_back(orange_ball);

  double cone_radius = 60;
  double cone_height = 150;
  Graphite::Light::Intensity cone_k{0.451, 0.627, 0.149};
  Algebrick::Point3d cone_center = {x_distance, -150, z_distance};
  Algebrick::Vec3d cone_dir = {0, 1, 0};
  double shininess = 10;
  auto *cone =
      new Graphite::Object::Cone(cone_height, cone_radius, cone_center,
                                 cone_dir, shininess, cone_k, cone_k, cone_k);
  objects->push_back(cone);

  double cylinder_radius = 10;
  double cylinder_height = 50;
  Graphite::Light::Intensity cylinder_k{0.604, 0.388, 0.329};
  Algebrick::Point3d cylinder_center = {x_distance, -200, z_distance};
  Algebrick::Vec3d cylinder_dir = {0, 1, 0};
  auto cylinder = new Graphite::Object::Cilinder(
      cylinder_center, cylinder_dir, cylinder_radius, cylinder_height,
      shininess, cylinder_k, cylinder_k, cylinder_k);
  objects->push_back(cylinder);
}

void add_pub_chair(const Algebrick::Point3d &pos,
                   std::vector<Graphite::Object::Object *> *objects) {
  double seat_radius = 30;
  double seat_height = 10;
  double seat_y = -100;
  Graphite::Light::Intensity seat_k{0.212, 0.176, 0.176};
  Algebrick::Point3d seat_center = {pos.x, seat_y, pos.z};
  Algebrick::Vec3d seat_dir = {0, 1, 0};
  double shininess = 10;
  auto seat = new Graphite::Object::Cilinder(seat_center, seat_dir, seat_radius,
                                             seat_height, shininess, seat_k,
                                             seat_k, seat_k);
  objects->push_back(seat);

  double support_radius = 5;
  double support_height = 100;
  Graphite::Light::Intensity support_k{0.82, 0.82, 0.82};
  Algebrick::Point3d support_center = {pos.x, seat_y - 100, pos.z};
  auto support = new Graphite::Object::Cilinder(
      support_center, seat_dir, support_radius, support_height, shininess,
      support_k, support_k, support_k);
  objects->push_back(support);
}

std::vector<Graphite::Object::Object *> get_objects() {

  std::vector<Graphite::Object::Object *> objects;
  get_santa_tree(&objects);
  add_pub_chair({-100, 0, 100}, &objects);
  add_pub_chair({-100, 0, 170}, &objects);
  add_pub_chair({-100, 0, 30}, &objects);
  return objects;
}
