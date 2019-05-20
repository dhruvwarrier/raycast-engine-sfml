
#ifndef RAYCAST_H
#define RAYCAST_H

#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <SFML/graphics.hpp>

#define SCREEN_SIZE_X sf::VideoMode::getFullscreenModes()[0].width
#define SCREEN_SIZE_Y sf::VideoMode::getFullscreenModes()[0].height
#define FOV 60.0
#define RAY_ANGLE_INC (FOV/SCREEN_SIZE_X)

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#define sind(x) (sin((x) * M_PI / 180))
#define cosd(x) (cos((x) * M_PI / 180))
#define tand(x) (tan((x) * M_PI / 180))

// if point is out of map bounds, x = y = INT_MAX
struct point {
	int x;
	int y;
	point(int _x, int _y) : x(_x), y(_y) {}
};

// if grid point is out of map bounds, x = y = INT_MAX
struct grid_point {
	int x;
	int y;
	grid_point(int _x, int _y) : x(_x), y(_y) {}
};

// if slice does not exist at this location, size = location = INT_MAX
struct slice_info {
	int size;
	int location;
	// additional texture info can be inserted here later
	slice_info(int _size, int _location) : size(_size), location(_location) {}
};

point find_closest_horizontal_wall_intersection(int playerX, int playerY);

point find_closest_vertical_wall_intersection(int playerX, int playerY);

// if no wall exists at this ray, returns 0
double find_closest_distance_to_wall(int playerX, int playerY, point& horiz_intersection, point& vert_intersection);

slice_info cast_ray(int playerX, int playerY, double player_angle, int screen_column);

#endif // RAYCAST_H