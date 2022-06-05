#include "FileOps.hpp"
#include "fractals/Mandelbrot.hpp"
#include "Generator.hpp"

#include <fstream>
#include <iostream>

Generator::Generator(Params const& params, Palette palette) : m_params(params)
{
    auto fractal = getFractal();

    auto height = params.m_height;
    auto width = params.m_width;
    auto file = fileops::createBmpHeader(width, height, "fractal");

    auto xmin = params.m_minX;
    auto xmax = params.m_maxX;
    auto ymin = params.m_minY;
    auto ymax = params.m_maxY;

    const uint32_t numBytes = width * height * 3;
    char* p_buffer = new char[numBytes];
    if (!p_buffer)
    {
        throw std::runtime_error("unable to initialize image buffer");
    }
    std::cout << "generating fractal:" << std::endl;
    for (uint32_t h = 0; h < height; h++)
    {
       for (uint32_t w = 0; w < width; w++)
       {
            double x, y;
            getCoords(h, w, x, y);
            auto iterations = fractal->getPixel(x, y);
            Color c  = palette.iterationsToColor(iterations);
            p_buffer[((h * width) + w) * 3] = (char) c.blue;
            p_buffer[((h * width) + w) * 3 + 1] = (char) c.green;
            p_buffer[((h * width) + w) * 3 + 2] = (char) c.red;
       }
    }
    file->write(p_buffer, numBytes);
    file->close();

    delete [] p_buffer;
} 

std::shared_ptr<Fractal> Generator::getFractal()
{
    if (m_params.m_fractal == "Mandelbrot")
        return std::make_shared<Mandelbrot>();
    else 
    {
        throw std::runtime_error("you didn't type mandelbrot right");
    }
}

void Generator::getCoords(uint32_t height, uint32_t width, double& x, double& y)
{
    x = m_params.m_minX + (((m_params.m_maxX - m_params.m_minX) / m_params.m_width) * width);
    y = m_params.m_minY + (((m_params.m_maxY - m_params.m_minY) / m_params.m_height) * height);
}