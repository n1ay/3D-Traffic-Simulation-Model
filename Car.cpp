#include "Car.hpp"
#include "World.hpp"
#include <cstdlib>
#include "Lane.hpp"

Car::Car(Lane* lane):
	lane(lane), position(0), velocity(rand()%(World::maxVelocity+1))
{}

Car::Car():
	lane(nullptr), position(-1), velocity(-1)
{}

Car::~Car() {

}

Car* Car::copy(Lane* laneptr) {
	Car* car = new Car(laneptr);
	car->position = this->position;
	car->velocity = this->velocity;
	return car;
}

void Car::update() {

	if(checkFrontDistance()==-1) {
		lane->removeCar(position);
		return;
	}
	velocity = checkFrontDistance();
	std::cout<<"v="<<velocity<<" p="<<position<<std::endl;
	lane->moveCar(position, position+velocity);
	position += velocity;

	if(rand()%100 < World::probability && velocity > 0)
		--velocity;
	else if(velocity<World::maxVelocity)
		++velocity;
	std::cout<<"After: v="<<velocity<<" p="<<position<<std::endl;
}

int Car::checkFrontDistance() {
	if(velocity+position>=lane->length) {
		for(int i=1; i+position<lane->length; ++i) {
			if(lane->getCar(i+position) != nullptr) {
				return i;
			}
		}
		return -1;
	}

	for(int i=1; i<=velocity; ++i) {
		if(lane->getCar(i+position) != nullptr) {
			return i;
		}
	}
	return velocity;
}

std::ostream & operator<< (std::ostream & ostr, const Car & car) {
	ostr<<"[x";
	ostr<<car.velocity;
	ostr<<"]";
	return ostr;
}
