#ifndef Graphite_Scene
#define Graphite_Scene

#include "../../algebrick/include/point3d.hpp"
#include "../../algebrick/include/vec3d.hpp"
#include "../include/canvas.hpp"
#include "../include/space.hpp"
#include "algebrick/include/matrix.hpp"
#include "algebrick/include/ray.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <optional>

namespace Graphite {

enum class RenderMode { PERSPECTIVE, ORTHOGRAPHIC, OBLIQUE };

class FrameRef {
private:
  Algebrick::Vec3d x;
  Algebrick::Vec3d y;
  Algebrick::Vec3d z;
  Algebrick::Point3d o;

public:
  FrameRef();
  FrameRef(const Algebrick::Point3d &, const Algebrick::Point3d &,
           const Algebrick::Point3d &);

  // getters
  const Algebrick::Vec3d &x_axis() const;
  const Algebrick::Vec3d &y_axis() const;
  const Algebrick::Vec3d &z_axis() const;
  const Algebrick::Point3d &origin() const;

  // special methods
  Algebrick::Matrix perspective_matrix() const;
};

class Scene {
private:
  // const FrameRef space_ref;
  FrameRef eye_pov;
  Space *space;
  std::optional<SDL_Color> bg;
  RenderMode mode;
  Algebrick::Vec3d oblique_dir;
  double canvas_dist;

public:
  Scene(Space *);
  Scene(Space *, RenderMode);
  ~Scene();

  // getters
  const Space &get_space() const;
  Space &get_space();
  std::optional<SDL_Color> get_bg_color() const;
  double get_canvas_dist() const;
  Algebrick::Ray ray_to(const Algebrick::Point3d &p) const;

  // setters
  void set_canvas_dist(double);
  void set_space(Space *);
  void set_bg_color(SDL_Color);
  void set_render_mode(const RenderMode);
  void set_oblique_dir(const Algebrick::Vec3d &);
  void set_eye_pov(FrameRef &&);

  // getters
  const FrameRef &get_pov() const;
  void render(Canvas &) const;
};

struct SceneEventHandler {
private:
  Scene *scene;

public:
  SceneEventHandler(Scene *scene) : scene{scene} {}
  inline State operator()(const SDL_Event &event, Canvas &canvas) const {
    switch (event.type) {
    case SDL_MOUSEBUTTONUP: {
      Algebrick::Ray ray = scene->ray_to(Algebrick::Point3d{
          static_cast<double>(event.button.x),
          static_cast<double>(event.button.y), -scene->get_canvas_dist()});

      std::optional<Object::RayLenObj> inter = scene->get_space().raycast(ray);
      if (inter.has_value()) {
        Object::Object *obj = inter->second;
        obj->set_visible(!obj->is_visible());
      }
      canvas.clear();
      scene->get_space().reset_transform();
      scene->render(canvas);
      return State::Refresh;
    }
    case SDL_QUIT:
      return State::Quit;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_q:
      case SDLK_ESCAPE:
        return State::Quit;
      }
    }
    return State::Continue;
  }
};

} // namespace Graphite

#endif // !Graphite_Scene
