#include "globals.hpp"

namespace arch {
uint16_t Window::_width = 800;
uint16_t Window::_height = 600;
Color Window::_bgColor = {1.0, 1.0, 1.0, 1.0};

auto Window::width() -> uint16_t {
  return _width;
}

auto Window::width(uint16_t width) -> void {
  _width = width;
}

auto Window::height() -> uint16_t {
  return _height;
}

auto Window::height(uint16_t height) -> void {
  _height = height;
}

auto Window::bgColor() -> Color {
  return _bgColor;
}

auto Window::bgColor(const Color& bgColor) -> void {
  glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

}  // namespace arch
