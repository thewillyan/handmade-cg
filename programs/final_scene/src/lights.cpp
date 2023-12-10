#include "graphite/include/light.hpp"
#include "graphite/include/light_point.hpp"
#include <vector>

std::vector<Graphite::Light::Source *> get_lights() {

  auto upper = new Graphite::Light::Point({0, 190, 100}, {0.7, 0.7, 0.7});
  upper->set_decay(1e-5, 6e-3, 0.1);

  std::vector<Graphite::Light::Source *> lights = {upper};
  return lights;
}
