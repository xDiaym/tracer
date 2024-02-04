#pragma once
#include <geometry/object.hpp>
#include <light_source.hpp>
#include <memory>
#include <vector>


struct Scene {
  std::vector<Light> light_sources;
  std::vector<std::unique_ptr<Object>> objects;
  Vec3f background = {0, 0, 0};
  float ambient_intensity = 0.25;
};