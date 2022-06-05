#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include <boost/multiprecision/cpp_complex.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

#include <typeinfo>

class Fractal
{
public:
    Fractal() : m_iterations(100), m_beginX(0), m_beginY(0) {}
    Fractal(uint32_t iterations, double beginX, double beginY) :
        m_iterations(100), m_beginX(beginX), m_beginY(beginY) {}
        
    virtual float getPixel(double x, double y) = 0;

protected:
    uint32_t m_iterations;
    double m_beginX;
    double m_beginY;

};
#endif