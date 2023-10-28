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
  double canvas_dist = 5;

  // create ball
  double radius = 900;
  Algebrick::Point3d center{0, 0, -(canvas_dist + radius)};
  SDL_Color color{255, 0, 0, 255};
  auto red_ball = new Graphite::Sphere(center, radius, color);
  red_ball->set_reflection(2);

  // create planes
  SDL_Color plane1_color = {static_cast<Uint8>(0.2 * 255),
                            static_cast<Uint8>(0.7 * 255),
                            static_cast<Uint8>(0.2 * 255), 255};
  Graphite::Plane *plane1 =
      new Graphite::Plane({0, -radius, 0}, {0, 1, 0}, plane1_color, 1);

  Graphite::Plane *plane2 =
      new Graphite::Plane({0, -200, 0}, {0, 0, 1}, plane1_color, 1);

  // create light
  auto light = new Graphite::Light::Point({0, 60, -30}, {0.7, 0.7, 0.7});
  light->set_decay(1e-4, 6e-2, 0.1);

  // create space
  auto objs = Graphite::Space();
  objs.set_ambient_light({0.3, 0.3, 0.3});
  objs.add_obj(red_ball);
  objs.add_obj(plane1);
  objs.add_obj(plane2);
  objs.add_light(light);
  auto scene = Graphite::Scene(&objs);
  scene.set_bg_color({100, 100, 100, 255});

  // render
  scene.render(canvas, 10);
  canvas.draw();
  return 0;
}
