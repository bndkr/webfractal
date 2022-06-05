#ifndef PARAMS_HPP
#define PARAMS_HPP

#include <string>

class Params
{
public:
    Params(int argc, char** argv);
    
    double m_minX, m_minY, m_maxX, m_maxY;
    std::string m_palette, m_fractal;
    size_t m_height, m_width;
  
    bool m_exit;

};

#endif