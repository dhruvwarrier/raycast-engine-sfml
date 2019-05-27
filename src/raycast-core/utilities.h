
#ifndef RAYCAST_UTILITIES_H
#define RAYCAST_UTILITIES_H

#include "graphics.h"
#include <functional>
#include <vector>
#include <algorithm>

namespace rc {
	namespace utilities {

		// Sample an input array down into the target size.
		// The downsampler must take an array of T and return some average of the elements.
		template <typename T> T * downsample(const T * input_arr, unsigned int input_size, unsigned int target_size,
			std::function<T(const T * arr_to_be_squashed, unsigned int arr_size)> downsampler) {

			if (target_size > input_size) return nullptr;

			// create target sized arr
			T * downsampled_arr = new T[target_size];
			unsigned int sampled_arr_i = 0;

			// if the sizes are the same, return a copy
			if (input_size == target_size) {
				std::copy(input_arr, input_arr + input_size, downsampled_arr);
				return downsampled_arr;
			}
			
			// lower and higher_incr are the increments at which the input arr will be sampled
			unsigned int lower_incr = input_size / target_size;
			unsigned int higher_incr = lower_incr + 1;

			// the number of times we sample at the lower increment
			unsigned int num_lower_incr = higher_incr * target_size - input_size;

			// sample at lower increments
			for (unsigned int i = 0; i < num_lower_incr * lower_incr; i += lower_incr) {
				downsampled_arr[sampled_arr_i] = downsampler(&input_arr[i], lower_incr);
				sampled_arr_i++;
			}

			// sample at higher increments
			for (unsigned int i = num_lower_incr * lower_incr; i < input_size; i += higher_incr) {
				downsampled_arr[sampled_arr_i] = downsampler(&input_arr[i], higher_incr);
				sampled_arr_i++;
			}

			return downsampled_arr;
		}

		// Interpolate an array up to a larger size.
		// The interpolator must generate num_elems_between elements lying between some lhs and rhs T.
		template <typename T> T * interpolate(const T * input_arr, unsigned int input_size, unsigned int target_size,
			std::function<T *(const T & lhs, const T & rhs, unsigned int num_elems_between)> interpolator) {
			return nullptr;
		}

		// Downsample a 2D array to a smaller size.
		// The downsampler must take an array of ptrs to T and return some average of the elements.
		template <typename T> T * downsample2d(const T * input_arr, unsigned int input_size_x,
			unsigned int input_size_y, unsigned int target_size_x, unsigned int target_size_y,
			std::function<T(const T ** arr_to_be_squashed, unsigned int arr_size)> downsampler) {
			return nullptr;
		}

		// Interpolate a 2D array up to a larger size.
		// The interpolator must generate num_elems_between elements lying between some lhs and rhs T.
		template <typename T> T * interpolate2d(const T * input_arr, unsigned int input_size_x,
			unsigned int input_size_y, unsigned int target_size_x, unsigned int target_size_y,
			std::function<T *(const T & lhs, const T & rhs, unsigned int num_elems_between)> interpolator) {
			return nullptr;
		}
	}
}

#endif // RAYCAST_UTILITIES_H