#include "FileOps.hpp"
#include "fractals/Mandelbrot.hpp"
#include "Generator.hpp"

#include <fstream>
#include <iostream>
#include <thread>

Generator::Generator(Params const& params, Palette palette) : m_params(params), m_palette(palette)
{
    auto p_fractal = getFractal();

    auto height = params.m_height;
    auto width = params.m_width;

    const uint32_t numBytes = width * height * 3;
    uint8_t* p_buffer = new uint8_t[numBytes];
    if (!p_buffer)
    {
        throw std::runtime_error("unable to initialize image buffer");
    }

    auto file = fileops::createBmpHeader(width, height, "fractal");
    std::cout << "generating fractal:" << std::endl;

    // launch 8 threads that populate the buffer concurrently
    std::thread worker1(&Generator::generateFractalThreaded, this, 0, 8, p_buffer, p_fractal);
	std::thread worker2(&Generator::generateFractalThreaded, this, 1, 8, p_buffer, p_fractal);
	std::thread worker3(&Generator::generateFractalThreaded, this, 2, 8, p_buffer, p_fractal);
	std::thread worker4(&Generator::generateFractalThreaded, this, 3, 8, p_buffer, p_fractal);
	std::thread worker5(&Generator::generateFractalThreaded, this, 4, 8, p_buffer, p_fractal);
	std::thread worker6(&Generator::generateFractalThreaded, this, 5, 8, p_buffer, p_fractal);
	std::thread worker7(&Generator::generateFractalThreaded, this, 6, 8, p_buffer, p_fractal);
	std::thread worker8(&Generator::generateFractalThreaded, this, 7, 8, p_buffer, p_fractal);

	worker1.join();
	worker2.join();
	worker3.join();
	worker4.join();
	worker5.join();
	worker6.join();
	worker7.join();
	worker8.join();

    file->write((char*)p_buffer, numBytes);
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

void Generator::generateFractalThreaded(uint32_t offset, uint32_t divisions, uint8_t* p_buffer, std::shared_ptr<Fractal> p_fractal)
{
    auto xmin = m_params.m_minX;
    auto xmax = m_params.m_maxX;
    auto ymin = m_params.m_minY;
    auto ymax = m_params.m_maxY;
    auto height = m_params.m_height;
    auto width = m_params.m_width;

    for (uint32_t h = offset; h < height; h += divisions)
    {
       for (uint32_t w = 0; w < width; w++)
       {
            double x, y;
            uint8_t r, g, b;
            getCoords(h, w, x, y);
            auto iterations = p_fractal->getPixel(x, y);
            m_palette.iterationsToColor(iterations, r, g, b);
            p_buffer[((h * width) + w) * 3] = b;
            p_buffer[((h * width) + w) * 3 + 1] = g;
            p_buffer[((h * width) + w) * 3 + 2] = r;
       }
    }
}