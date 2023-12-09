#include "graphite/include/objs/cilinder.hpp"
#include "graphite/include/objs/cone.hpp"
#include "graphite/include/objs/object.hpp"
#include "graphite/include/objs/sphere.hpp"

Graphite::Object::Sphere *get_sphere() {
  double radius = 40;
  Algebrick::Point3d center{0, 0, -100};
  SDL_Color color{0, 0, 0, 255};
  Graphite::Light::Intensity ball_k{0.7, 0.2, 0.2};
  auto red_ball = new Graphite::Object::Sphere(center, radius, color, ball_k,
                                               ball_k, ball_k);
  red_ball->set_reflection(10);

  return red_ball;
}

Graphite::Object::Cone *get_cone() {
  double cone_radius = 40;
  double cone_height = 100;
  Graphite::Light::Intensity cone_k{0.8, 0.3, 0.2};
  Algebrick::Point3d cone_center = {100, 0, -100};
  Algebrick::Vec3d cone_dir = {0, 1, 0};
  double shininess = 10;

  auto *cone =
      new Graphite::Object::Cone(cone_height, cone_radius, cone_center,
                                 cone_dir, shininess, cone_k, cone_k, cone_k);

  return cone;
}

Graphite::Object::Cilinder *get_cylinder() {
  double cylinder_radius = 40;
  double cylinder_height = 100;
  Graphite::Light::Intensity cylinder_k{0.3, 0.3, 0.7};
  Algebrick::Point3d cylinder_center = {-100, -100, -100};
  Algebrick::Vec3d cylinder_dir = {0, 1, 0};
  double shininess = 10;

  auto cylinder = new Graphite::Object::Cilinder(
      cylinder_center, cylinder_dir, cylinder_radius, cylinder_height,
      shininess, cylinder_k, cylinder_k, cylinder_k);

  return cylinder;
}

std::vector<Graphite::Object::Object *> get_objects() {
  auto sphere = get_sphere();
  auto cone = get_cone();
  auto cylinder = get_cylinder();

  std::vector<Graphite::Object::Object *> objects = {sphere, cone, cylinder};
  return objects;
}
