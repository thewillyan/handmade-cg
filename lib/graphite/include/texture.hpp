#ifndef Graphite_Texture
#define Graphite_Texture

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
namespace Graphite {

enum TextureMode {
  Scale,
  Repeat,
};

class Texture {
private:
  TextureMode mode;
  SDL_Surface *surface;

public:
  Texture(SDL_Surface *);
  Texture(SDL_Surface *, TextureMode);

  SDL_Color get_color(int, int);
};
} // namespace Graphite

#endif // !Graphite_Texture
