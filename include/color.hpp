#pragma once
#include "math/vec3f.hpp"
#include <algorithm>
#include <cstdint>

struct Color {
  uint8_t r, g, b, a;

  static Color from_f32(float r, float g, float b, float a = 1.f) {
    return {uint8_t(std::clamp(255 * r, 0.f, 255.f)), uint8_t(std::clamp(255 * g, 0.f, 255.f)),
            uint8_t(std::clamp(255 * b, 0.f, 255.f)), uint8_t(std::clamp(255 * a, 0.f, 255.f))};
  }

  static Color from(Vec3f v) {
    return {uint8_t(std::clamp(255 * v.x, 0.f, 255.f)), uint8_t(std::clamp(255 * v.y, 0.f, 255.f)),
            uint8_t(std::clamp(255 * v.z, 0.f, 255.f)), 255};
  }
};