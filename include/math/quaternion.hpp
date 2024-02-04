#pragma once
#include "math/vec3f.hpp"
#include <cmath>

struct Quaternion {
  Vec3f u;
  float a;

  Quaternion(float x, float y, float z, float w) : a(x), u({y, z, w}) {}

  Quaternion(Vec3f v, float angle) : u(v.norm() * sin(angle / 2)), a(cos(angle / 2)) {}

  Quaternion operator+(Quaternion other) const noexcept { return {u + other.u, a + other.a}; }

  Quaternion operator-() const noexcept { return {-u, -a}; }

  Quaternion operator*(Quaternion other) const noexcept {
    return {a * other.u + other.a * u + u.cross(other.u), a * other.a - u.dot(other.u)};
  }

  Vec3f operator*(Vec3f v) const noexcept {
    Quaternion qu(0, v.x, v.y, v.z);
    return (*this * qu * conj()).u;
  }

  Quaternion conj() const noexcept { return {-u, a}; }
};