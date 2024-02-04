#pragma once

class Vec3f {
public:
  float x, y, z;

  constexpr Vec3f(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

  constexpr Vec3f(float fill) : x(fill), y(fill), z(fill) {}

  friend Vec3f operator+(Vec3f lhs, Vec3f rhs) noexcept;
  friend Vec3f operator-(Vec3f lhs, Vec3f rhs) noexcept;
  friend Vec3f operator*(float alpha, Vec3f rhs) noexcept;
  friend Vec3f operator*(Vec3f lhs, float alpha) noexcept;
  Vec3f operator-() const noexcept;

  Vec3f &operator+=(Vec3f other) noexcept;
  Vec3f &operator-=(Vec3f other) noexcept;
  Vec3f &operator*=(float alpha) noexcept;

  Vec3f norm() const noexcept;

  float dot(Vec3f other) const noexcept;
  Vec3f cross(Vec3f other) const noexcept;

  float magnitude() const noexcept;
  float square_magnitude() const noexcept;
};

float dot(Vec3f a, Vec3f b) noexcept;
Vec3f cross(Vec3f a, Vec3f b) noexcept;

Vec3f proj(Vec3f a, Vec3f b) noexcept;
Vec3f reflect(Vec3f v, Vec3f n) noexcept;
Vec3f refract(Vec3f I, Vec3f N, float eta0, float eta1 = 1.f) noexcept;
Vec3f step(float edge, Vec3f v) noexcept;
Vec3f step(Vec3f edge, Vec3f v) noexcept;