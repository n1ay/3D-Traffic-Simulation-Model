#include "Car.hpp"
#include "Road.hpp"
#include "World.hpp"


Road::Road(int direction):
	direction(direction), length(World::length)
{
	road = new Car [World::length];
}

Road::~Road() {
	delete [] road;
}

void Road::update() {
	for(int i=0; i<World::length; ++i) {
		road[i].update();
	}
}



