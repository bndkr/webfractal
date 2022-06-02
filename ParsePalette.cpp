#include "ParsePalette.hpp"

#include <boost/filesystem.hpp>

#include <fstream>

ParsePalette::ParsePalette(std::string palettePath) :
    m_colors(), m_steps(), m_exit(false)
{
    auto path = boost::filesystem::path(palettePath);

    if (boost::filesystem::exists(palettePath))
    {
        auto fs = std::ifstream();
        fs.open(path.generic_string(), std::ios::in);

        if (!fs)
        {
            throw std::runtime_error(
                "Error: palette file [" + 
                path.generic_string() + "] cannot be read");
        }

        uint32_t numPrimamryColors;
        fs >> numPrimamryColors;

        if (numPrimamryColors < 0 || numPrimamryColors > 4)
        {
            throw std::runtime_error(
                "Error: Cannot read palette file: "
                "invalid number of primary colors.");
        }
        

    }
}