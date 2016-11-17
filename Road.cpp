/*
 * Road.cpp
 *
 *  Created on: 17.11.2016
 *      Author: kamil
 */

#include "Road.hpp"

Road::Road(int length, int left, int right): length(length), left(left), right(right) {
	for(int i=0; i<left; i++)
		lanesLeft.push_back(new Lane(LEFT, length));
	for(int i=0; i<right; i++)
		lanesRight.push_back(new Lane(RIGHT, length));
}

Road::~Road() {

}

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

bool Road::isForbidden(Lane* lane1, Lane* lane2) {
	auto pair = forbiddenLaneChanges.find(lane1);
	if(pair == forbiddenLaneChanges.map::end()) {
		pair = forbiddenLaneChanges.find(lane2);
		if(pair == forbiddenLaneChanges.map::end()) {
			return false;
		}
		else {
			if(pair->second->count(lane1))
				return true;
			else
				return false;
		}
	}
	else {
		if(pair->second->count(lane2))
			return true;
		else
			return false;
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
	for(int i=0; i<left; i++)
		lanesLeft[i] -> update();

	for(int i=0; i<right; i++)
		lanesRight[i] -> update();
}

void Road::lockUpdate() {
	for(int i=0; i<left; i++)
		lanesLeft[i] -> lockUpdate();

	for(int i=0; i<right; i++)
		lanesRight[i] -> lockUpdate();
}

