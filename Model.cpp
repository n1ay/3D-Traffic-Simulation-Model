/*
 * Model.cpp
 *
 *  Created on: 17.01.2017
 *      Author: kamil
 */

#include "Model.hpp"

Model::Model() {
	// TODO Auto-generated constructor stub

}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

void Model::update() {
	for(auto &iter: trafficLights)
		iter->tick();

	for(auto &iter: crossroads) {
		iter->cleanUpdate();
		iter->transferAll();
		iter->update();
		iter->lockUpdate();
	}

	for(auto &iter:crossroads)
		iter->allowUpdate();

	++frame;
}

void Model::addCrossroad(Crossroad* crossroad) {
	crossroads.push_back(crossroad);
}

void Model::addRoad(Road* road) {
	roads.push_back(road);
}

void Model::addTrafficLight(TrafficLight* trafficLight) {
	trafficLights.push_back(trafficLight);
}
