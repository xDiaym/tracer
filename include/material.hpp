#pragma once
#include <math/vec3f.hpp>


struct Material {
  struct {
    float diffusive, specular, reflective, refractive;
  } albedo;
  Vec3f diffuse_color;// FIXME: color
  float specular_exponent;
  float refractive_index;
};