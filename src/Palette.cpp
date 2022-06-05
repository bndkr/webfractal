#include "Palette.hpp"

#include <boost/filesystem.hpp>

#include <fstream>

Palette::Palette(std::string palettePath, uint32_t steps) :
	m_steps(steps), m_numChannels(steps * 3), m_colors()
{
    auto path = boost::filesystem::path(palettePath);

    if (boost::filesystem::exists(palettePath))
    {
        auto fs = std::ifstream();
        fs.open(path.generic_string(), std::ios::in);

        if (!fs)
        {
            throw std::runtime_error(
                "palette file [" + 
                path.generic_string() + "] cannot be read");
        }

        uint32_t numPrimamryColors;
        fs >> numPrimamryColors;

        if (numPrimamryColors < 1 || numPrimamryColors > 4)
        {
            throw std::runtime_error("Palette config file "
                "parser: invalid number of primary colors");
        }
        auto colors = std::vector<uint32_t>();
        for (size_t i = 0; i < numPrimamryColors; i++)
        {
            uint32_t red, green, blue, color;
            fs >> red;
            fs >> green;
            fs >> blue;
            if (red < 0 || red > 0xff)
            {
                throw std::runtime_error("Palette config file "
                "parser: invalid red color " + std::to_string(red));
            }
            if (blue < 0 || blue > 0xff)
            {
                throw std::runtime_error("Palette config file "
                "parser: invalid blue color " + std::to_string(blue));
            }
            if (green < 0 || green > 0xff)
            {
                throw std::runtime_error("Palette config file "
                "parser: invalid green color " + std::to_string(green));
            }

            color = blue + (green << 8) + (red << 16);

            colors.push_back(color);
        }

        if (colors.size() == 2)
        {
            interpolate(colors[0], colors[1]);
        }
        if (colors.size() == 3)
        {
            interpolate(colors[0], colors[1], colors[2]);
        }
        if (colors.size() == 4)
        {
            interpolate(colors[0], colors[1], colors[2], colors[3]);
        }
    }
    else
    {
        throw std::runtime_error("Cannot find palette file path (" + palettePath + ")");
    }
}

