#ifndef ROAD_HPP_
#define ROAD_HPP_

#include "Car.hpp"

enum Direction {
	LEFT = 0,
	RIGHT = 1
};

class Road {
private:
	Car* road;
	int direction;
	int length;

public:

	Road();
	~Road();
	void update();
};

#endif /* ROAD_HPP_ */
