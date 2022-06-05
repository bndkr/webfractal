#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include <typeinfo>

class Fractal
{
public:
    Fractal(uint32_t iterations, double beginX, double beginY) :
        m_iterations(iterations), m_beginX(beginX), m_beginY(beginY) {}
    virtual float getPixel(double x, double y) = 0;

private:
    uint32_t m_iterations;
    double m_beginX;
    double m_beginY;

};
#endif