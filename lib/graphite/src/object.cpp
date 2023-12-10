#include "graphite/include/objs/object.hpp"

Graphite::Object::Object::Object() : visible{true}, id{id_counter++} {};

unsigned long int Graphite::Object::Object::get_id() const { return id; };
bool Graphite::Object::Object::is_visible() const { return visible; };

void Graphite::Object::Object::rotate_x(double angle) {
  Algebrick::Matrix rotation_matrix = {
      {1, 0, 0, 0},
      {0, std::cos(angle), -std::sin(angle), 0},
      {0, std::sin(angle), std::cos(angle), 0},
      {0, 0, 0, 1}};
  transform(rotation_matrix);
}

void Graphite::Object::Object::rotate_y(double angle) {
  Algebrick::Matrix rotation_matrix = {
      {std::cos(angle), 0, std::sin(angle), 0},
      {0, 1, 0, 0},
      {-std::sin(angle), 0, std::cos(angle), 0},
      {0, 0, 0, 1}};
  transform(rotation_matrix);
}

void Graphite::Object::Object::rotate_z(double angle) {
  Algebrick::Matrix rotation_matrix = {
      {std::cos(angle), -std::sin(angle), 0, 0},
      {std::sin(angle), std::cos(angle), 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}};
  transform(rotation_matrix);
}

void Graphite::Object::Object::set_visible(bool v) { visible = v; };

void Graphite::Object::Object::set_container_obj(Object *obj) {
  container_obj = obj;
};

Graphite::Object::Object *Graphite::Object::Object::get_container_obj() const {
  return container_obj;
};
