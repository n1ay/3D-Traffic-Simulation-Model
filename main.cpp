/*
 * Data-Driven Modeling sim engine
 * main.cpp
 *
 *  Created on: 03.11.2016
 */

#include "World.hpp"
#include "Car.hpp"
#include "Lane.hpp"

#include <iostream>

#include <cstdlib>
#include <ctime>

#include <unistd.h>

/*
 * TODO: Można zespawnować samochód jeden na drugim, wtedy poprzedni znika
 *
 *
 *
 *
 */

int main(int argc, char* argv[]) {
	srand(time(NULL));
	World::initWorldVariables(0, 20, 5);

	Lane lane(Direction::RIGHT, World::length);

	lane.spawnCar();

	for(int i=0; i<10; i++) {
		lane.log();
		lane.update();
		sleep(1);
	}

	//std::cout<<"I am doing something!"<<std::endl;
	return 0;
}
