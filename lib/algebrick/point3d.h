#ifndef Algebrick_Point_H
#define Algebrick_Point_H

#include "vec3d.h"
#include <iostream>

namespace Algebrick {

class Point3d {
public:
  double x;
  double y;
  double z;

  Point3d(double a, double b, double c);
  Vec3d operator-(const Point3d &other) const;
  operator Vec3d() const;
};

std::ostream &operator<<(std::ostream &out, const Point3d &p);

};     // namespace Algebrick
#endif // !Algebrick_Point_H
