#ifndef ROAD_HPP_
#define ROAD_HPP_

enum Direction {
	LEFT = 0,
	RIGHT = 1
};

//forward declaration of Car
class Car;

class Road {
private:
	Car* road;
	int direction;
	int length;

public:

	Road(int direction);
	~Road();
	void update();
};

#endif /* ROAD_HPP_ */
