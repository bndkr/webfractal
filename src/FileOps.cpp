#include <FileOps.hpp>

namespace fileops
{
	std::shared_ptr<std::ofstream> createBmpHeader(uint32_t const& width, uint32_t const& height, std::string filename)
	{
		// create the file object stream and set up the buffer.
		auto file = std::make_shared<std::ofstream>(std::ofstream(
			filename + ".bmp", std::ios::out | std::ios::binary));

		int total_pixels = width * height;

		/*-------BMP HEADER--------*/
		char id_field[2] = { 'B', 'M' }; // "BM" for bitmap
		char file_size[4] =
		{// file size in bytes. The 56 is the byte size of the header
				 (total_pixels * 3 + 54) & 0x000000ff,
				((total_pixels * 3 + 54) & 0x0000ff00) >> 8,
				((total_pixels * 3 + 54) & 0x00ff0000) >> 16,
				((total_pixels * 3 + 54) & 0xff000000) >> 24
		};
		char app_1[2] = { 0, 0 }; //Application specific
		char app_2[2] = { 0, 0 }; //Application specific
		char offset[4] = { 54, 0, 0, 0 }; // Offset of raw data

		/*-------DIB HEADER--------*/
		char dib_size[4] = { 40, 0, 0, 0 }; //size of the dib header in bytes
		char w[4] =
		{	// width of image in pixels
			 width & 0x000000ff,
			(width & 0x0000ff00) >> 8,
			(width & 0x00ff0000) >> 16,
			(width & 0xff000000) >> 24
		};
		char h[4] =
		{	// height of image in pixels
			 height & 0x000000ff,
			(height & 0x0000ff00) >> 8,
			(height & 0x00ff0000) >> 16,
			(height & 0xff000000) >> 24
		};
		char color_planes[2] = { 1, 0 }; // number of color planes
		char bits_per_pixel[2] = { 24, 0 }; // bits per pixel
		char compression[4]{ 0, 0, 0, 0 }; // no compression.
		char raw_size[4] =
		{ // this is the number of bytes of the raw image data.
			 (total_pixels * 3) & 0x000000ff,
			((total_pixels * 3) & 0x0000ff00) >> 8,
			((total_pixels * 3) & 0x00ff0000) >> 16,
			((total_pixels * 3) & 0xff000000) >> 24
		};
		char print_resolution_1[4] =
		{ // this is really arbitrary, we don't plan on printing the bitmap.
			 2835 & 0x000000ff,
			(2835 & 0x0000ff00) >> 8,
			(2835 & 0x00ff0000) >> 16,
			(2835 & 0xff000000) >> 24
		};
		char print_resolution_2[4] =
		{ // this is really arbitrary, we don't plan on printing the bitmap.
			 2835 & 0x000000ff,
			(2835 & 0x0000ff00) >> 8,
			(2835 & 0x00ff0000) >> 16,
			(2835 & 0xff000000) >> 24
		};
		char palette_colors[4] = { 0, 0, 0, 0 }; //no palette
		char important_colors[4] = { 0, 0, 0, 0 };

		file->write(id_field, 2);
		file->write(file_size, 4);
		file->write(app_1, 2);
		file->write(app_2, 2);
		file->write(offset, 4);
		file->write(dib_size, 4);
		file->write(w, 4);
		file->write(h, 4);
		file->write(color_planes, 2);
		file->write(bits_per_pixel, 2);
		file->write(compression, 4);
		file->write(raw_size, 4);
		file->write(print_resolution_1, 4);
		file->write(print_resolution_2, 4);
		file->write(palette_colors, 4);
		file->write(important_colors, 4);
		return file;
	}
}