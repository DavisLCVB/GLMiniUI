#pragma once
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace arch {
struct Color {
  float r;
  float g;
  float b;
  float a;

  Color darken(float factor = 0.1) const;
  Color lighten(float factor = 0.1) const;

  Color(float r = 1.0, float g = 1.0, float b = 1.0, float a = 1.0);
};
}  // namespace arch
