#pragma once
#include <cstdint>

using f32_t = float;
using f64_t = double;

namespace arch {
namespace constants {
constexpr f32_t PI{3.14159265358979323846};
constexpr uint16_t CURVE_MAX_SEGMENTS{100};
constexpr float TEXT_OFFSET{0.7};
}  // namespace constants
}  // namespace arch
