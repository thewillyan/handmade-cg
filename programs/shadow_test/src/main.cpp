#include "../../../lib/algebrick/include/point3d.hpp"
#include "../../../lib/graphite/include/canvas.hpp"
#include "../../../lib/graphite/include/light_point.hpp"
#include "../../../lib/graphite/include/scene.hpp"
#include "../../../lib/graphite/include/space.hpp"
#include "../../../lib/graphite/include/sphere.hpp"
#include <cstddef>

const size_t WIN_WIDTH = 500;
const size_t WIN_HEIGHT = 500;

int main() {
  auto canvas = Graphite::Canvas(WIN_WIDTH, WIN_HEIGHT);
  double canvas_dist = 5;

  // create ball
  double radius = 900;
  Algebrick::Point3d center{0, 0, -(canvas_dist + radius)};
  SDL_Color color{255, 0, 0, 255};
  auto red_ball = new Graphite::Sphere(center, radius, color);
  red_ball->set_reflection(2);

  // create light
  auto light = new Graphite::Light::Point({0, 5, 0}, {0.7, 0.7, 0.7});
  light->set_decay(0, 0.02, 0.1);

  // create space
  auto objs = Graphite::Space();
  objs.add_obj(red_ball);
  objs.add_light(light);
  auto scene = Graphite::Scene(&objs);
  scene.set_bg_color({100, 100, 100, 255});
  scene.set_ambient_light({0.9, 0.9, 0.9});

  // render
  scene.render(canvas, 10);
  canvas.draw();
  return 0;
}
