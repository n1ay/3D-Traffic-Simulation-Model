#include "Lane.hpp"
#include "Car.hpp"
#include "World.hpp"


Lane::Lane(int direction, int length):
	direction(direction), length(length)
{
	lane = new Car* [length];
	updateLane = new Car* [length];
}

Lane::~Lane() {
	for(int i=0; i<length; ++i) {
		delete lane[i];
		delete updateLane[i];
	}
	delete [] lane;
	delete [] updateLane;
}

void Lane::update() {
	cleanUpdate();
	for(int i=length; i>=0; --i) {
		if(lane[i]!=nullptr)
			lane[i]->update();
	}
}

void Lane::spawnCar() {
	updateLane[0] = new Car(this);
}

std::ostream & operator<<(std::ostream & ostr, const Lane & lane) {
	if(lane.direction == Direction::LEFT)
		ostr<<"direction: <-\n";
	else
		ostr<<"direction: ->\n";
	for(int i=0; i<lane.length; i++)
		if(lane.lane[i] == nullptr)
			ostr<<"[  ]";
		else
			ostr<<(*(lane.lane[i]));
	return ostr;
}

void Lane::log() {

	if(direction == Direction::LEFT)
			std::cout<<"direction: <-\n";
		else
			std::cout<<"direction: ->\nData:\n";

	for(int i=0; i<length; i++)
		if(lane[i] == nullptr)
			std::cout<<"[  ]";
		else
			std::cout<<(*(lane[i]));

	std::cout<<"\nTemp:"<<std::endl;

	for(int i=0; i<length; i++)
		if(updateLane[i] == nullptr)
			std::cout<<"[  ]";
		else
			std::cout<<(*(updateLane[i]));
	std::cout<<std::endl;

}

Car* Lane::getCar(int position) {
	return lane[position];
}

void Lane::moveCar(int from, int to) {
	std::cout<<"copying car for attributes: from="<<from<<" to="<<to<<std::endl;
	updateLane[to] = lane[from]->copy(this);
}

void Lane::removeCar(int position) {
	if(updateLane[position]==nullptr) return;
	delete updateLane[position];
	updateLane[position] = nullptr;
}

void Lane::cleanUpdate() {
	for(int i=0; i<length; ++i)
		if(updateLane[i] != nullptr) {
			delete updateLane[i];
			updateLane[i] = nullptr;
		}
}

void Lane::lockUpdate() {
	Car** tmp = lane;
	lane = updateLane;
	updateLane = tmp;
}

int Lane::getLength() {
	return length;
}
