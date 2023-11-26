#include "algebrick/include/point3d.hpp"
#include "graphite/include/canvas.hpp"
#include "graphite/include/light_point.hpp"
#include "graphite/include/plane.hpp"
#include "graphite/include/scene.hpp"
#include "graphite/include/space.hpp"
#include "graphite/include/sphere.hpp"
#include <SDL_stdinc.h>
#include <cstddef>

const size_t WIN_WIDTH = 500;
const size_t WIN_HEIGHT = 500;
unsigned long int Graphite::Object::id_counter = 0;

int main() {
  auto canvas = Graphite::Canvas(WIN_WIDTH, WIN_HEIGHT);
  double canvas_dist = 30;

  // create ball
  double radius = 40;
  Algebrick::Point3d center{0, 0, -100};
  SDL_Color color{0, 0, 0, 255};
  Graphite::Light::Intensity ball_k{0.7, 0.2, 0.2};
  auto red_ball =
      new Graphite::Sphere(center, radius, color, ball_k, ball_k, ball_k);
  red_ball->set_reflection(10);
  // red_ball->translate({100, 0, 0});

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

  // create light
  auto light = new Graphite::Light::Point({0, 60, -30}, {0.7, 0.7, 0.7});
  light->set_decay(1e-5, 6e-3, 0.1);

  // create space
  Graphite::Space objs = {floor, wall, red_ball};
  objs.set_ambient_light({0.3, 0.3, 0.3});
  objs.add_light(light);
  auto scene = Graphite::Scene(&objs);
  scene.set_bg_color({255, 255, 255, 255});
  scene.set_eye_pov({{50, 80, 0}, {50, 100, -2}, center});

  // render
  scene.render(canvas, canvas_dist);
  canvas.draw();
  return 0;
}
