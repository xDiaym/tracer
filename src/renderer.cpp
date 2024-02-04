#include <camera.hpp>
#include <image.hpp>
#include <geometry/object.hpp>
#include <scene.hpp>

#include <cmath>


Intersection hit_scene(const Scene &scene, Ray ray) {
  Intersection intersection;
  float nearest = std::numeric_limits<float>::max();

  if (std::abs(ray.dir.z) > 2e-4) {
    float d = -(4)/ray.dir.z; // the checkerboard plane has equation y = -4
    Vec3f p = ray.orig + ray.dir*d;
    if (d > 2e-4 && d < nearest && std::abs(p.y) < 10 && std::abs(p.x) < 10) {
      nearest = d, intersection.norm = {1, 0, 0}, intersection.hit_point = p, intersection.hit = true;
      intersection.material.diffuse_color = (int(0.5 * p.x) + int(0.5 * p.y + 1000)) & 1 ? Vec3f(1, 1, 0) : Vec3f(1);
    }
  }

  for (auto&& object : scene.objects) {
    Intersection inter = object->intersect(ray);
    if (!inter.hit || inter.distance > nearest) continue;
    nearest = inter.distance;
    intersection = inter;
  }
  return intersection;
}

Vec3f cast_ray(const Scene &scene, Ray ray, const int depth = 0) {
  Vec3f color = scene.background;

  const auto [material, hit_point, N, d, hit] = hit_scene(scene, ray);
  if (!hit || depth > 4) return color;

  const auto reflected = cast_ray(scene, {hit_point, reflect(ray.dir, N).norm()}, depth + 1);
  const auto refracted = cast_ray(scene, {hit_point, refract(ray.dir, N, material.refractive_index).norm()}, depth + 1);

  auto diffusive_intensity = 0.f, specular_intensity = 0.f;
  for (const auto &source: scene.light_sources) {
    const auto L = (source.position - hit).norm();
    const auto [_1, shadow_pt, _2, _3, in_shadow] = hit_scene(scene, {hit_point, L});
    if (in_shadow && (shadow_pt - hit_point).magnitude() < (source.position - hit_point).magnitude()) continue;

    diffusive_intensity += std::max(0.f, N.dot(L)) * source.intense;
    const auto reflected_angle = std::max(0.f, reflect(L, N).dot(ray.dir));
    specular_intensity += std::pow(reflected_angle, material.specular_exponent);
  }
  // FIXME:  use light source for this                            ---v
  color = material.diffuse_color * (diffusive_intensity + scene.ambient_intensity) * material.albedo.diffusive +
          Vec3f(1, 1, 1) * specular_intensity * material.albedo.specular + reflected * material.albedo.reflective +
          refracted * material.albedo.refractive;
  // TODO: use light color --^
  return color;
}


#include <omp.h>
void render(ImageBuffer &image, const Scene &scene, const Camera &camera) {
  const auto fov = std::tan(camera.fov() / 2);

  #pragma omp parallel for
  for (int y = 0; y < image.height(); ++y)
    for (int x = 0; x < image.width(); ++x) {
      const float i = (2.f * x / float(image.width()) - 1) * fov * image.aspect_ratio();
      const float j = (1 - 2.f * y / float(image.height())) * fov;
      const auto dir = (camera.direction() + i * camera.right() + j * camera.up()).norm();
      const Ray ray = {camera.position(), dir};

      const auto color = cast_ray(scene, ray);
      image.set(x, y, Color::from(color));
    }
}
