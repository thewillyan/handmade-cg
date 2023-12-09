#include "SDL_image.h"
#include "algebrick/include/point3d.hpp"
#include "algebrick/include/vec3d.hpp"
#include "graphite/include/objs/object.hpp"
#include "graphite/include/objs/plane.hpp"
#include "graphite/include/texture.hpp"
#include <vector>

Graphite::Object::Plane *get_floor() {
  Graphite::Light::Intensity no_ambient{0, 0, 0};
  auto *floor =
      new Graphite::Object::Plane({0, -200, 0}, {0, 1, 0}, no_ambient, 1,
                                  no_ambient, no_ambient, no_ambient);
  return floor;
}

Graphite::Object::Plane *get_wall(const Algebrick::Point3d &p,
                                  const Algebrick::Vec3d &n) {
  Graphite::Light::Intensity no_ambient{0, 0, 0};
  auto *floor = new Graphite::Object::Plane(p, n, no_ambient, 1, no_ambient,
                                            no_ambient, no_ambient);
  return floor;
}

std::vector<Graphite::Object::Object *> get_room() {

  SDL_Surface *wood_image = IMG_Load("../textures/oak_floor.jpg");
  auto *wood_texture = new Graphite::Texture(wood_image);

  SDL_Surface *brick_image = IMG_Load("../textures/dragfaced_brick.jpg");
  auto *brick_texture = new Graphite::Texture(brick_image);

  auto floor = get_floor();
  floor->set_texture(wood_texture);

  auto left_wall = get_wall({-200, 0, 0}, {-1, 0, 0});
  left_wall->set_texture(brick_texture);

  auto right_wall = get_wall({200, 0, 0}, {1, 0, 0});
  right_wall->set_texture(brick_texture);

  auto back_wall = get_wall({0, 0, -200}, {0, 0, 1});
  back_wall->set_texture(brick_texture);

  auto front_wall = get_wall({0, 0, 200}, {0, 0, -1});
  front_wall->set_texture(brick_texture);

  auto ceiling = get_wall({0, 200, 200}, {0, -1, 0});
  ceiling->set_texture(wood_texture);

  std::vector<Graphite::Object::Object *> objs = {
      floor, left_wall, right_wall, back_wall, front_wall, ceiling};
  return objs;
}
