#ifndef Graphite_Light
#define Graphite_Light

#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/ray.hpp"
#include "../include/object.hpp"
#include <SDL2/SDL_pixels.h>
#include <stdexcept>

namespace Graphite::Light {

class Intensity {
private:
  double ir;
  double ig;
  double ib;

public:
  Intensity(double r, double g, double b);
  Intensity operator+(const Intensity &other) const;
  SDL_Color apply(const SDL_Color &color) const;
};

class Source {
public:
  virtual Algebrick::Point3d get_pos() const = 0;
  virtual Intensity get_intensity(const Object &obj,
                                  const Algebrick::Point3d &inter,
                                  const Algebrick::Ray &eye_ray) const = 0;
};
} // namespace Graphite::Light

#endif // !Graphite_Light
