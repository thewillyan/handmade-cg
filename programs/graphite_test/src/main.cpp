#include "../../../lib/graphite/canvas.h"
#include <SDL2/SDL_rect.h>
#include <cstddef>

void render_square(Graphite::Canvas &screen, SDL_Point center, int size,
                   SDL_Color color) {
  for (int x = (center.x - (size / 2)); x <= (center.x + (size / 2)); ++x) {
    for (int y = (center.y - (size / 2)); y <= (center.y + (size / 2)); ++y) {
      screen.set_pixel({x, y}, color);
    }
  }
}

int main() {
  const size_t HEIGHT = 500;
  const size_t WIDTH = 500;

  Graphite::Canvas screen = Graphite::Canvas(HEIGHT, WIDTH);
  render_square(screen, {HEIGHT / 2, WIDTH / 2}, 200, {200, 100, 50, 255});
  screen.draw();

  return 0;
}
