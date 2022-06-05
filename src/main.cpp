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
        if (params.m_exit)
        {
            return 1;
        }
        Palette palette(params.m_palette, 90);

        Generator generator(params);
        
    }
    catch (std::runtime_error e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}