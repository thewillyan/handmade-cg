#include "../include/intensity.hpp"
#include <SDL2/SDL_stdinc.h>
#include <algorithm>
#include <stdexcept>

using namespace Graphite::Light;

// constructor
Intensity::Intensity(double r, double g, double b) {
  if ((r < 0 || r > 1) || (g < 0 || g > 1) || (b < 0 || b > 1)) {
    throw std::invalid_argument("Intensity value is over 1 or negative");
  }
  ir = r;
  ig = g;
  ib = b;
}
Intensity::Intensity(const SDL_Color &color)
    : ir{static_cast<double>(color.r) / 255.0},
      ig{static_cast<double>(color.g) / 255.0},
      ib{static_cast<double>(color.b) / 255.0} {}

// operators
Intensity Intensity::operator+(const Intensity &other) const {
  auto new_ir = std::min<double>((ir + other.ir), 1);
  auto new_ig = std::min<double>((ig + other.ig), 1);
  auto new_ib = std::min<double>((ib + other.ib), 1);
  return {new_ir, new_ig, new_ib};
}
Intensity Intensity::operator*(const Intensity &other) const {
  return {ir * other.ir, ig * other.ig, ib * other.ib};
}
Intensity Intensity::operator*(double k) const {
  auto new_ir = std::clamp<double>((ir * k), 0, 1);
  auto new_ig = std::clamp<double>((ig * k), 0, 1);
  auto new_ib = std::clamp<double>((ib * k), 0, 1);
  return {new_ir, new_ig, new_ib};
}
Intensity Intensity::operator/(double k) const {
  auto new_ir = std::clamp<double>((ir / k), 0, 1);
  auto new_ig = std::clamp<double>((ig / k), 0, 1);
  auto new_ib = std::clamp<double>((ib / k), 0, 1);
  return {new_ir, new_ig, new_ib};
}
Intensity::operator SDL_Color() const {
  return {static_cast<Uint8>(ir * 255), static_cast<Uint8>(ig * 255),
          static_cast<Uint8>(ib * 255), 255};
}
