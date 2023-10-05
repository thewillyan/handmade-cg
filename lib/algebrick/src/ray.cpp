#include "../include/algebrick.hpp"
#include "../include/point3d.hpp"
#include "../include/vec3d.hpp"

using namespace Algebrick;

// constructor
Ray::Ray(Point3d s, const Vec3d &d) : src{s}, dir{d.norm()} {}
Ray::Ray(Point3d s, const Point3d &d) : src{s}, dir{(d - s).norm()} {}

// getters
Point3d Ray::source() const { return src; }
Vec3d Ray::direction() const { return dir; }
