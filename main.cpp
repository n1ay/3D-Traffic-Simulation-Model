/*
 * Data-Driven Modeling sim engine
 * main.cpp
 *
 *  Created on: 03.11.2016
 */

#include <iostream>
#include <cstdlib>
#include "World.hpp"
#include "Car.hpp"
#include <ctime>
#include <unistd.h>
#include "Lane.hpp"

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
	lane.lockUpdate();
	lane.log();

	for(int i=0; i<10; i++) {
		lane.update();
		lane.lockUpdate();
		lane.log();
		sleep(1);
	}

	//std::cout<<"I am doing something!"<<std::endl;
	return 0;
}
