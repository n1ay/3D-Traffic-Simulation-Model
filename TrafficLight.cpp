/*
 * TrafficLight.cpp
 *
 *  Created on: 06.12.2016
 *      Author: kamil
 */

#include "TrafficLight.hpp"

TrafficLight::TrafficLight() {
	redToGreenCycleTime = 0;
	greenToRedCycleTime = 0;
	lightColor = RED;
	cycleTime = 0;
}

TrafficLight::~TrafficLight() {

}

void TrafficLight::changeLight() {
	if(lightColor == GREEN && cycleTime == 0) {
		lightColor = RED;
		cycleTime = redToGreenCycleTime;
	}
	else if(lightColor == RED && cycleTime == 0) {
		lightColor = GREEN;
		cycleTime = greenToRedCycleTime;
	}
}

void TrafficLight::setRedToGreenCycleTime(int time) {
	redToGreenCycleTime = time;
}

void TrafficLight::setGreenToRedCycleTime(int time) {
	greenToRedCycleTime = time;
}

void TrafficLight::setLightColor(LightColor color) {
	lightColor = color;
}

TrafficLight::LightColor TrafficLight::getLightColor() {
	return lightColor;
}

void TrafficLight::addLane(Lane* lane) {
	lane->setTrafficLight(this);
}

