#ifndef Graphite_Light_Intensity
#define Graphite_Light_Intensity

#include <SDL2/SDL_pixels.h>

namespace Graphite::Light {

class Intensity {
private:
  double ir;
  double ig;
  double ib;

public:
  // constructors
  Intensity(double r, double g, double b);
  Intensity(const SDL_Color &color);

  // operators
  Intensity operator+(const Intensity &other) const;
  Intensity operator*(const Intensity &other) const;
  Intensity operator*(double k) const;
  Intensity operator/(double k) const;

  SDL_Color apply(const SDL_Color &color) const;
};

} // namespace Graphite::Light

#endif // !Graphite_Light_Intensity
