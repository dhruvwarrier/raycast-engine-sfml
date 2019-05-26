
#ifndef RAYCAST_H
#define RAYCAST_H

#include <utility> 
using std::pair;
#include <vector>
#include "map_node.h"
#include "graphics.h"

namespace rc {

	// if point is out of map bounds, x = y = INT_MAX
	struct point {
		int x, y;
		point(int _x, int _y) : x(_x), y(_y) {}
	};

	// if grid point is out of map bounds, x = y = INT_MAX
	struct grid_point {
		int x, y;
		grid_point(int _x, int _y) : x(_x), y(_y) {}
		grid_point(point pt, int grid_factor) : x(pt.x >> grid_factor), y(pt.y >> grid_factor) {}
	};

	struct ray {
		point origin;
		double angle;
		ray(point _origin, double _angle) : origin(_origin), angle(_angle) {}
	};

	class raycast_engine {
	private:

		// emits a ray from first intersection with the grid, and traces it until it hits either a wall or goes out of bounds
		// if the ray goes out of bounds, return point(INT_MAX, INT_MAX)
		// else return the unit coordinates of the location where wall was found
		point emit_and_trace_ray(point first_grid_intersection, int offset_x, int offset_y);

		// utility fn to convert a polar distance to a cartesian distance
		double inline reverse_fishbowl(double polar_distance);

		// returns whether pt is out of map bounds or not
		bool outside_map_bounds(const point & pt);

		// screen dimensions
		unsigned int SCREEN_SIZE_X, SCREEN_SIZE_Y;

		// map grid dimensions
		unsigned int GRID_SIZE_X, GRID_SIZE_Y;

		// 1 grid block = 2^(GRID_FACTOR) player coords
		unsigned int grid_factor;

		// camera field of view in degrees
		double fov;

		map_node ** MAP_DATA;

		// array of all textures used by the engine
		std::vector<graphics::texture> WALL_TEXTURES;

	public:

		raycast_engine(unsigned int screen_size_x, unsigned int screen_size_y,
			unsigned int map_grid_size_x, unsigned int map_grid_size_y, unsigned int grid_factor,
			double field_of_view);

		virtual ~raycast_engine();

		// --------------------------------- engine initialization ---------------------------------

		// adds texture to array of renderable textures
		void add_wall_texture(graphics::texture wall_texture);

		// creates a texture from the image, and adds it to array of 
		// renderable textures, at full image resolution
		void add_wall_texture(const uint8_t * wall_image, unsigned int image_size);

		// the sizes of each of these arrays must be map_grid_size_x * map_grid_size_y.
		// texture_index is the index into WALL_TEXTURES where the texture for this face of the wall can be found.
		// left, right, front and back are each face of the wall.
		// WALL_TEXTURES must be initialized before creating the map!
		void create_map(bool ** wall_arr, texture_index ** left_tex_arr, texture_index ** right_tex_arr,
			texture_index ** front_tex_arr, texture_index ** back_tex_arr);

		// return angle subtended by a single slice at the player position
		double get_slice_angle();

		// set camera field of view
		void set_field_of_view();

		// ----------------------------------------- ray casting -----------------------------------

		// finds the closest horizontal intersection with the grid along this ray in player coords
		point find_closest_horizontal_intersection_on_ray(const ray & ray);

		// finds the closest vertical intersection with the grid along this ray in player coords
		point find_closest_vertical_intersection_on_ray(const ray & ray);

		// finds the closest intersection, horizontal or vertical, along this ray in player coords
		point find_closest_intersection_on_ray(const ray & ray);

		// casts a ray that strikes the screen column, originating at the player origin,
		// with the field of view centred around the player angle.
		// returns the slice information (size, location, and texture data) to render the slice with.
		// If wall is not found along this ray returns slice(INT_MAX, INT_MAX, nullptr)
		graphics::slice cast_ray(const ray & player_transform, unsigned int screen_column);
	};
}

#endif // RAYCAST_H