/*
 * Model.hpp
 *
 *  Created on: 17.01.2017
 *      Author: kamil
 */

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "Crossroad.hpp"
#include "Road.hpp"

class Model {

	friend int main(int argc, char** argv);


friend class MapParser;
friend class FrameParser;
private:
	unsigned long int frame = 0;
	std::vector<Crossroad*> crossroads;
	std::vector<Road*> roads;
	std::vector<TrafficLight*> trafficLights;
	// probability of spawning vehicle of certain size


public:
	Model();
	virtual ~Model();
	void update();
	void addCrossroad(Crossroad* crossroad);
	void addRoad(Road* road);
	void addTrafficLight(TrafficLight* trafficLight);
};

#endif /* MODEL_HPP_ */
