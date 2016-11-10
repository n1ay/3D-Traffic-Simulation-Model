#ifndef LANE_HPP_
#define LANE_HPP_

#include <iostream>

enum Direction {
	LEFT = 0,
	RIGHT = 1
};

//forward declaration of Car
class Car;

class Lane {

private:
	Car** lane;
	Car** updateLane;
	int direction;
	int length;

public:

	Lane(int direction, int length);
	~Lane();
	friend class Car;
	friend std::ostream & operator<<(std::ostream &, const Lane &);
	void update();
	void spawnCar();
	void moveCar(int, int);
	Car* getCar(int);
	void removeCar(int);
	void cleanUpdate();
	void lockUpdate();
	int getLength();
	void log();
};

#endif /* LANE_HPP_ */
