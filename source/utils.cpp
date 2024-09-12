#include "utils.hpp"

namespace arch {

Color::Color(float r, float g, float b, float a) {
  if (r < 0)
    r = 0;
  if (r > 1)
    r = r / 255;
  if (g < 0)
    g = 0;
  if (g > 1)
    g = g / 255;
  if (b < 0)
    b = 0;
  if (b > 1)
    b = b / 255;
  if (a < 0)
    a = 0;
  if (a > 1)
    a = a / 255;
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

Color Color::darken(float factor) const {
  return {r - factor, g - factor, b - factor, a};
}

Color Color::lighten(float factor) const {
  return {r + factor, g + factor, b + factor, a};
}
}  // namespace arch
