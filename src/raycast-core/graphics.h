
#ifndef  RAYCAST_GRAPHICS_H
#define RAYCAST_GRAPHICS_H

#include <stdint.h>

namespace rc 
{
	// if slice does not exist at this location, size = location = INT_MAX
	struct slice
	{
		int size, location;
		// additional texture info can be inserted here later
		slice(int _size, int _location) : size(_size), location(_location) {}
	};

	struct pixel_color
	{
		uint8_t r, g, b, a;
		pixel_color(uint8_t _r, uint8_t _g,
			uint8_t _b, uint8_t _a = 255) : r(_r), g(_g), b(_b), a(_a) {}
	};

	class texture
	{
	private:

		// size of 2d square matrix color_arr
		unsigned int texture_res;
		// 2D color array of all colors that make up this texture
		pixel_color ** color_arr;

	public:

		// texture_res should be at most 2^(grid_factor)
		// higher resolutions will not be distinguishable
		texture(unsigned int texture_res);

		texture(const texture & rhs);

		// image here is an array of RGBA pixels made of 8 bit int components
		// image_size is the size of the square image in pixels
		// if image_size is larger than texture resolution then the image is downsampled
		// the largest square part of the image is loaded as the texture
		void load_from_image(const uint8_t * image, unsigned int image_size);

		virtual ~texture();

		void copy_from(const texture & rhs);

		// return color_arr
		const pixel_color ** get_color_array();
	};
}


#endif // RAYCAST_GRAPHICS_H
