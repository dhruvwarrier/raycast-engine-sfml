#include <SFML/Graphics.hpp>
#include "raycast-core/utilities.h"
#include <iostream>
#include "raycast-core/utilities.h"
#include <functional>

int main() {

	double* arr = new double[4];
	arr[0] = 1.0;
	arr[1] = 2.0;
	arr[2] = 3.0;
	arr[3] = 4.0;

	double * lla = rc::utilities::interpolate<double>(arr, 4, 20, [](const double & lhs, const double & rhs, unsigned int num_elems) {
		double dx = (rhs - lhs)/(num_elems + 1);
		double * inbtwn = new double[num_elems];
		for (unsigned int i = 0; i < num_elems; ++i) {
			inbtwn[i] = lhs + (i + 1)*dx;
		}
		return inbtwn;
	});

	for (unsigned int i = 0; i < 20; ++i) std::cout << lla[i] << std::endl;

	delete[] lla;
	delete[] arr;

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		window.display();
	}

	return 0;
}