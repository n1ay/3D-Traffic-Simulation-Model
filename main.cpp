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
#include "Crossroad.hpp"

#include <iostream>

#include <cstdlib>
#include <ctime>

#include <unistd.h>

/*
 *
 * Pradwopodobnie działa -> TODO: Dorobić zmianę pasa ruchu
 * TODO: Road destructor
 * TODO: Dodać, żeby przy zmianie pasa przestrzegał zasad forbidLaneChange w klasie Road
 * TODO: Dorobić możliwość wcześniejszego kończenia/późniejszego zakańczania lane'ów
 *
 */

int main(int argc, char* argv[]) {

	std::cout<<argc<<" "<<argv<<std::endl;

	srand(time(NULL));
	//World::initWorldVariables(15, 20, 5, 5, 20, 90);
	World::initWorldVariables(0, 20, 4, 5, 20, 90);

	Crossroad crossroad;

	Road road1(15, 1, 3);
	Road road2(25, 2, 2);

	std::vector<std::pair<Lane*, int> > rule1;
	rule1.push_back(std::pair<Lane*, int>(road2.getLanes(RIGHT)[0], 80));
	rule1.push_back(std::pair<Lane*, int>(road2.getLanes(RIGHT)[1], 20));
	crossroad.addRule(road1.getLanes(RIGHT)[0], rule1);
	crossroad.addRoad(&road1);
	crossroad.addRoad(&road2);

	for(int i=0; i<50; i++) {
		road1.getLanes(RIGHT)[rand()%road1.getLanesQuantity(RIGHT)]->spawnCar(rand()%World::maxLength+1);
		std::cout<<crossroad<<std::endl;
		crossroad.cleanUpdate();
		crossroad.transferAll();
		crossroad.update();
		crossroad.lockUpdate();
		usleep(500000);
	}

	return 0;
}
