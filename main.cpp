/*
 * Data-Driven Modeling sim engine
 * main.cpp
 *
 *  Created on: 03.11.2016
 */

#include "World.hpp"
#include "Car.hpp"
#include "Lane.hpp"
#include "Road.hpp"

#include <iostream>

#include <cstdlib>
#include <ctime>

#include <unistd.h>

/*
 * TODO: Można zespawnować samochód jeden na drugim, wtedy poprzedni znika
 * TODO: Dorobić zmianę pasa ruchu
 *
 *
 *
 */

int main(int argc, char* argv[]) {
	srand(time(NULL));
	World::initWorldVariables(30, 20, 5);

	int n=3;

	Road road(20, n, n);

	for(int i=0; i<50; i++) {
		(road.getLanes(LEFT))[i%n]->spawnCar();
		(road.getLanes(RIGHT))[i%n]->spawnCar();
		std::cout<<road<<std::endl;
		road.update();
		road.lockUpdate();
		sleep(1);
	}

	//std::cout<<"I am doing something!"<<std::endl;
	return 0;
}
