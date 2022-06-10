#ifndef PARAMS_HPP
#define PARAMS_HPP

#include <string>
#include <vector>

class Params
{
public:
    Params(int argc, char** argv);
    
    double m_minX, m_minY, m_maxX, m_maxY;
    std::string m_palette, m_fractal;
    uint32_t m_height, m_width;
    uint32_t m_iterations;
    uint32_t m_numColors;
    std::vector<uint32_t> m_colors;
};

#endif