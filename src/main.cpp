#include "Generator.hpp"
#include "Params.hpp"
#include "Palette.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    try
    {
        std::cin.get();
        Params params(argc, argv);
        Palette palette(params.m_palette, 27);
        Generator generator(params, palette);
    }
    catch (std::runtime_error e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}