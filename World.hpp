/*
 * World.hpp
 *
 *  Created on: 04.11.2016
 *      Author: nepcia
 */

#ifndef WORLD_HPP_
#define WORLD_HPP_

class World {
public:
	static int length;
	static int probability;
	static int maxVelocity;
	static int maxLength;

	static int laneChangeProbabilityLow;
	static int laneChangeProbabilityHigh;

	static void initWorldVariables(int probability, int length, int maxVelocity, int maxLength, int laneChangeProbabilityLow, int LaneChangeProbabilityHigh);
};


#endif /* WORLD_HPP_ */
