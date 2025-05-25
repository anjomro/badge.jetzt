#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "Complex.h"

namespace mandelbrot 
{
    // helper
    float c_abs(Complex number);
    bool check_if_part_of_mandelbrot(Complex point, size_t max_iter, size_t cutoff);
    void print_mandelbrot_set();
}

#endif