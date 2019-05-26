
#ifndef  RAYCAST_GRAPHICS_H
#define RAYCAST_GRAPHICS_H

#include <stdint.h>

namespace rc {
	namespace graphics {

		struct color {
			uint8_t r, g, b, a;
			color(uint8_t _r, uint8_t _g,
				uint8_t _b, uint8_t _a = 255) : r(_r), g(_g), b(_b), a(_a) {
			}
			color() {
				r = g = b = a = 0;
			}
		};

		// if slice does not exist at this location, size = location = INT_MAX
		struct slice {
			// size along screen Y
			unsigned int size;

			// location of slice along screen X
			unsigned int location;

			// array of color to be rendered for this slice (exactly _size in size)
			const color * texture_data;

			slice(unsigned int _size, unsigned int _location, const color * _texture_data) : size(_size),
				location(_location), texture_data(_texture_data) {
			}
		};

		class texture {
		private:

			// size of single dimension of color_arr
			unsigned int square_size;
			// 2D color array of all colors that make up this texture
			color * color_arr;

			uint8_t * create_rgba_array_from_color_array(const color * color_arr, unsigned int size);
			color * create_color_array_from_rgba_array(const uint8_t * rgba_arr, unsigned int size);

			void delete_color_arr();

		public:

			// square_size should be at most 2^(grid_factor)
			// higher resolutions will not be distinguishable
			texture(unsigned int texture_square_size);

			// creates a deep copy of this texture
			texture(const texture & rhs);

			virtual ~texture();

			// image_rgba_arr here is an array of RGBA pixels made of 8 bit int components
			// image_size is the size of the square image in pixels (i.e. image_rgb_arr 
			// is 4*image_size^2 in size)
			// if image_size is != texture size then the image is downsampled or interpolated
			// the largest square part of the image is loaded as the texture
			void load_from_rgba_array(const uint8_t * image_rgba_arr, unsigned int image_size);

			// creates a deep copy of this texture
			void copy_from(const texture & rhs);

			// get the color array
			const color * get_color_array() const;

			// num_pixels = square_size * square_size
			const unsigned int get_num_pixels() const;

			// get an rgba array from the color array
			uint8_t * get_rgba_array();
		};
	}
}


#endif // RAYCAST_GRAPHICS_H
