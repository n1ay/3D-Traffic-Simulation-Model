#include "Car.hpp"
#include "Road.hpp"
#include "World.hpp"


Road::Road(int direction):
	direction(direction), length(World::length)
{
	road = new Car* [World::length];
}

Road::~Road() {
	for(int i=0; i<length; ++i)
		delete road[i];
	delete [] road;
}

void Road::update() {
	for(int i=World::length; i>=0; --i) {
		if(road[i] != nullptr)
			road[i] -> update();
	}
}

void Road::spawnCar() {
	road[0] = new Car(this);
}

std::ostream & operator<<(std::ostream & ostr, const Road & road) {
	if(road.direction == Direction::LEFT)
		ostr<<"direction: <-\n";
	else
		ostr<<"direction: ->\n";
	for(int i=0; i<road.length; i++)
		if(road.road[i] == nullptr)
			ostr<<"[]";
		else
			ostr<<(*(road.road[i]));
	return ostr;
}

Car* Road::getCar(int position) {
	return road[position];
}

void Road::moveCar(int from, int to) {
	if(from == to)
		return;
	road[to] = road[from];
	road[from] = nullptr;
}

void Road::removeCar(int position) {
	road[position] = nullptr;
}
