#include "algebrick/include/point3d.hpp"
#include "graphite/include/canvas.hpp"
#include "graphite/include/directed_light.hpp"
#include "graphite/include/intensity.hpp"
#include "graphite/include/objs/object.hpp"
#include "graphite/include/objs/plane.hpp"
#include "graphite/include/scene.hpp"
#include "graphite/include/space.hpp"
#include "graphite/include/spotlight.hpp"
#include <SDL_stdinc.h>
#include <cstddef>

const size_t WIN_WIDTH = 500;
const size_t WIN_HEIGHT = 500;
unsigned long int Graphite::Object::Object::id_counter = 0;

int main() {
  auto canvas = Graphite::Canvas(WIN_WIDTH, WIN_HEIGHT);
  double canvas_dist = 30;

  // create wall
  Graphite::Light::Intensity no_ambient{0, 0, 0};
  Graphite::Light::Intensity wall_k{0.3, 0.3, 0.7};
  SDL_Color wall_color = {0, 0, 0, 255};
  auto *wall = new Graphite::Object::Plane({0, 0, -200}, {0, 0, 1}, wall_color,
                                           1, wall_k, wall_k, no_ambient);

  // create spotlight
  Graphite::Light::Intensity spotlight_k{0.7, 0.7, 0.7};
  Algebrick::Point3d spotlight_p = {-150, -150, -150};
  Algebrick::Vec3d spotlight_direction = {0, 0, -1};
  auto *spotlight = new Graphite::Light::Spot(spotlight_p, spotlight_k,
                                              spotlight_direction, M_PI / 4);

  // create directed light
  Graphite::Light::Intensity directed_k{0.7, 0.7, 0.7};
  Algebrick::Vec3d directed_direction = {0, 0, -1};
  auto *directed =
      new Graphite::Light::Directed(directed_k, directed_direction);
  directed->set_decay(1e-5, 6e-3, 0.5);

  // create space
  auto objs = Graphite::Space();
  objs.add_obj(wall);
  objs.add_light(spotlight);
  objs.add_light(directed);
  auto scene = Graphite::Scene(&objs);
  scene.set_bg_color({255, 255, 255, 255});

  // render
  scene.render(canvas, canvas_dist);
  canvas.draw();
  return 0;
}
