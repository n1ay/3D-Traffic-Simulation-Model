/*
 * main.cpp
 *
 *  Created on: 03.12.2016
 *      Author: nepcia
 */

#include <iostream>

#include "GEng.hpp"
#include "SimMap.hpp"
#include "SimData.hpp"



int main() {

	//read map
	SimMap sm;
	sm.readmap();

	//read cars
	SimData sd;
	sd.readdata(&sm);

	//start graphics engine
	GEng ge(sm, sd);
	ge.start();

	return 0;
}



































