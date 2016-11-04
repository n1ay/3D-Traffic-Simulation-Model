
#ifndef WORLD_CPP_
#define WORLD_CPP_

class World {
public:
	static int length;
	static int probability;
	static int maxVelocity;

	static void initWorldVariables(int probability, int length, int maxVelocity) {
		World::length = length;
		World::probability = probability;
		World::maxVelocity = maxVelocity;
	}
};

#endif
