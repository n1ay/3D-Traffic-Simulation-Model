#include "Car.hpp"
#include "World.hpp"
#include <cstdlib>
#include "Lane.hpp"

Car::Car(Lane* lane, int length):
	lane(lane), length(length), position(0), velocity(rand()%(World::maxVelocity+1))
{}

Car::Car():
	lane(nullptr), length(0), position(-1), velocity(-1)
{}

Car::~Car() {

}

Car* Car::copy(Lane* laneptr) {
	Car* car = new Car(laneptr, this->length);
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
	//std::cout<<"v="<<velocity<<" p="<<position<<std::endl;
	lane->moveCar(position, position+velocity);
	position += velocity;

	if(rand()%100 < World::probability && velocity > 0)
		--velocity;
	else if(velocity<World::maxVelocity)
		++velocity;
	//std::cout<<"After: v="<<velocity<<" p="<<position<<std::endl;
}

int Car::checkFrontDistance() {
	if(velocity+position>=lane->length) {
		for(int i=1; i+position<lane->length; ++i) {
			if(lane->getCar(i+position) != nullptr) {
				return i - lane->getCar(i+position)->length;
			}
		}
		return -1;
	}

	for(int i=1; i<=velocity+World::maxLength - 1; ++i) {
		if(i+position>=lane->length)
			return std::min(i, velocity);
		if(lane->getCar(i+position) != nullptr) {
			return std::min(i - lane->getCar(i+position)->length, velocity);
		}
	}
	return velocity;
}

int Car::getLength() {
	return length;
}

std::ostream & operator<< (std::ostream & ostr, const Car & car) {
	ostr<<"[x"<<car.velocity<<"]";
	return ostr;
}

void Car::putInLane(Lane* lane) {
	this->lane->getLane()[position]=nullptr;
	this->lane = lane;
	lane->putCar(this, position);
}

Lane* Car::doChangeLane() {
	if(velocity > checkFrontDistance() && checkFrontDistance() != -1)
		return lane->seekLane(true);
	else return nullptr;
}

void Car::changeLane(Lane* lane) {
	if(lane == nullptr || lane->getLane()[position]!=nullptr) return;
	int r = rand()%100;
	bool block = false;
	for(int i =0; position-i>=0; i++) {
		if(lane->getCar(position-i) != nullptr) {
			if(lane->getCar(position-i)->velocity >= i) {
				block = true;
				break;
			}
		}
	}
	if(block && r<World::laneChangeProbabilityLow)
		putInLane(lane);
	else if(!block && r<World::laneChangeProbabilityHigh)
		putInLane(lane);
}
