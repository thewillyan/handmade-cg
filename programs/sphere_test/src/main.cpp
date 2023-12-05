#include "algebrick/include/point3d.hpp"
#include "graphite/include/canvas.hpp"
#include "graphite/include/objs/sphere.hpp"
#include "graphite/include/scene.hpp"
#include "graphite/include/space.hpp"
#include <cstddef>

const size_t WIN_WIDTH = 500;
const size_t WIN_HEIGHT = 500;
unsigned long int Graphite::Object::Object::id_counter = 0;

int main() {
  auto canvas = Graphite::Canvas(WIN_WIDTH, WIN_HEIGHT);
  double canvas_dist = 5;

  // create ball
  double radius = 1000;
  Algebrick::Point3d center{0, 0, -(canvas_dist + radius)};
  SDL_Color color{255, 0, 0, 255};
  auto red_ball = new Graphite::Object::Sphere(center, radius, color);

  auto objs = Graphite::Space();
  objs.add_obj(red_ball);
  auto scene = Graphite::Scene(&objs);
  scene.set_bg_color({100, 100, 100, 255});
  scene.render(canvas, 10);

  canvas.draw();
  return 0;
}
