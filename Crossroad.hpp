/*
 * Crossroad.hpp
 *
 *  Created on: 04.12.2016
 *      Author: kamil
 */

#ifndef CROSSROAD_HPP_
#define CROSSROAD_HPP_

#include "Lane.hpp"
#include "TrafficLight.hpp"
#include <map>

class Crossroad {
private:
	std::vector<Road*> roads;
	std::map<Lane*, std::vector<std::pair<Lane*, int> > > rules;
	std::vector<TrafficLight*> trafficLights;

public:
	Crossroad();
	~Crossroad();
	void addRule(Lane* from, std::vector<std::pair<Lane*, int> > rule);
	void transfer(Lane* from);
	void setDestination(Lane* from);
	void transferAll();
	friend std::ostream & operator<< (std::ostream & ostr, Crossroad & crossroad);
	void addRoad(Road* road);
	void update();
	void lockUpdate();
	void cleanUpdate();
	void addTrafficLight(TrafficLight*);
};

#endif /* CROSSROAD_HPP_ */
