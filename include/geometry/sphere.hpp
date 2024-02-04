#pragma once
#include "material.hpp"
#include "math/vec3f.hpp"
#include <geometry/object.hpp>
#include <cmath>


struct Sphere : public Object {
  Vec3f center;
  float radius;
  Material material;

  Sphere(Vec3f center_, float radius_, Material material_)
      : center(center_), radius(radius_), material(material_) {}

  Intersection intersect(Ray ray) const noexcept override {
    const auto L = center - ray.orig;
    const auto t = L.dot(ray.dir);
    const auto d2 = L.dot(L) - t * t;
    if (d2 >= radius * radius) return {.hit = false};
    const auto d = std::sqrt(radius * radius - d2);
    if (t - d > 1e-3) {
      const auto hit_point = ray.orig + (t - d) * ray.dir;
      const auto norm = (hit_point - center).norm();
      return {material, hit_point, norm, t - d, true};
    }
    if (t + d > 1e-3) {
      const auto hit_point = ray.orig + (t + d) * ray.dir;
      const auto norm = (hit_point - center).norm();
      return {material, hit_point, norm, t + d, true};
    }
    return {.hit = false};
  }
};
