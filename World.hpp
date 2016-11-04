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

	static void initWorldVariables(int probability, int length, int maxVelocity);
};


#endif /* WORLD_HPP_ */
