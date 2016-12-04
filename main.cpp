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
 * Już chyba działa :) -> Niby poprawione, ale nadal nie działa -> TODO: Można zespawnować samochód jeden na drugim, wtedy poprzedni znika
 * TODO: Dorobić zmianę pasa ruchu
 * TODO: Road destructor
 * TODO: Dodać, żeby przy zmianie pasa przestrzegał zasad forbidLaneChange w klasie Road
 * TODO: Update zawsze zwiększa prędkość samochodów(ale nie ponad max), nawet jak w odległości od siebie 1 komórki mają przeszkodę
 *
 *
 *
 */

int main(int argc, char* argv[]) {
	srand(time(NULL));
	//World::initWorldVariables(15, 20, 5, 5, 20, 90);
	World::initWorldVariables(0, 20, 5, 5, 20, 90);


	Road road(20, 3, 1);

	for(int i=0; i<50; i++) {
		(road.getLanes(LEFT))[1/*rand()%road.getLanesQuantity(LEFT)*/]->spawnCar(1);
		(road.getLanes(RIGHT))[rand()%road.getLanesQuantity(RIGHT)]->spawnCar(3);
		std::cout<<road<<std::endl;
		road.update();
		road.lockUpdate();
		usleep(500000);
	}

	//std::cout<<"I am doing something!"<<std::endl;
	return 0;
}
