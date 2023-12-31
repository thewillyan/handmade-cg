#include "algebrick/include/algebrick.hpp"
#include "algebrick/include/matrix.hpp"
#include <iostream>

int main() {
  Algebrick::Vec3d v{6, 2, 4};
  std::cout << "v = " << v << std::endl;
  const double k = 2;
  std::cout << v << k << " = " << (v * k) << std::endl;
  std::cout << v << "(1/" << k << ") = " << (v / k) << std::endl;

  Algebrick::Vec3d u{4, 0, 3};
  std::cout << "u = " << u << std::endl;
  std::cout << v << " + " << u << " = " << (v + u) << std::endl;
  std::cout << v << " - " << u << " = " << (v - u) << std::endl;
  std::cout << v << " * " << u << " = " << (v * u) << std::endl;
  std::cout << v << " @ " << u << " = " << v.direct_mul(u) << std::endl;

  Algebrick::Vec3d w = v.norm();
  std::cout << "Normalized v = " << w << std::endl;
  std::cout << "Normalized v lenght: " << w.length() << std::endl;

  Algebrick::Point3d p{1, 1, 3};
  Algebrick::Point3d q{1, 0, 2};
  std::cout << "p := " << p << std::endl;
  std::cout << "q := " << q << std::endl;
  std::cout << "p - q = " << (p - q) << std::endl;

  Algebrick::Matrix m = {{3, 2}, {4, 3}};
  Algebrick::Matrix inv = Algebrick::Matrix::inv(m).mul(m);
  for (size_t i = 0; i < inv.get_lines(); ++i) {
    std::cout << "| ";
    for (size_t j = 0; j < inv.get_cols(); ++j) {
      std::cout << inv.get(i, j) << ' ';
    }
    std::cout << "|\n";
  }
  std::cout << std::endl;
  for (size_t i = 0; i < m.get_lines(); ++i) {
    std::cout << "| ";
    for (size_t j = 0; j < m.get_cols(); ++j) {
      std::cout << m.get(i, j) << ' ';
    }
    std::cout << "|\n";
  }
  return 0;
}
