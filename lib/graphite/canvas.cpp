#include "canvas.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstddef>

using namespace Graphite;

int cmpColors::hashColor(const SDL_Color &color) {
  return static_cast<int>(color.r) << (3 * 8) |
         static_cast<int>(color.g) << (2 * 8) |
         static_cast<int>(color.b) << (1 * 8) | static_cast<int>(color.a);
}

bool cmpColors::operator()(const SDL_Color &a, const SDL_Color &b) {
  return hashColor(a) < hashColor(b);
}

// Canvas definitions
Canvas::Canvas(size_t w, size_t h, SDL_Color color)
    : width{w}, height{h}, default_color{color},
      color_map{std::map<SDL_Color, std::vector<SDL_Point>, cmpColors>()},
      window{nullptr}, renderer{nullptr} {
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}
Canvas::Canvas(size_t w, size_t h)
    : width{w}, height{h}, default_color{0, 0, 0, 255},
      color_map{std::map<SDL_Color, std::vector<SDL_Point>, cmpColors>()},
      window{nullptr}, renderer{nullptr} {
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
};
Canvas::~Canvas() { SDL_Quit(); }

size_t Canvas::get_width() const { return width; }
size_t Canvas::get_height() const { return height; }

void Canvas::set_pixel(SDL_Point point, SDL_Color color) {
  color_map[color].push_back(point);
}
void Canvas::fill(SDL_Color c) {
  default_color = c;
  this->clear();
}
void Canvas::clear() { color_map.clear(); };
void Canvas::draw() const {
  SDL_SetRenderDrawColor(renderer, default_color.r, default_color.g,
                         default_color.b, default_color.a);
  SDL_RenderClear(renderer);
  for (auto &pair : color_map) {
    SDL_SetRenderDrawColor(renderer, pair.first.r, pair.first.g, pair.first.b,
                           pair.first.a);
    SDL_RenderDrawPoints(renderer, pair.second.data(), pair.second.size());
  }
  SDL_RenderPresent(renderer);
  SDL_Delay(5000);
}
