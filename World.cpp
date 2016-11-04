#include "World.hpp"

void World::initWorldVariables(int probability, int length, int maxVelocity) {
	World::length = length;
	World::probability = probability;
	World::maxVelocity = maxVelocity;
}

int World::length;
int World::probability;
int World::maxVelocity;

