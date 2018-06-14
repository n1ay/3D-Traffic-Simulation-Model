/*
 * SimData.cpp
 *
 *  Created on: 19.01.2017
 *      Author: nepcia
 */

#include "SimData.hpp"

#include <iostream>
#include <string>

#include <stdexcept>

#include <map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

SimData::SimData() {
	framemax = 0;
}

SimData::~SimData() {
	// TODO Auto-generated destructor stub
}

void SimData::readdata(SimMap *sm) {
	namespace pt = boost::property_tree;

	//read json
	pt::ptree ptree;
	pt::json_parser::read_json("frames.json", ptree);

	//tmp car storage
	struct Cartmp {
		unsigned int length;
		std::map<unsigned int, Car::carstep> frames;
	};

	std::map<unsigned int, Cartmp> tmpcars;

	for (auto frame : ptree.get_child("frames")) {
		auto current_frame = frame.second.get<unsigned int>("frame");
		if(current_frame>framemax)
			framemax = current_frame;

		for (auto lane_data : frame.second.get_child("values")) {
			std::string l = lane_data.second.get<std::string>("lane");

			bool forward;
			auto i = l.find('r');
			if( i == std::string::npos) {
				i = l.find('l');
				if (i == std::string::npos)
					throw std::runtime_error("Cannot parse line info");
				forward = false;
			} else
				forward = true;

			unsigned int
				rid = 2 * std::stoi(l.substr(0, i)),
				lid = std::stoi(l.substr(i+1));

			if(!forward)
				++rid;

			for (auto car : lane_data.second.get_child("cars")) {
				auto id = car.second.get<unsigned int>("id");
				auto len= car.second.get<unsigned int>("length");
				auto pos= car.second.get<unsigned int>("position");


				tmpcars[id].length = len;
				tmpcars[id].frames[current_frame] = {rid, lid, pos, forward};
			}
		}
	}

	//fill cars data
	cars.resize(tmpcars.rbegin()->first + 1);
	for(auto &c : cars)
		c.steps.resize(framemax+1);

	for (auto c : tmpcars) {
		cars[c.first].length = c.second.length;
		for(auto pos : c.second.frames)
			cars[c.first].steps[pos.first] = pos.second;
	}

	//car which is not in some frame is teleported to spawner
	for (auto &c : cars) {
		for (auto &s : c.steps) {
			if(s.road == (unsigned int)-1)
				s.road = sm->spawn_way;
		}
	}
}















