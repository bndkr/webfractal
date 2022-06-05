#include "FileOps.hpp"
#include "Generator.hpp"

#include <fstream>
#include <iostream>

Generator::Generator(Params const& params) : m_params(params)
{
    auto height = params.m_height;
    auto width = params.m_width;
    auto file = fileops::createBmpHeader(width, height, "fractal");

    const int numBytes = width * height * 3;
    char* p_buffer = new char[numBytes];

    for (uint32_t h = 0; h < height; h++)
    {
       for (uint32_t w = 0; w < width; w++)
       {
           p_buffer[((h * width) + w) * 3] = (char) h-w; // blue
           p_buffer[((h * width) + w) * 3 + 1] = (char)h - w * (2); // green
           p_buffer[((h * width) + w) * 3 + 2] = (char)h - w * (4); // red
       }
    }
    file->write(p_buffer, numBytes);
    file->close();

    delete [] p_buffer;
} 