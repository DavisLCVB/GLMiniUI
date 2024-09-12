#pragma once
#include <array>
#include <cstdint>
#include "GL/glut.h"
#include "constants.hpp"
#include "utils.hpp"

namespace arch {
class Window {
 public:
  Window() = delete;
  Window(const Window&) = delete;
  Window(Window&&) = delete;
  auto operator=(const Window&) -> Window& = delete;
  auto operator=(Window&&) -> Window& = delete;
  static auto width() -> uint16_t;
  static auto width(uint16_t width) -> void;
  static auto height() -> uint16_t;
  static auto height(uint16_t height) -> void;
  static auto bgColor() -> Color;
  static auto bgColor(const Color& bgColor) -> void;

 private:
  static uint16_t _width;
  static uint16_t _height;
  static Color _bgColor;
};
}  // namespace arch
