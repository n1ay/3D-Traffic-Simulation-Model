/*
 * SimData.hpp
 *
 *  Created on: 19.01.2017
 *      Author: nepcia
 */

#ifndef SRC_SIMDATA_HPP_
#define SRC_SIMDATA_HPP_

#include "SimMap.hpp"
#include <vector>

class CarObject;

class SimData {

	friend CarObject;

	unsigned int framemax;

	struct Car {
		struct carstep {
			unsigned int road=-1, lane=0, position=0;
			bool forward = true;
		};
		unsigned int length;
		std::vector<carstep> steps;
	};

	std::vector<Car> cars;
public:
	SimData();
	virtual ~SimData();

	void readdata(SimMap *sm);
};

#endif /* SRC_SIMDATA_HPP_ */
