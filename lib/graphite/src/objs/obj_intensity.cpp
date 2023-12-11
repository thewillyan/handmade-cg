#include "graphite/include/objs/obj_intensity.hpp"
#include <SDL2/SDL_pixels.h>

Graphite::Object::ObjectIntensity::ObjectIntensity()
    : shineness(1), ambient_intensity(1, 1, 1), diffuse_intensity(1, 1, 1),
      specular_intensity(1, 1, 1){};

Graphite::Object::ObjectIntensity::ObjectIntensity(
    double shineness, const Light::Intensity &ambient_intensity,
    const Light::Intensity &diffuse_intensity,
    const Light::Intensity &specular_intensity)
    : shineness(shineness), ambient_intensity(ambient_intensity),
      diffuse_intensity(diffuse_intensity),
      specular_intensity(specular_intensity){};

Graphite::Object::ObjectIntensity::ObjectIntensity(SDL_Color c, double s)
    : shineness(s), ambient_intensity(c), diffuse_intensity(c),
      specular_intensity(c){};

// methods
double Graphite::Object::ObjectIntensity::get_shineness() const {
  return shineness;
}
Graphite::Light::Intensity
Graphite::Object::ObjectIntensity::get_ambient_intensity() const {
  return ambient_intensity;
}
Graphite::Light::Intensity
Graphite::Object::ObjectIntensity::get_diffuse_intensity() const {
  return diffuse_intensity;
}
Graphite::Light::Intensity
Graphite::Object::ObjectIntensity::get_specular_intensity() const {
  return specular_intensity;
}

void Graphite::Object::ObjectIntensity::set_shineness(double shi) {
  this->shineness = shi;
}

void Graphite::Object::ObjectIntensity::set_ambient_intensity(
    const Light::Intensity &amb) {
  this->ambient_intensity = amb;
}

void Graphite::Object::ObjectIntensity::set_diffuse_intensity(
    const Light::Intensity &dif) {
  this->diffuse_intensity = dif;
}

void Graphite::Object::ObjectIntensity::set_specular_intensity(
    const Light::Intensity &spec) {
  this->specular_intensity = spec;
}
