#include "graphite/include/canvas.hpp"
#include "graphite/include/objs/object.hpp"
#include "graphite/include/scene.hpp"
#include "graphite/include/space.hpp"
#include "lights.cpp"
#include "objects.cpp"
#include "room.cpp"
#include "utils/include/mesh_loader.hpp"
#include <cstddef>

const size_t WIN_WIDTH = 500;
const size_t WIN_HEIGHT = 500;
unsigned long int Graphite::Object::Object::id_counter = 0;

int main() {
  auto canvas = Graphite::Canvas(WIN_WIDTH, WIN_HEIGHT);
  double canvas_dist = 5;

  auto objs = Graphite::Space();

  auto room = get_room();
  for (auto obj : room) {
    objs.add_obj(obj);
  }

  auto objects = get_objects();
  for (auto obj : objects) {
    objs.add_obj(obj);
  }

  objs.set_ambient_light({0.5, 0.5, 0.5});
  auto lights = get_lights();
  for (auto light : lights) {
    objs.add_light(light);
  }

  auto scene = Graphite::Scene(&objs);
  scene.set_bg_color({255, 255, 255, 255});
  scene.set_eye_pov({{0, 0, 0}, {0, 100, 10}, {0, 0, 100}});
  canvas.zoom_in(1.5);

  scene.render(canvas, canvas_dist);
  canvas.draw();
  return 0;
}
