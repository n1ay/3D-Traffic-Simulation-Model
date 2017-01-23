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
#include "Model.hpp"
#include "MapParser.hpp"
#include "FrameParser.hpp"

#include <iostream>

#include <cstdlib>
#include <ctime>

#include <unistd.h>

/*
 * 1 cell = 1 m
 * 1 update = 0.5 s
 * velocity of 1 = 2 m/s -> 7.2km/h
 *
 */

int main(int argc, char* argv[]) {

	std::cout<<argc<<" "<<argv<<std::endl;

	srand(time(NULL));
	World::initWorldVariables(1, 50, 20, 14, 20, 90);

	MapParser mapParser;
	FrameParser frameParser;
	frameParser.createTree();
	Model model = mapParser.readmap();
	for(int i=0; i<2*10*60; i++) {
		frameParser.parseFrame(model);
		model.update();
		//std::cout<<*(model.crossroads.at(1))<<std::endl;
		//usleep(500000);
	}
	frameParser.parseFrame(model);
	frameParser.saveToFile();
	return 0;
}
