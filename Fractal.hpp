#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include <typeinfo>

class Fractal
{
public:
    Fractal() {}
    virtual float getPixel(double x, double y) = 0;

private:
    uint32_t m_iterations;
    double m_beginX;
    double m_beginY;

};
#endif