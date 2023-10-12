#include "../../../lib/algebrick/include/point3d.hpp"
#include "../../../lib/graphite/include/canvas.hpp"
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
  double radius = 1000;
  Algebrick::Point3d center{0, 0, -(canvas_dist + radius)};
  SDL_Color color{255, 0, 0, 255};
  auto red_ball = new Graphite::Sphere(center, radius, color);

  auto objs = Graphite::Space();
  objs.add_obj(red_ball);
  auto scene = Graphite::Scene(&objs);
  scene.render(canvas, 10);

  canvas.draw();
  return 0;
}
