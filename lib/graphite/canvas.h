#ifndef Graphite_Render_H
#define Graphite_Render_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <initializer_list>
#include <map>
#include <vector>

namespace Graphite {

struct cmpColors {
  int hashColor(const SDL_Color &color);
  bool operator()(const SDL_Color &a, const SDL_Color &b);
};

class Canvas {
private:
  const size_t width;
  const size_t height;
  SDL_Color default_color;
  std::map<SDL_Color, std::vector<SDL_Point>, cmpColors> color_map;
  SDL_Window *window;
  SDL_Renderer *renderer;

public:
  // contructor
  Canvas(size_t, size_t, SDL_Color);
  Canvas(size_t, size_t);

  // destructor
  ~Canvas();

  // delete copy statements
  Canvas(const Canvas &) = delete;
  Canvas &operator=(const Canvas &) = delete;

  // move
  Canvas(Canvas &&);
  Canvas &operator=(Canvas &&) = delete;

  // getters
  size_t get_width() const;
  size_t get_height() const;

  // methods
  void set_pixel(SDL_Point, SDL_Color);
  void fill(SDL_Color);
  void clear();
  void draw() const;
};
} // namespace Graphite
#endif // !Graphite_Render_H
