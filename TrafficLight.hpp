/*
 * TrafficLight.hpp
 *
 *  Created on: 06.12.2016
 *      Author: kamil
 */

#ifndef TRAFFICLIGHT_HPP_
#define TRAFFICLIGHT_HPP_

#include "Lane.hpp"

class Lane;

class TrafficLight {
	friend class Crossroad;
public:
	enum LightColor {
			GREEN, RED
		};
private:
	LightColor lightColor;
	int redToGreenCycleTime;
	int greenToRedCycleTime;
	int cycleTime;
public:
	TrafficLight();
	~TrafficLight();
	void changeLight();
	void setRedToGreenCycleTime(int time);
	void setGreenToRedCycleTime(int time);
	void setLightColor(LightColor color);
	LightColor getLightColor();
	void addLane(Lane* lane);
};

#endif /* TRAFFICLIGHT_HPP_ */
