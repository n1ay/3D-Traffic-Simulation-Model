#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include "World.hpp"

void World::initWorldVariables(int probability, int length, int maxVelocity, int maxLength, int laneChangeProbabilityLow, int laneChangeProbabilityHigh) {
	if(length < maxLength) {
		std::cerr<<"Lane should be long enough to contain at least one car!\n"<<std::endl;
		exit(-1);
	}
	World::length = length;
	World::probability = probability;
	World::maxVelocity = maxVelocity;
	World::maxLength = maxLength;
	World::laneChangeProbabilityLow = laneChangeProbabilityLow;
	World::laneChangeProbabilityHigh = laneChangeProbabilityHigh;
}

int World::length;
int World::probability;
int World::maxVelocity;
int World::maxLength;
int World::laneChangeProbabilityLow;
int World::laneChangeProbabilityHigh;

