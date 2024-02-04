#include "geometry/sphere.hpp"
#include "math/vec3f.hpp"
#include <camera.hpp>
#include <cmath>
#include <format>
#include <image.hpp>
#include <iostream>
#include <png_saver.hpp>
#include <profiler.hpp>
#include <ranges>
#include <renderer.hpp>
#include <scene.hpp>

constexpr Material mirror     = {{0.0, 16., 0.8, 0.0}, {1.0, 1.0, 1.0}, 1425.,  1.};
constexpr Material glass      = {{0.0,  0.9, 0.1, 0.8}, {0.6, 0.7, 0.8},  125., 1.5};
constexpr Material red_rubber = {{0.9, 0.1, 0.0, 0.0}, {0.3, 0.1, 0.1},    10,  1.};

int main() {
  ImageBuffer image(720, 480, {255, 255, 255, 255});
  Scene scene;
  scene.light_sources.push_back(Light{Vec3f(-10, -10, 10), 1});
  scene.light_sources.push_back(Light{Vec3f( 10,  10, 10), 1});
  scene.light_sources.push_back(Light{Vec3f(-10,  10, 10), 1});
  scene.light_sources.push_back(Light{Vec3f( 10, -10, 10), 1});

  scene.objects.push_back(std::make_unique<Sphere>(Vec3f(8, 6, 0), 2, red_rubber));
  scene.objects.push_back(std::make_unique<Sphere>(Vec3f(8, 3, 0), 2, red_rubber));
  scene.objects.push_back(std::make_unique<Sphere>(Vec3f(8, -2, 0), 3, glass));
  scene.objects.push_back(std::make_unique<Sphere>(Vec3f(5, 4.5, 3), 1, mirror));

  scene.background = {0.2, 0.7, 0.8};
  Camera camera({0, 0, 0}, {1, 0, 0}, M_PI_2);

#if 0
  {
    PROFILE_SCOPE("animation rendering");
    for (int i : std::views::iota(0, 90)) {
      const float angle = i * 4 * M_PI / 360.f - M_PI_4;
      camera.poisition() = Vec3f(cos(angle), sin(angle), 0) * 8 + Vec3f(8, 0, 0);
      camera.look_at(Vec3f(8, 0, 0));
      render(image, scene, camera);
      std::cout << std::format("rendering frame no. {:03}...", i) << std::endl;
      save_png(image, std::format("output/output{:03}.png", i));
    }
  }
#else
  {
    PROFILE_SCOPE("single frame rendering");
    render(image, scene, camera);
  }
  save_png(image, "example.png");
#endif

  return 0;
}
