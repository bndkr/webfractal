#include "Mandelbrot.hpp"

float Mandelbrot::getPixel(double x, double y)
{
    return static_cast<float>(x + y);
}