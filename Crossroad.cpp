/*
 * Crossroad.cpp
 *
 *  Created on: 04.12.2016
 *      Author: kamil
 */

#include "Crossroad.hpp"
#include <iostream>
#include "Car.hpp"
#include "Road.hpp"

Crossroad::Crossroad() {

}

Crossroad::~Crossroad() {

}

void Crossroad::addRule(Lane* from, std::vector<std::pair<Lane*, int> > rule) {
	int sum = 0;
	for(auto& iter: rule)
		sum += iter.second;
	if(sum != 100) {
		std::cerr<<"Cumulative probability of all possibilities have to sum up to 100!"<<std::endl;
		exit(-1);
	}
	rules.insert(std::pair<Lane*, std::vector<std::pair<Lane*, int> > >(from, rule));
}

void Crossroad::setDestination(Lane* from) {
	Car* car = from->getCar(from->getLength()-1);
	if(!car || car->getDestination()) return;
	int cumulativeProbability = 0;
	auto vec = rules.find(from);
	if(vec == rules.end()) return;
	int r = rand()%100;
	for(auto& iter: vec->second) {
		cumulativeProbability += iter.second;
		if(r<cumulativeProbability) {
			car->setDestination(iter.first);
			return;
		}
	}
}

void Crossroad::transfer(Lane* from) {
	Car* car = from->getCar(from->getLength()-1);
	TrafficLight::LightColor color;
	color = (from->getTrafficLight()==nullptr)?(TrafficLight::GREEN):(from->getTrafficLight()->getLightColor());
	if(!car || !car->getDestination() || color==TrafficLight::RED || car->getDestination()->isUsed(0, 1)) return;
	car->getDestination()->putCar(car, 0);
	from->putCar(nullptr, from->getLength()-1);
	car->setLane(car->getDestination());
	car->setPosition(0);
	car->setDestination(nullptr);
}

void Crossroad::transferAll() {
	for(auto& iter: rules) {
		setDestination(iter.first);
		transfer(iter.first);
	}
}

std::ostream & operator<< (std::ostream & ostr, Crossroad & crossroad) {
	for(auto& iter: crossroad.roads) {
		ostr<<*iter;
		ostr<<"==============================\n";
		ostr<<"==============================\n";
	}
	return ostr;
}

void Crossroad::addRoad(Road* road) {
	for(auto r: roads)
		if(r==road)
			return;
	roads.push_back(road);
}

void Crossroad::update() {
	for(auto& iter: roads)
		iter->update();
}

void Crossroad::allowUpdate() {
	for(auto& iter: roads)
		iter->allowUpdate();
}

void Crossroad::lockUpdate() {
	for(auto& iter: roads)
		iter->lockUpdate();
}

void Crossroad::cleanUpdate() {
	for(auto& iter: roads)
		iter->cleanUpdate();
}

void Crossroad::setIntersection(bool intersects) {
	this->intersects=intersects;
}
