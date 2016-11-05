#include "Car.hpp"
#include "Road.hpp"
#include "World.hpp"
#include <cstdlib>

Car::Car(Road* road):
	road(road), position(0), velocity(rand()%(World::maxVelocity+1))
{}

Car::Car():
	road(nullptr), position(-1), velocity(-1)
{}

Car::~Car() {

}

void Car::update() {
	if(checkFrontDistance() == -1) {
		road -> removeCar(position);
		delete this;
		return;
	}

	velocity = checkFrontDistance();
	road->moveCar(position, position+velocity);
	position += velocity;

	if(rand()%100 < World::probability && velocity > 0)
		--velocity;
	else if(velocity<World::maxVelocity)
		++velocity;
}

int Car::checkFrontDistance() {
	if(position+velocity > World::length)
		return -1;
	for(int i=1; i<=velocity; ++i) {
		if(road->getCar(i+position) != nullptr) {
			return i;
		}
	}
	return velocity;
}

std::ostream & operator<< (std::ostream & ostr, const Car & car) {
	ostr<<"[x(";
	ostr<<car.velocity;
	ostr<<")]";
	return ostr;
}
