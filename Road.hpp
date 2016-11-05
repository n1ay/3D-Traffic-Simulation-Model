#ifndef ROAD_HPP_
#define ROAD_HPP_

#include <iostream>

enum Direction {
	LEFT = 0,
	RIGHT = 1
};

//forward declaration of Car
class Car;

class Road {

private:
	Car** road;
	int direction;
	int length;

public:

	Road(int direction);
	~Road();
	friend std::ostream & operator<<(std::ostream &, const Road &);
	void update();
	void spawnCar();
	void moveCar(int, int);
	Car* getCar(int);
	void removeCar(int);
};

#endif /* ROAD_HPP_ */
