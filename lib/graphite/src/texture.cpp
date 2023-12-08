#include "graphite/include/texture.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>
#include <cmath>

using namespace Graphite;

Texture::Texture(SDL_Surface *s) : mode{TextureMode::Repeat}, surface{s} {}
Texture::Texture(SDL_Surface *s, TextureMode m) : mode{m}, surface{s} {}

SDL_Color get_pixel_color(const SDL_Surface *surface, const int i,
                          const int j) {
  // Bytes per pixel
  const Uint8 Bpp = surface->format->BytesPerPixel;
  Uint8 *pPixel = (Uint8 *)surface->pixels + j * surface->pitch + i * Bpp;
  Uint32 PixelData = *(Uint32 *)pPixel;
  SDL_Color Color = {0x00, 0x00, 0x00, 0x00};

  SDL_GetRGBA(PixelData, surface->format, &Color.r, &Color.g, &Color.b,
              &Color.a);
  return Color;
}

SDL_Color Texture::get_color(const int i, const int j) {
  SDL_Color color{1, 1, 1, 1};
  switch (mode) {
  case TextureMode::Scale:
    // TODO: all this.
    break;
  case TextureMode::Repeat:
    color = get_pixel_color(surface, std::abs(i) % surface->h,
                            std::abs(j) % surface->w);
  }
  return color;
}
