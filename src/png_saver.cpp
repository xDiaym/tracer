#include <image.hpp>
#include <png.h>
#include <png_saver.hpp>

void save_png(const ImageBuffer &image, const std::filesystem::path &path) noexcept {
  FILE *fp = fopen(path.c_str(), "wb");
  if (!fp) abort();

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) abort();

  png_infop info = png_create_info_struct(png);
  if (!info) abort();

  if (setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  // Output is 8bit depth, RGB format.
  png_set_IHDR(png, info, image.width(), image.height(), 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);

  for (int i = 0; i < image.height(); ++i) png_write_row(png, image.line(i));

  png_write_end(png, info);

  fclose(fp);

  png_destroy_write_struct(&png, &info);
}