/*
 * Road.cpp
 *
 *  Created on: 17.11.2016
 *      Author: kamil
 */

#include "Road.hpp"
#include "Lane.hpp"

Road::Road(int length, int left, int right): length(length), left(left), right(right) {
	for(int i=0; i<left; i++)
		lanesLeft.push_back(new Lane(this, LEFT, length));
	for(int i=0; i<right; i++)
		lanesRight.push_back(new Lane(this, RIGHT, length));
}

Road::~Road() {

}

//it is called lane1 and lane2 instead of from and to
//because on road when its forbidden to change lane from lane1 to lane2
//then its also forbidden to do the same from lane 2 to lane1
void Road::forbidLaneChange(Lane* lane1, Lane* lane2) {
	auto pair = forbiddenLaneChanges.find(lane1);
	if(pair == forbiddenLaneChanges.map::end()) {
		auto setPtr = new std::set<Lane*>();
		setPtr -> insert(lane2);
		forbiddenLaneChanges.insert(std::pair<Lane*, std::set<Lane*>* >(lane1, setPtr));
	}
	else {
		pair->second->insert(lane2);

	}
}

std::vector<Lane*> Road::getLanes(int direction) {
	if(direction == LEFT)
		return lanesLeft;
	else
		return lanesRight;
}

std::ostream & operator<<(std::ostream & stream, const Road & road) {
	stream<<"direction: <-\n";
	for(int i=0; i<road.left; i++)
		stream<<*(road.lanesLeft[i])<<"\n";

	stream<<"direction: ->\n";
	for(int i=0; i<road.right; i++)
		stream<<*(road.lanesRight[i])<<"\n";

	return stream;

}

void Road::update() {
	changeLanes();
	for(int i=0; i<left; i++)
		lanesLeft[i] -> update();

	for(int i=0; i<right; i++)
		lanesRight[i] -> update();
}

void Road::allowUpdate() {
	changeLanes();
	for(int i=0; i<left; i++)
		lanesLeft[i] -> allowUpdate();

	for(int i=0; i<right; i++)
		lanesRight[i] -> allowUpdate();
}

void Road::lockUpdate() {
	for(int i=0; i<left; i++)
		lanesLeft[i] -> lockUpdate();

	for(int i=0; i<right; i++)
		lanesRight[i] -> lockUpdate();
}

void Road::changeLanes() {
	//from right to left
	for(auto &iter: lanesLeft) {
		if(iter != nullptr)
			iter->updateCarChangeLane(false);
	}
	for(auto &iter: lanesRight) {
		if(iter != nullptr)
			iter->updateCarChangeLane(false);
	}

	//from left to right
	for(auto &iter: lanesLeft) {
		if(iter != nullptr)
			iter->updateCarChangeLane(true);
	}
	for(auto &iter: lanesRight) {
		if(iter != nullptr)
			iter->updateCarChangeLane(true);
	}
}

int Road::getLength() {
	return length;
}

int Road::getLanesQuantity(int direction) {
	return (direction==LEFT)?lanesLeft.size():lanesRight.size();
}

void Road::cleanUpdate() {
	for(auto &iter: lanesLeft) {
		if(iter != nullptr)
			iter->cleanUpdate();
	}
	for(auto &iter: lanesRight) {
		if(iter != nullptr)
			iter->cleanUpdate();
	}
}

bool Road::isForbiddenToChangeLane(Lane* lane1, Lane* lane2) {
	auto pair = forbiddenLaneChanges.find(lane1);
	if(pair == forbiddenLaneChanges.end()) {
		pair = forbiddenLaneChanges.find(lane2);
		if(pair == forbiddenLaneChanges.end())
			return false;
		for(auto iter: *(pair->second)) {
			if(iter == lane1)
				return true;
		}
	}
	for(auto iter: *(pair->second)) {
				if(iter == lane2)
					return true;
			}
	return false;
}
