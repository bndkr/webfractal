#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <Fractal.hpp>

class Mandelbrot : public virtual Fractal
{
public:
    float getPixel(double x, double y);
};

#endif