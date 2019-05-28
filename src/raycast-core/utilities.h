
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
			// eg. if lower_incr = 2, every 2 elements will be squashed into one
			unsigned int lower_incr = input_size / target_size;
			unsigned int higher_incr = lower_incr + 1;

			// the number of times we sample at the lower increment
			unsigned int num_lower_incr = higher_incr * target_size - input_size;

			// sample at lower increments
			for (unsigned int i = 0; i < num_lower_incr * lower_incr; i += lower_incr) {
				downsampled_arr[sampled_arr_i++] = downsampler(&input_arr[i], lower_incr);
			}

			// sample at higher increments
			for (unsigned int i = num_lower_incr * lower_incr; i < input_size; i += higher_incr) {
				downsampled_arr[sampled_arr_i++] = downsampler(&input_arr[i], higher_incr);
			}

			return downsampled_arr;
		}

		// Interpolate an array up to a larger size.
		// The interpolator must generate num_elems_between elements lying between some lhs and rhs T.
		template <typename T> T * interpolate(const T * input_arr, unsigned int input_size, unsigned int target_size,
			std::function<T *(const T & lhs, const T & rhs, unsigned int num_elems_between)> interpolator) {

			if (target_size < input_size) return nullptr;

			// create target sized arr
			T * interpolated_arr = new T[target_size];
			unsigned int interpolated_arr_i = 0;

			// if the sizes are the same, return a copy
			if (input_size == target_size) {
				std::copy(input_arr, input_arr + input_size, interpolated_arr);
				return interpolated_arr;
			}

			// lower and higher_factor are the factors with which the elements will be augmented
			// eg. if lower_factor = 2, 2 elements will be inserted for every element
			unsigned int lower_factor = (target_size - input_size) / (input_size - 1);
			unsigned int higher_factor = lower_factor + 1;

			// the number of times to interpolate at the lower factor
			unsigned int num_lower_factor = higher_factor * (input_size - 1) + input_size - target_size;

			// utility fn to add interpolated elements to the array
			auto add_interpolated_elements = [&](unsigned int elem_index, unsigned int num_elements_rqd) {
				T * interpolated_elems = interpolator(input_arr[elem_index], input_arr[elem_index + 1], num_elements_rqd);
				for (unsigned int j = 0; j < num_elements_rqd; ++j) {
					// add each element in interpolated_elems to interpolated_arr
					interpolated_arr[interpolated_arr_i++] = interpolated_elems[j];
				}
				delete[] interpolated_elems;
			};

			// interpolate at the lower factor
			for (unsigned int i = 0; i < num_lower_factor; ++i) {
				// add ith element to interpolated_arr
				interpolated_arr[interpolated_arr_i++] = input_arr[i];
				// generate the remaining elements between this and the next element
				add_interpolated_elements(i, lower_factor);
			}

			// interpolate at the higher factor
			for (unsigned int i = num_lower_factor; i < input_size - 1; ++i) {
				// add ith element to interpolated_arr
				interpolated_arr[interpolated_arr_i++] = input_arr[i];
				// generate the remaining elements between this and the next element
				add_interpolated_elements(i, higher_factor);
			}

			// add last element
			interpolated_arr[interpolated_arr_i++] = input_arr[input_size - 1];

			return interpolated_arr;
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