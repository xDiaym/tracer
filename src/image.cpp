#include <algorithm>
#include <image.hpp>
#include <span>

ImageBuffer::ImageBuffer(size_t width, size_t height, Color default_) : width_(width), height_(height) {
  buffer = new Color[width_ * height_];
  auto s = std::span(buffer, width_ * height_);
  std::ranges::fill(s, default_);
}

size_t ImageBuffer::width() const noexcept { return width_; }

size_t ImageBuffer::height() const noexcept { return height_; }

float ImageBuffer::aspect_ratio() const noexcept { return width_ / static_cast<float>(height_); }

const uint8_t *ImageBuffer::line(size_t n) const noexcept {
  return reinterpret_cast<std::uint8_t *>(buffer + n * width_);
}

void ImageBuffer::set(size_t x, size_t y, Color color) noexcept { buffer[x + y * width_] = color; }

ImageBuffer::~ImageBuffer() { std::free(buffer); }
