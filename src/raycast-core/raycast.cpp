
#include "raycast.h"

namespace rc {

	raycast_engine::raycast_engine(unsigned int screen_size_x, unsigned int screen_size_y,
		unsigned int map_grid_size_x, unsigned int map_grid_size_y, unsigned int grid_factor,
		double field_of_view) {

	}

	raycast_engine::~raycast_engine() {
	}

	// ----------------------------------------- private fns ---------------------------------

	point raycast_engine::emit_and_trace_ray(point first_grid_intersection, int offset_x, int offset_y) {
		return point(0, 0);
	}

	double inline raycast_engine::reverse_fishbowl(double polar_distance) {
		return 0.0;
	}

	bool raycast_engine::outside_map_bounds(const point & pt) {
		return true;
	}

	// ----------------------------------------- public fns ----------------------------------

	void raycast_engine::create_map(bool ** wall_arr,
		texture_index ** left_tex_arr, texture_index ** right_tex_arr,
		texture_index ** front_tex_arr, texture_index ** back_tex_arr) {
	}

	double raycast_engine::get_slice_angle() {
		return 0.0;
	}

	void raycast_engine::set_field_of_view() {
	}

	void raycast_engine::add_wall_texture(graphics::texture wall_texture) {
	}

	void raycast_engine::add_wall_texture(const uint8_t * wall_image, unsigned int image_size) {
	}

	point raycast_engine::find_closest_horizontal_intersection_on_ray(const ray & ray) {
		return point(0, 0);
	}

	point raycast_engine::find_closest_vertical_intersection_on_ray(const ray & ray) {
		return point(0, 0);
	}

	point raycast_engine::find_closest_intersection_on_ray(const ray & ray) {
		return point(0, 0);
	}

	graphics::slice raycast_engine::cast_ray(const ray & player_transform, unsigned int screen_column) {
		return graphics::slice(0, 0, nullptr);
	}

}