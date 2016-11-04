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
	delete this->road;
}

void Car::update() {

}

bool Car::checkFrontDistance() {
	for(int i=1; i<=velocity; ++i) {
			return false;
	}
	return true;
}
