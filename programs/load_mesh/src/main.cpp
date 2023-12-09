#include "algebrick/include/point3d.hpp"
#include "graphite/include/canvas.hpp"
#include "graphite/include/light_point.hpp"
#include "graphite/include/objs/object.hpp"
#include "graphite/include/objs/sphere.hpp"
#include "graphite/include/scene.hpp"
#include "graphite/include/space.hpp"
#include "utils/include/mesh_loader.hpp"
#include <cstddef>
#include <filesystem>
#include <iostream>

const size_t WIN_WIDTH = 500;
const size_t WIN_HEIGHT = 500;
unsigned long int Graphite::Object::Object::id_counter = 0;

int main() {
  auto canvas = Graphite::Canvas(WIN_WIDTH, WIN_HEIGHT);
  double canvas_dist = 5;

  auto mesh_loader = Utils::MeshLoader();
  auto mesh = mesh_loader.load("../models/table/table.obj");
  mesh->rotate_x(-M_PI / 2.0);

  std::cout << std::filesystem::current_path() << std::endl;
  // create light
  auto light = new Graphite::Light::Point({0, 5, 0}, {0.7, 0.7, 0.7});
  light->set_decay(1e-4, 6e-2, 0.1);
  double radius = 40;
  Algebrick::Point3d center{0, 0, -100};
  SDL_Color color{0, 0, 0, 255};
  Graphite::Light::Intensity ball_k{0.7, 0.2, 0.2};
  auto red_ball = new Graphite::Object::Sphere(center, radius, color, ball_k,
                                               ball_k, ball_k);

  // create space
  auto objs = Graphite::Space();
  objs.set_ambient_light({0.5, 0.5, 0.5});
  objs.add_obj(red_ball);
  objs.add_light(light);
  objs.add_obj(mesh);
  auto scene = Graphite::Scene(&objs);
  scene.set_eye_pov(Graphite::FrameRef{{0, 0, 100}, {0, 200, 100}, {0, 0, 0}});
  scene.set_bg_color({255, 255, 255, 255});

  // // render
  scene.render(canvas, canvas_dist);
  canvas.zoom_out(100);
  canvas.draw();
  return 0;
}
