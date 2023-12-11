#include "../include/canvas.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstddef>

using namespace Graphite;

Canvas::Canvas(size_t w, size_t h, size_t pw, size_t ph, SDL_Color color)
    : width{w}, height{h}, pov_w{pw}, pov_h{ph}, default_color{color},
      color_map{std::map<SDL_Color, std::vector<SDL_Point>, cmpColors>()},
      window{nullptr}, renderer{nullptr}, event_handler{} {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}

Canvas::Canvas(size_t w, size_t h, SDL_Color color)
    : width{w}, height{h}, pov_w{60}, pov_h{60}, default_color{color},
      color_map{std::map<SDL_Color, std::vector<SDL_Point>, cmpColors>()},
      window{nullptr}, renderer{nullptr}, event_handler{} {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}
Canvas::Canvas(size_t w, size_t h)
    : width{w}, height{h}, pov_w{60}, pov_h{60}, default_color{0, 0, 0, 255},
      color_map{std::map<SDL_Color, std::vector<SDL_Point>, cmpColors>()},
      window{nullptr}, renderer{nullptr}, event_handler{} {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
};
Canvas::Canvas(Canvas &&other)
    : width{other.get_width()}, height{other.get_height()},
      pov_w{other.get_pov_width()}, pov_h{other.get_pov_height()},
      default_color{std::move(other.default_color)}, color_map{std::move(
                                                         other.color_map)} {
  other.window = nullptr;
  other.renderer = nullptr;
}
Canvas::~Canvas() {}

size_t Canvas::get_width() const { return width; }
size_t Canvas::get_height() const { return height; }
size_t Canvas::get_pov_width() const { return pov_w; }
size_t Canvas::get_pov_height() const { return pov_h; }

void Canvas::set_pov_width(size_t w) { pov_w = w; }
void Canvas::set_pov_height(size_t h) { pov_h = h; }
void Canvas::set_pixel(SDL_Point point, SDL_Color color) {
  color_map[color].push_back(point);
}
void Canvas::set_handler(
    std::function<State(const SDL_Event &, Canvas &)> handler) {
  event_handler = handler;
}

void Canvas::zoom_in(double factor) {
  pov_w = static_cast<size_t>(pov_w / factor);
  pov_h = static_cast<size_t>(pov_h / factor);
}
void Canvas::zoom_out(double factor) {
  pov_w = static_cast<size_t>(pov_w * factor);
  pov_h = static_cast<size_t>(pov_h * factor);
}
void Canvas::fill(SDL_Color c) {
  default_color = c;
  this->clear();
}
void Canvas::clear() { color_map.clear(); };

enum class AppState { Continue, Quit };

AppState handler_loop() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_MOUSEBUTTONUP:
      // event.button;
      break;
    case SDL_QUIT:
      return AppState::Quit;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_q:
      case SDLK_ESCAPE:
        return AppState::Quit;
      }
    }
  }
  return AppState::Continue;
}

void Canvas::draw() {
  // display loop
  auto state = State::Refresh;
  SDL_Event event;
  while (state != State::Quit) {
    if (state == State::Refresh) {
      SDL_SetRenderDrawColor(renderer, default_color.r, default_color.g,
                             default_color.b, default_color.a);
      SDL_RenderClear(renderer);
      for (auto &pair : color_map) {
        SDL_SetRenderDrawColor(renderer, pair.first.r, pair.first.g,
                               pair.first.b, pair.first.a);
        SDL_RenderDrawPoints(renderer, pair.second.data(), pair.second.size());
      }
      SDL_RenderPresent(renderer);
    }

    if (event_handler.has_value()) {
      while (SDL_PollEvent(&event)) {
        state = (*event_handler)(event, *this);
      }
    }
  }
}
