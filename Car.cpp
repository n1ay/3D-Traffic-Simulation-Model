#include "Car.hpp"
#include "World.cpp"
#include <cstdlib>

	Car::Car(Road* road) {
		this->road = road;
		position = 0;
		velocity = rand()%(World::maxVelocity+1);
	}

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
