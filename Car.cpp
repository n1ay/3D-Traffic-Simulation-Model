#include "Car.hpp"
#include "World.hpp"
#include <cstdlib>
#include "Lane.hpp"
#include "Road.hpp"

int Car::count = 0;

Car::Car(Lane* lane, int length):
	lane(lane), length(length), position(0), velocity(rand()%((World::maxVelocity-4)/2)+4)
{
	Car::count++;
}

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


//TODO: dodać zmienną, która warunkuje czy trzeba zwiększyć prędkość samochodu w update, czy nie
//TODO: jest to już gotowe, ale nie tak jak powinno i trochę na około

void Car::update() {
	if(alreadyUpdated)
		return;
	alreadyUpdated = true;
	if(checkFrontDistance()==-1) {
		lane->removeCar(position);
		return;
	}
	int preUpdateVelocity = velocity;
	velocity = moveSmooth();
	velocity = checkFrontDistance();
	lane->moveCar(position, position+velocity);
	position += velocity;

	if(rand()%100 < World::probability && velocity > 0)
		--velocity;
	else if(velocity<World::maxVelocity && preUpdateVelocity == velocity && getFrontDistance() && doAccelerate)
		++velocity;
	changedLane = false;
	doAccelerate = true;
}

int Car::moveSmooth() {
	int l = lane->getLength();
	Car* car = nullptr;
	int vel, pos;
	for(int i=position+1; i<l; i++)
		if(lane->getCar(i)) {
			car=lane->getCar(i);
			break;
		}

	if(!car) {
		vel = 0;
		pos = lane->getLength();
	}
	else {
		vel = car->velocity;
		pos = car->position - (car->length-1);
	}

	if(velocity <= vel) {
		return velocity;
	}

	int dv = (velocity - vel)*(velocity - vel)/(pos-position);
	int dv1 = (velocity - vel+1)*(velocity - vel+1)/(pos-position);

	if(dv1)
		doAccelerate = false;


	return std::max(1, velocity - dv);


}

int Car::checkFrontDistance() {
	if(lane->getCrossInfo()) {
		//crosses a road
		if(velocity+position+1>=lane->length) {
			for(int i=1; i+position<lane->length; ++i) {
				if(lane->getCar(i+position) != nullptr) {
					return i - lane->getCar(i+position)->length;
				}
			}
			return lane->getLength()-position-1;
		}

	} else {
		if(velocity+position>=lane->length) {
			for(int i=1; i+position<lane->length; ++i) {
				if(lane->getCar(i+position) != nullptr) {
					return i - lane->getCar(i+position)->length;
				}
			}
			return -1;
		}
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

int Car::getFrontDistance() {
	if(lane->getCrossInfo()) {
		//crosses a road
		if(velocity+position+1>=lane->length) {
			for(int i=1; i+position<lane->length; ++i) {
				if(lane->getCar(i+position) != nullptr) {
					return i - lane->getCar(i+position)->length;
				}
			}
			return lane->getLength()-position-1;
		}

	} else {
		if(velocity+position>=lane->length) {
			for(int i=1; i+position<lane->length; ++i) {
				if(lane->getCar(i+position) != nullptr) {
					return i - lane->getCar(i+position)->length;
				}
			}
			return -1;
		}
	}

	for(int i=1; i<=velocity+World::maxLength; ++i) {
		if(i+position>=lane->length)
			return i;
		if(lane->getCar(i+position) != nullptr) {
			return i - lane->getCar(i+position)->length;
		}
	}
	return World::maxLength;
}


int Car::getLength() {
	return length;
}

std::ostream & operator<< (std::ostream & ostr, const Car & car) {
	ostr<<"["<<car.velocity<<"l"<<car.length<<"]";
	return ostr;
}

void Car::putInLane(Lane* lane) {
	this->lane->putCar(nullptr, position);
	this->lane = lane;
	lane->putCar(this, position);
	changedLane = true;
}

Lane* Car::doChangeLane(bool next) {
	if(velocity > checkFrontDistance() && checkFrontDistance() != -1)
		return lane->seekLane(next);
	else return nullptr;
}

void Car::changeLane(Lane* lane) {
	bool block = lane?(lane->isUsed(position, length)):true;
	if (this->lane->road->isForbiddenToChangeLane(this->lane, lane)) return;
	if(changedLane || block) return;
	int r = rand()%100;
	block = false;
	for(int i=0; position-i>=0; i++) {
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

void Car::setDestination(Lane* destination) {
	this->destination = destination;
}

Lane* Car::getDestination() {
	return destination;
}

void Car::setLane(Lane* lane) {
	this->lane = lane;
}

void Car::setPosition(int position) {
	this->position = position;
}

void Car::setUpdated(bool updated) {
	this->alreadyUpdated = updated;
}
