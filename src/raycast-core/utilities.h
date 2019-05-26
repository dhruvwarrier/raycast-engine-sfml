
#ifndef RAYCAST_UTILITIES_H
#define RAYCAST_UTILITIES_H

#include "graphics.h"

namespace rc {
	namespace utilities {

		// sample an input array down into the target size
		extern graphics::color * downsample(const graphics::color * input_arr, unsigned int input_size, unsigned int target_size);

		// interpolate an array up to a larger size
		extern graphics::color * interpolate(const graphics::color * input_arr, unsigned int input_size, unsigned int target_size);

		extern graphics::color * downsample2d(const graphics::color * input_arr, unsigned int input_size_x, unsigned int input_size_y,
			unsigned int target_size_x, unsigned int target_size_y);

		extern graphics::color * interpolate2d(const graphics::color * input_arr, unsigned int input_size_x, unsigned int input_size_y,
			unsigned int target_size_x, unsigned int target_size_y);
	}
}

#endif // RAYCAST_UTILITIES_H