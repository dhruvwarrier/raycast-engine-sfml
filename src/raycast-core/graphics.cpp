#include "graphics.h"
#include "utilities.h"
#include <functional>

namespace rc {
	namespace graphics {

		texture::texture(unsigned int texture_square_size) {
			square_size = texture_square_size;
			// color_arr is a flattened 2D array of colors
			color_arr = new color[square_size * square_size];
		}

		texture::texture(const texture & rhs) {
			copy_from(rhs);
		}

		texture::~texture() {
			delete_color_arr();
		}

		// ------------------------------------------------------------------------------------------
		// ------------------------------------ private fns -----------------------------------------
		// ------------------------------------------------------------------------------------------

		void texture::delete_color_arr() {
			// delete the array
			delete[] color_arr;
			color_arr = nullptr;
		}

		uint8_t * texture::create_rgba_array_from_color_array(const color * color_arr, unsigned int size) {

			uint8_t * rgba_arr = new uint8_t[size * 4];

			for (unsigned int i = 0; i < size; ++i) {
				rgba_arr[i * 4] = color_arr[i].r;
				rgba_arr[i * 4 + 1] = color_arr[i].g;
				rgba_arr[i * 4 + 2] = color_arr[i].b;
				rgba_arr[i * 4 + 3] = color_arr[i].a;
			}

			return rgba_arr;
		}
		color * texture::create_color_array_from_rgba_array(const uint8_t * rgba_arr, unsigned int size) {

			color * color_arr = new color[size / 4];
			
			for (unsigned int i = 0; i < size; i += 4) {
				color_arr[i / 4] = color(rgba_arr[i],
					rgba_arr[i + 1], rgba_arr[i + 2], rgba_arr[i + 3]);
			}

			return color_arr;
		}

		// ------------------------------------------------------------------------------------------
		// ---------------------------------- public interface --------------------------------------
		// ------------------------------------------------------------------------------------------

		void texture::load_from_rgba_array(const uint8_t * image_rgba_arr, unsigned int image_size) {

			unsigned int num_bytes = image_size * image_size * 4;
			
			// create the color array from the rgba array
			color * temp_color_arr = create_color_array_from_rgba_array(image_rgba_arr, num_bytes);

			delete_color_arr(); // delete in preparation to replace

			// downsample or interpolate to target size, if required
			if (square_size != image_size) {

				color * new_color_arr;

				// temporary so that it compiles
				std::function<color *(const color & lhs, const color & rhs, unsigned int num_elems_between)> interpolator;
				std::function<color(const color ** arr_to_be_squashed, unsigned int arr_size)> downsampler;

				if (image_size > square_size) {
					// downsample the color array to bring down to size
					new_color_arr = utilities::downsample2d(temp_color_arr, image_size, image_size, square_size, square_size, downsampler);
				}
				else {
					// interpolate the color array to bring up to size
					new_color_arr = utilities::interpolate2d(temp_color_arr, image_size, image_size, square_size, square_size, interpolator);
				}

				delete[] temp_color_arr;
				color_arr = new_color_arr;
			}
			else {
				// no downsampling or interpolating required
				color_arr = temp_color_arr;
			}
		}

		void texture::copy_from(const texture & rhs) {

			square_size = rhs.square_size;

			const color * rhs_color_arr = rhs.get_color_array();
			color * lhs_color_arr;

			// if rhs has a color array, copy it
			if (rhs_color_arr != nullptr) {

				// copy over the color array from rhs
				lhs_color_arr = new color[rhs.get_num_pixels()];

				for (unsigned int i = 0; i < rhs.get_num_pixels(); ++i) {
					lhs_color_arr[i] = color(rhs_color_arr[i].r,
						rhs_color_arr[i].g, rhs_color_arr[i].b, rhs_color_arr[i].a);
				}
			}
			else {
				// else create a blank color array
				lhs_color_arr = nullptr;
			}

			// delete my color arr
			delete_color_arr();
			// reassign my color arr
			color_arr = lhs_color_arr;
		}

		const color * texture::get_color_array() const {
			return color_arr;
		}

		const unsigned int texture::get_num_pixels() const {
			return square_size * square_size;
		}

		uint8_t * texture::get_rgba_array() {
			return create_rgba_array_from_color_array(color_arr, square_size);
		}
	}
}

