
#ifndef RAYCAST_UTILITIES_H
#define RAYCAST_UTILITIES_H

#include "graphics.h"

namespace rc {
	namespace utilities {

		// sample an input array down into the target size
		template <typename T> T * downsample(const T * input_arr, unsigned int input_size, unsigned int target_size) {
			return nullptr;
		}

		// interpolate an array up to a larger size
		template <typename T> T * interpolate(const T * input_arr, unsigned int input_size, unsigned int target_size) {
			return nullptr;
		}

		// downsample a 2D array to a smaller size
		template <typename T> T * downsample2d(const T * input_arr, unsigned int input_size_x, unsigned int input_size_y,
			unsigned int target_size_x, unsigned int target_size_y) {
			return nullptr;
		}

		// interpolate a 2D array up to a larger size
		template <typename T> T * interpolate2d(const T * input_arr, unsigned int input_size_x, unsigned int input_size_y,
			unsigned int target_size_x, unsigned int target_size_y) {
			return nullptr;
		}
	}
}

#endif // RAYCAST_UTILITIES_H