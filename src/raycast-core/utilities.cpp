
#include "utilities.h"
#include <utility>
using std::pair;

namespace rc {
	namespace utilities {

		// sample an input array down into the target size
		graphics::color * downsample(const graphics::color * input_arr, unsigned int input_size, unsigned int target_size) {
			return nullptr;
		}

		// interpolate an array up to a larger size
		graphics::color * interpolate(const graphics::color * input_arr, unsigned int input_size, unsigned int target_size) {
			return nullptr;
		}

		// downsample a 2D array to a smaller size
		graphics::color * downsample2d(const graphics::color * input_arr, unsigned int input_size_x, unsigned int input_size_y, 
			unsigned int target_size_x, unsigned int target_size_y) {
			return nullptr;
		}

		// interpolate a 2D array up to a larger size
		graphics::color * interpolate2d(const graphics::color * input_arr, unsigned int input_size_x, unsigned int input_size_y, 
			unsigned int target_size_x, unsigned int target_size_y) {
			return nullptr;
		}
	}
}