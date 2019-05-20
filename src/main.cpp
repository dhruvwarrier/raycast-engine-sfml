#include <SFML/Graphics.hpp>
#include "raycast-core/map_data.h"
#include "raycast-core/raycast.h"

int MAP_DATA[MAP_SIZE_X][MAP_SIZE_Y];

volatile double player_angle = 0;
volatile int player_x_pos = 96;
volatile int player_y_pos = 96;
int increment = 11;

void config_map();

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "Raycast engine");

	config_map();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) 
			{
				switch (event.key.code) 
				{
					case sf::Keyboard::Up:
						player_y_pos = player_y_pos - increment * sind(player_angle);
						player_x_pos = player_x_pos + increment * cosd(player_angle);
						break;

					case sf::Keyboard::Down:
						player_y_pos = player_y_pos + increment * sind(player_angle);
						player_x_pos = player_x_pos - increment * cosd(player_angle);
						break;

					case sf::Keyboard::Right:
						player_angle -= 50 * RAY_ANGLE_INC;
						break;

					case sf::Keyboard::Left:
						player_angle += 50 * RAY_ANGLE_INC;
						break;

					default: break;
				}
			}
		}

		// wrap around player_angle to keep it within the bounds of 0 - 360
		if (player_angle < 0.0) player_angle += 360.0;
		else if (player_angle > 360.0) player_angle -= 360.0;

		window.clear();

		sf::RectangleShape ceiling_and_floor(sf::Vector2f(SCREEN_SIZE_X, SCREEN_SIZE_Y / 2));

		ceiling_and_floor.setFillColor(sf::Color::White);
		ceiling_and_floor.setPosition(0, 0);
		window.draw(ceiling_and_floor);

		ceiling_and_floor.setFillColor(sf::Color(192, 192, 192));
		ceiling_and_floor.setPosition(0, SCREEN_SIZE_Y / 2);
		window.draw(ceiling_and_floor);

		for (int i = 0; i < SCREEN_SIZE_X; ++i)
		{
			slice_info this_slice = cast_ray(player_x_pos, player_y_pos, player_angle, i);
			if (this_slice.size != INT_MAX) 
			{
				sf::Vertex slice_line[] = 
				{
					sf::Vertex(sf::Vector2f(i, this_slice.location), sf::Color::Blue),
					sf::Vertex(sf::Vector2f(i, this_slice.location + this_slice.size - 1), sf::Color::Blue)
				};

				window.draw(slice_line, 2, sf::Lines);
			}
		}

		window.display();
	}

	return 0;
}

void config_map() {

	// initializes the map with a small maze
	// map.PNG is an image of this map

	for (int i = 0; i < MAP_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {
			MAP_DATA[i][j] = 0;
		}
	}

	MAP_DATA[0][0] = 1;
	MAP_DATA[1][0] = 1;
	MAP_DATA[2][0] = 1;
	MAP_DATA[3][0] = 1;
	MAP_DATA[4][0] = 1;
	MAP_DATA[5][0] = 1;
	MAP_DATA[6][0] = 1;
	MAP_DATA[7][0] = 1;
	MAP_DATA[11][0] = 1;
	MAP_DATA[14][0] = 1;

	MAP_DATA[7][1] = 1;
	MAP_DATA[11][1] = 1;
	MAP_DATA[14][1] = 1;

	MAP_DATA[0][2] = 1;
	MAP_DATA[1][2] = 1;
	MAP_DATA[2][2] = 1;
	MAP_DATA[3][2] = 1;
	MAP_DATA[4][2] = 1;
	MAP_DATA[5][2] = 1;
	MAP_DATA[7][2] = 1;
	MAP_DATA[11][2] = 1;
	MAP_DATA[14][2] = 1;

	MAP_DATA[5][3] = 1;
	MAP_DATA[7][3] = 1;
	MAP_DATA[11][3] = 1;
	MAP_DATA[14][3] = 1;

	MAP_DATA[5][4] = 1;
	MAP_DATA[7][4] = 1;
	MAP_DATA[11][4] = 1;
	MAP_DATA[14][4] = 1;

	MAP_DATA[5][5] = 1;
	MAP_DATA[7][5] = 1;
	MAP_DATA[11][5] = 1;
	MAP_DATA[14][5] = 1;

	MAP_DATA[5][6] = 1;
	MAP_DATA[7][6] = 1;
	MAP_DATA[8][6] = 1;
	MAP_DATA[11][6] = 1;
	MAP_DATA[14][6] = 1;

	MAP_DATA[0][9] = 1;
	MAP_DATA[1][9] = 1;
	MAP_DATA[2][9] = 1;
	MAP_DATA[3][9] = 1;
	MAP_DATA[4][9] = 1;
	MAP_DATA[5][9] = 1;
	MAP_DATA[6][9] = 1;
	MAP_DATA[7][9] = 1;
	MAP_DATA[8][9] = 1;
	MAP_DATA[9][9] = 1;
	MAP_DATA[10][9] = 1;
	MAP_DATA[11][9] = 1;
	MAP_DATA[12][9] = 1;
	MAP_DATA[13][9] = 1;
}