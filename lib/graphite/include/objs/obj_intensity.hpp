#ifndef OBJECT_INTENSITY_HPP
#define OBJECT_INTENSITY_HPP

#include "graphite/include/intensity.hpp"
#include <SDL2/SDL_pixels.h>

namespace Graphite::Object {
class ObjectIntensity {
private:
  double shineness;
  Light::Intensity ambient_intensity;
  Light::Intensity diffuse_intensity;
  Light::Intensity specular_intensity;

public:
  ObjectIntensity();
  ObjectIntensity(double, const Light::Intensity &, const Light::Intensity &,
                  const Light::Intensity &);
  ObjectIntensity(SDL_Color, double);

  // methods
  double get_shineness() const;
  Light::Intensity get_ambient_intensity() const;
  Light::Intensity get_diffuse_intensity() const;
  Light::Intensity get_specular_intensity() const;

  void set_shineness(double);
  void set_ambient_intensity(const Light::Intensity &);
  void set_diffuse_intensity(const Light::Intensity &);
  void set_specular_intensity(const Light::Intensity &);
};
};     // namespace Graphite::Object
#endif // !OBJECT_INTENSITY_HPP
