#include "Road.hpp"
#include "World.cpp"

class Road {
private:
	Car* road;
	Direction direction;

public:

	Road(int direction) {
		this->direction = direction;
		road = new Car [World::length];
	}

	~Road() {
		delete [] road;
	}

	void update() {
		for(int i=0; i<World::length; ++i) {
			road[i].update();
		}
	}
};



