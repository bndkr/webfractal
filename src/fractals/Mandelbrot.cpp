#include "Mandelbrot.hpp"

#include "Complex.hpp"

float Mandelbrot::getPixel(double x, double y)
{
    // typedef boost::multiprecision::cpp_complex_oct Complex; 


    Complex z = {0, 0};
    Complex before = {0, 0};
    Complex c = {x, y};

    uint32_t iteration = 0;
    while(z.distanceFromOrigin() < 2 && iteration < m_iterations)
    {
        before = z;
        z = (z * z) + c;
        iteration++;
    }
    if (iteration == m_iterations)
    {
        return -1.0f; // inside the mandelbrot set
    }
    auto min = before.distanceFromOrigin();
    auto max = z.distanceFromOrigin();

    auto gradient = static_cast<float>((2 - min) / (max - min));// min is greater than 2. why?
    return iteration + gradient;

}