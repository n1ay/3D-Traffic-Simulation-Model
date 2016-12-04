/*
 * Crossroad.hpp
 *
 *  Created on: 04.12.2016
 *      Author: kamil
 */

#ifndef CROSSROAD_HPP_
#define CROSSROAD_HPP_

#include "Lane.hpp"
#include <map>

enum trafficLight {
	GREEN, RED
};

class Crossroad {
private:
	std::vector<Road*> roads;
	std::map<Lane*, std::vector<std::pair<Lane*, int> > > rules;

public:
	Crossroad();
	~Crossroad();
	void addRule(Lane* from, std::vector<std::pair<Lane*, int> > rule);
	void transfer(Lane* from);
	void setDestination(Lane* from);
};

#endif /* CROSSROAD_HPP_ */
