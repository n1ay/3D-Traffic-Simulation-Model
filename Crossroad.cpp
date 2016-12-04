/*
 * Crossroad.cpp
 *
 *  Created on: 04.12.2016
 *      Author: kamil
 */

#include "Crossroad.hpp"
#include <iostream>
#include "Car.hpp"

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
	for(auto iter: vec->second) {
		cumulativeProbability += iter.second;
		if(r<cumulativeProbability)
			car->setDestination(iter.first);
	}
}

void Crossroad::transfer(Lane* from) {
	Car* car = from->getCar(from->getLength()-1);
	if(!car) return;
	car->getDestination()->putCar(car, 0);
	from->putCar(nullptr, from->getLength()-1);
}
