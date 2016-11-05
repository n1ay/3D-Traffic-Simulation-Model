/*
 * Data-Driven Modeling sim engine
 * main.cpp
 *
 *  Created on: 03.11.2016
 */

#include <iostream>
#include <cstdlib>
#include "Road.hpp"
#include "World.hpp"
#include "Car.hpp"
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
	World::initWorldVariables(50, 20, 5);

	Road road(Direction::RIGHT);

	for(int i=0; i<10; i++) {
		road.spawnCar();
		std::cout<<road<<std::endl;
		road.update();
		sleep(1);
	}

	//std::cout<<"I am doing something!"<<std::endl;
	return 0;
}
