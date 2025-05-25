#include "Complex.h"
#include "../base/display.h"
#include <Adafruit_SSD1306.h>
#include "mandelbrot.h"

namespace mandelbrot {
  // Max iterations of mandelbrot set to check
  const size_t MAX_ITER = 10;
  const float DIVERGENCE_CUTOFF = 2;
  const float MANDELBROT_MAX_X = 1;
  const float MANDELBROT_MIN_X = -2;
  const float MANDELBROT_MAX_Y = 1;
  const float MANDELBROT_MIN_Y = -1;

  const size_t DISPLAY_WIDTH = 128;
  const size_t DISPLAY_HEIGHT = 32;

  float c_abs(Complex number) {
    float real = number.real();
    float imaginary = number.imag();

    return sqrt(real * real + imaginary * imaginary);
  }

  bool check_if_part_of_mandelbrot(Complex point, size_t max_iter, size_t cutoff) {
    // First iteration
    Complex number = point;

    for(size_t i = 0; i < max_iter; i++) {
      if (c_abs(number) > 2) {
        return false;
      }
      // Take square
      number = number.c_sqr() + point;
    }

    return true;
  }

  void print_mandelbrot_set() {
    Adafruit_SSD1306& oledDisplay = display::get();

    float x_range = abs(MANDELBROT_MAX_X - MANDELBROT_MIN_X);
    float y_range = abs(MANDELBROT_MAX_Y - MANDELBROT_MIN_Y);

    for (float x = 0; x < DISPLAY_WIDTH; x++) {
      for (float y = 0; y < DISPLAY_HEIGHT; y++) {
        float real = (x/DISPLAY_WIDTH) * x_range + MANDELBROT_MIN_X;
        float imaginary = (y/DISPLAY_HEIGHT) * y_range + MANDELBROT_MIN_Y;
        Complex point(real, imaginary);

        bool part_of_mandelbrot = check_if_part_of_mandelbrot(point, MAX_ITER, DIVERGENCE_CUTOFF);
        uint16_t color = 0;
        if (part_of_mandelbrot) {
          color = SSD1306_BLACK;
        } else {
          color = SSD1306_WHITE;
        }

        oledDisplay.writePixel(x, y, color);
      }
    }
    display::display();
  }
}