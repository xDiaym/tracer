#include "math/vec3f.hpp"
#include <algorithm>
#include <cmath>


Vec3f operator+(Vec3f lhs, Vec3f rhs) noexcept { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}; }

Vec3f operator-(Vec3f lhs, Vec3f rhs) noexcept { return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z}; }

Vec3f operator*(float alpha, Vec3f rhs) noexcept { return {alpha * rhs.x, alpha * rhs.y, alpha * rhs.z}; }

Vec3f operator*(Vec3f lhs, float alpha) noexcept { return {alpha * lhs.x, alpha * lhs.y, alpha * lhs.z}; }

Vec3f Vec3f::operator-() const noexcept { return {-x, -y, -z}; }


Vec3f &Vec3f::operator+=(Vec3f other) noexcept {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Vec3f &Vec3f::operator-=(Vec3f other) noexcept {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

Vec3f &Vec3f::operator*=(float alpha) noexcept {
  x *= alpha;
  y *= alpha;
  z *= alpha;
  return *this;
}

Vec3f Vec3f::norm() const noexcept {
  const auto len = magnitude();
  // FIXME: zero division
  return {x / len, y / len, z / len};
}


float Vec3f::dot(Vec3f other) const noexcept { return x * other.x + y * other.y + z * other.z; }

Vec3f Vec3f::cross(Vec3f other) const noexcept {
  return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
}


float Vec3f::magnitude() const noexcept { return std::sqrt(x * x + y * y + z * z); }

float Vec3f::square_magnitude() const noexcept { return x * x + y * y + z * z; }

/** Projection of $a$ on $e$ */
float dot(Vec3f a, Vec3f b) noexcept { return a.dot(b); }
Vec3f cross(Vec3f a, Vec3f b) noexcept { return a.cross(b); }

Vec3f proj(Vec3f a, Vec3f e) noexcept { return a.dot(e) * e; }

Vec3f reflect(Vec3f v, Vec3f n) noexcept { return v - 2 * v.dot(n) * n; }

Vec3f refract(Vec3f I, Vec3f N, float eta0, float eta1) noexcept {
  const float cos0 = std::clamp(0.f, 1.f, dot(I, N));
  if (cos0 < 0) return refract(I, -N, eta1, eta0);
  const float eta = eta0 / eta1;
  const float k = 1.f - eta * eta * (1.f - dot(N, I) * dot(N, I));
  if (k < 0.0) return Vec3f(0);
  return eta * I - (eta * dot(N, I) + std::sqrt(k)) * N;
}

Vec3f step(float edge, Vec3f v) noexcept { return {float(v.x > edge), float(v.y > edge), float(v.z > edge)}; }

Vec3f step(Vec3f edge, Vec3f v) noexcept { return {float(v.x > edge.x), float(v.y > edge.y), float(v.z > edge.z)}; }
