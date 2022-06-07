#ifndef PARSE_PALETTE_HPP
#define PARSE_PALETTE_HPP

#include <iostream>

#include <boost/unordered_map.hpp> 

class Palette
{
public:
	Palette(std::string palettePath, uint32_t steps);
    void interpolate(uint32_t color1, uint32_t color2);
    void interpolate(uint32_t color1, uint32_t color2, uint32_t color3);
    void interpolate(uint32_t color1, uint32_t color2, uint32_t color3, uint32_t color4);

	void getColor(uint32_t const& index, uint8_t& red, uint8_t& green, uint8_t& blue);

	void iterationsToColor(float iterations, uint8_t& red, uint8_t& green, uint8_t& blue);

	void printPalette();

	uint32_t m_steps; // number of colors in palette
	uint32_t m_numChannels; // number of colors in palette * 3

	boost::unordered_map<uint32_t, uint32_t> m_colors;
};

#endif