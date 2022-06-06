/*
 * MapReader.hpp
 *
 *  Created on: 14.01.2017
 *      Author: nepcia
 */

#ifndef SRC_SIMMAP_HPP_
#define SRC_SIMMAP_HPP_

#include <map>
#include <string>
#include <vector>

class SimMap {

public:
	using indextype = unsigned int;

	struct Node {
		float lat, lon;
	};
	std::map<indextype, Node> nodes;


	struct Way {
		unsigned int length;
		unsigned int lanes;
		indextype beg, end;
	};
	std::map<indextype, Way> ways;

	indextype spawn_node=0, spawn_way=0;

	SimMap();
	virtual ~SimMap();


	void readmap(std::string filename = "map.json");
};

#endif /* SRC_SIMMAP_HPP_ */
