#pragma once
#include "math/vec3f.hpp"

class Camera {
public:
  Camera(Vec3f pos, Vec3f dir, float fov_, Vec3f up = Vec3f(0, 0, 1))
      : position_(pos), direction_(dir.norm()), up_(up.norm()), fov_(fov_) {}

  const Vec3f &position() const noexcept { return position_; }
  Vec3f &poisition() noexcept { return position_; }

  const Vec3f &direction() const noexcept { return direction_; }
  Vec3f &direction() noexcept { return direction_; }

  const Vec3f &up() const noexcept { return up_; }
  Vec3f &up() noexcept { return up_; }

  Vec3f right() const noexcept { return cross(up_, direction_); }

  float fov() const noexcept { return fov_; }
  float &fov() noexcept { return fov_; }

  void look_at(Vec3f pos) noexcept {
    direction_ = (pos - position_).norm();
  }

private:
  Vec3f position_;
  Vec3f direction_;
  Vec3f up_;
  float fov_;
};
