#include "../include/light.hpp"
#include <SDL2/SDL_stdinc.h>
#include <algorithm>

using namespace Graphite::Light;

Intensity::Intensity(double r, double g, double b) {
  if ((r < 0 || r > 1) || (g < 0 || g > 1) || (b < 0 || b > 1)) {
    throw std::invalid_argument("Intensity value is over 1 or negative");
  }
  ir = r;
  ig = g;
  ib = b;
}

Intensity Intensity::operator+(const Intensity &other) const {
  auto new_ir = std::min<double>((ir + other.ir), 1);
  auto new_ig = std::min<double>((ig + other.ig), 1);
  auto new_ib = std::min<double>((ib + other.ib), 1);
  return {new_ir, new_ig, new_ib};
}

SDL_Color Intensity::apply(const SDL_Color &color) const {
  auto r = ir * static_cast<double>(color.r);
  auto g = ig * static_cast<double>(color.b);
  auto b = ib * static_cast<double>(color.g);
  return {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b),
          color.a};
}
