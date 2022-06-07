#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "Params.hpp"
#include "fractals/Fractal.hpp"
#include "Palette.hpp"

class Generator
{
public:
    Generator(Params const& params, Palette palette);

    void generateFractalThreaded(uint32_t offset, uint32_t divisions, uint8_t* buffer, std::shared_ptr<Fractal> p_fractal);

    std::shared_ptr<Fractal> getFractal();

    void getCoords(uint32_t height, uint32_t width, double& x, double& y);

private:
    Params m_params;
    Palette m_palette;
};

#endif