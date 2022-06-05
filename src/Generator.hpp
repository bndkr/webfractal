#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "Params.hpp"

class Generator
{
public:
    Generator(Params const& params);
private:
    Params m_params;
};

#endif