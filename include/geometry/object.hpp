#pragma once
#include <cstdint>
#include <material.hpp>
#include <ray.hpp>
#include <math/vec3f.hpp>


struct Intersection {
  Material material = {{1, 0, 0, 0}, {1, 1, 1}, 0, 0};
  Vec3f hit_point = {0, 0, 0};
  Vec3f norm = {0, 0, 0};
  float distance = 0;
  uint8_t hit = false;
};


class Object {
public:
  virtual Intersection intersect(Ray ray) const noexcept = 0;
  virtual ~Object() = default;
};