void Palette::interpolate(uint32_t color1, uint32_t color2)
{
	double half = m_steps / 2;
	// blue channel
	uint8_t blue1 = color1 & 0x0000ff;
	uint8_t blue2 = color2 & 0x0000ff;
	// green channel
	uint8_t green1 = (color1 & 0x00ff00) >> 8;
	uint8_t green2 = (color2 & 0x00ff00) >> 8;
	// red channel
	uint8_t red1 = (color1 & 0xff0000) >> 16;
	uint8_t red2 = (color2 & 0xff0000) >> 16;
	uint32_t i = 0;
	for (i; i < half; i++)
	{
		m_colors[i * 3] = blue1 * ((half - i) / half) + blue2 * (i / half);
		m_colors[i * 3 + 1] = green1 * ((half - i) / half) + green2 * (i / half);
		m_colors[i * 3 + 2] = red1 * ((half - i) / half) + red2 * (i / half);

		m_colors[i * 3 + (m_steps * 3) / 2] = blue2 * ((half - i) / half) + blue1 * (i / half);
		m_colors[i * 3 + 1 + (m_steps * 3) / 2] = green2 * ((half - i) / half) + green1 * (i / half);
		m_colors[i * 3 + 2 + (m_steps * 3) / 2] = red2 * ((half - i) / half) + red1 * (i / half);
	}
}
void Palette::interpolate(uint32_t color1, uint32_t color2, uint32_t color3)
{
double third = m_steps / 3;

	// blue channel
	uint8_t blue1 = color1 & 0x0000ff;
	uint8_t blue2 = color2 & 0x0000ff;
	uint8_t blue3 = color3 & 0x0000ff;
	// green channel
	uint8_t green1 = (color1 & 0x00ff00) >> 8;
	uint8_t green2 = (color2 & 0x00ff00) >> 8;
	uint8_t green3 = (color3 & 0x00ff00) >> 8;
	// red channel
	uint8_t red1 = (color1 & 0xff0000) >> 16;
	uint8_t red2 = (color2 & 0xff0000) >> 16;
	uint8_t red3 = (color3 & 0xff0000) >> 16;
	uint32_t i = 0;
	for (i; i < third; i++)
	{
		m_colors[i * 3] = blue1 * ((third - i) / third) + blue2 * (i / third);
		m_colors[i * 3 + 1] = green1 * ((third - i) / third) + green2 * (i / third);
		m_colors[i * 3 + 2] = red1 * ((third - i) / third) + red2 * (i / third);

		m_colors[i * 3 + (m_steps * 3) / 3] = blue2 * ((third - i) / third) + blue3 * (i / third);
		m_colors[i * 3 + 1 + (m_steps * 3) / 3] = green2 * ((third - i) / third) + green3 * (i / third);
		m_colors[i * 3 + 2 + (m_steps * 3) / 3] = red2 * ((third - i) / third) + red3 * (i / third);

		m_colors[i * 3 + (m_steps * 6) / 3] = blue3 * ((third - i) / third) + blue1 * (i / third);
		m_colors[i * 3 + 1 + (m_steps * 6) / 3] = green3 * ((third - i) / third) + green1 * (i / third);
		m_colors[i * 3 + 2 + (m_steps * 6) / 3] = red3 * ((third - i) / third) + red1 * (i / third);
	}
}
void Palette::interpolate(uint32_t color1, uint32_t color2, uint32_t color3, uint32_t color4)
{
    double fourth = m_steps / 4;

	// blue channel
	uint8_t blue1 = color1 & 0x0000ff;
	uint8_t blue2 = color2 & 0x0000ff;
	uint8_t blue3 = color3 & 0x0000ff;
	uint8_t blue4 = color4 & 0x0000ff;
	// green channel
	uint8_t green1 = (color1 & 0x00ff00) >> 8;
	uint8_t green2 = (color2 & 0x00ff00) >> 8;
	uint8_t green3 = (color3 & 0x00ff00) >> 8;
	uint8_t green4 = (color4 & 0x00ff00) >> 8;
	// red channel
	uint8_t red1 = (color1 & 0xff0000) >> 16;
	uint8_t red2 = (color2 & 0xff0000) >> 16;
	uint8_t red3 = (color3 & 0xff0000) >> 16;
	uint8_t red4 = (color4 & 0xff0000) >> 16;
	uint32_t i = 0;
	for (i; i < fourth; i++)
	{
		m_colors[i * 3] = blue1 * ((fourth - i) / fourth) + blue2 * (i / fourth);
		m_colors[i * 3 + 1] = green1 * ((fourth - i) / fourth) + green2 * (i / fourth);
		m_colors[i * 3 + 2] = red1 * ((fourth - i) / fourth) + red2 * (i / fourth);

		m_colors[i * 3 + (m_steps * 3) / 4] = blue2 * ((fourth - i) / fourth) + blue3 * (i / fourth);
		m_colors[i * 3 + 1 + (m_steps * 3) / 4] = green2 * ((fourth - i) / fourth) + green3 * (i / fourth);
		m_colors[i * 3 + 2 + (m_steps * 3) / 4] = red2 * ((fourth - i) / fourth) + red3 * (i / fourth);

		m_colors[i * 3 + (m_steps * 6) / 4] = blue3 * ((fourth - i) / fourth) + blue4 * (i / fourth);
		m_colors[i * 3 + 1 + (m_steps * 6) / 4] = green3 * ((fourth - i) / fourth) + green4 * (i / fourth);
		m_colors[i * 3 + 2 + (m_steps * 6) / 4] = red3 * ((fourth - i) / fourth) + red4 * (i / fourth);

		m_colors[i * 3 + (m_steps * 9) / 4] = blue4 * ((fourth - i) / fourth) + blue1 * (i / fourth);
		m_colors[i * 3 + 1 + (m_steps * 9) / 4] = green4 * ((fourth - i) / fourth) + green1 * (i / fourth);
		m_colors[i * 3 + 2 + (m_steps * 9) / 4] = red4 * ((fourth - i) / fourth) + red1 * (i / fourth);
	}
}

Color Palette::getColor(uint32_t const& index)
{
    return Color {m_colors[index * 3 + 2], m_colors[index * 3 + 1], m_colors[index * 3]};
}

void Palette::printPalette()
{
    for (size_t i = 0; i < m_steps; i++)
    {
		Color c = getColor(i);
		std::cout << "c: " << i << " r: " 
			<< c.red << " g: " << c.green << " b: "
			<< c.blue << std::endl;
    }
}

Color Palette::iterationsToColor(float iterations)
{
	// TODO: inner color
	if (iterations == -1.0f)
	{
		return Color{0, 0, 0};
	}
	uint32_t step = static_cast<uint32_t>(iterations);
	auto gradient = iterations - step; // how 'inbetween' the color is, between 0 and 1
	
	step = step % m_steps; // m_steps is the number of colors in the palette

	auto baseColor = getColor(step);
	auto newColor = getColor((step + 1) % m_steps);
	Color inbetweenColor({});
	
	// interpolate between baseColor and newColor
	inbetweenColor.red = 
		baseColor.red + (newColor.red - baseColor.red) * gradient;

	inbetweenColor.blue = 
		baseColor.blue + (newColor.blue - baseColor.blue) * gradient;

	inbetweenColor.green =
		 baseColor.green + (newColor.green - baseColor.green) * gradient;

	return inbetweenColor;
}