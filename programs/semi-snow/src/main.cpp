#include "algebrick/include/point3d.hpp"
#include "graphite/include/canvas.hpp"
#include "graphite/include/cilinder.hpp"
#include "graphite/include/cone.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/light_point.hpp"
#include "graphite/include/plane.hpp"
#include "graphite/include/scene.hpp"
#include "graphite/include/space.hpp"
#include "graphite/include/sphere.hpp"
#include "graphite/include/triangular_plane.hpp"
#include <cmath>
#include <cstddef>

const size_t WIN_WIDTH = 500;
const size_t WIN_HEIGHT = 500;
unsigned long int Graphite::Object::id_counter = 0;

int main() {
  auto canvas = Graphite::Canvas(WIN_WIDTH, WIN_HEIGHT);
  double canvas_dist = 30;

  // create ball
  double radius = 40;
  Algebrick::Point3d sphere_center{0, 0, -100};
  SDL_Color color{0, 0, 0, 255};
  Graphite::Light::Intensity ball_k{0.7, 0.2, 0.2};
  auto red_ball = new Graphite::Sphere(sphere_center, radius, color, ball_k,
                                       ball_k, ball_k);
  red_ball->set_reflection(10);

  // create cilinder
  Graphite::Light::Intensity cilinder_k{0.2, 0.3, 0.8};
  Algebrick::Vec3d cylinder_dir{0, 1, 0};
  double cylinder_height = 3 * radius;
  double cylinder_radius = radius / 3;
  auto cilinder = new Graphite::Cilinder(sphere_center, cylinder_dir,
                                         cylinder_radius, cylinder_height, 10,
                                         cilinder_k, cilinder_k, cilinder_k);
  cilinder->translate({0, -30, 0});

  Graphite::Light::Intensity no_ambient{0, 0, 0};
  // create planes
  Graphite::Light::Intensity floor_k{0.2, 0.7, 0.2};
  SDL_Color floor_color = {0, 0, 0, 255};
  Graphite::Plane *floor = new Graphite::Plane(
      {0, -radius, 0}, {0, 1, 0}, floor_color, 1, floor_k, floor_k, no_ambient);

  Graphite::Light::Intensity wall_k{0.3, 0.3, 0.7};
  SDL_Color wall_color = {0, 0, 0, 255};
  Graphite::Plane *wall = new Graphite::Plane(
      {0, 0, -200}, {0, 0, 1}, wall_color, 1, wall_k, wall_k, no_ambient);

  Graphite::TriangularPlane *tp = new Graphite::TriangularPlane(
      {-20, 5, -100}, {20, 5, -100}, {0, 35, -100}, 10, ball_k, ball_k, ball_k);
  tp->translate({0, 0, 50});

  // create light
  auto light = new Graphite::Light::Point({0, 60, -30}, {0.7, 0.7, 0.7});
  light->set_decay(1e-5, 6e-3, 0.1);

  // create space
  auto objs = Graphite::Space();
  objs.set_ambient_light({0.3, 0.3, 0.3});
  // objs.add_obj(red_ball);
  objs.add_obj(cilinder);
  objs.add_obj(tp);
  objs.add_obj(floor);
  objs.add_obj(wall);
  objs.add_light(light);
  auto scene = Graphite::Scene(&objs);
  scene.set_bg_color({255, 255, 255, 255});

  // render
  scene.render(canvas, canvas_dist);
  canvas.draw();
  return 0;
}
