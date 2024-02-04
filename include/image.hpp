#pragma once
#include <color.hpp>
#include <cstddef>
#include <cstdint>

class ImageBuffer final {
public:
  ImageBuffer(size_t width, size_t height, Color default_ = {255, 255, 255, 255});

  size_t width() const noexcept;
  size_t height() const noexcept;
  float aspect_ratio() const noexcept;
  const uint8_t *line(size_t) const noexcept;

  void set(size_t x, size_t y, Color color) noexcept;

  ~ImageBuffer();

private:
  size_t width_, height_;
  Color *buffer = nullptr;
};
