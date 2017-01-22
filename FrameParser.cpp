/*
 * FrameParser.cpp
 *
 *  Created on: 19.01.2017
 *      Author: kamil
 */

#include "FrameParser.hpp"

FrameParser::FrameParser() {}

FrameParser::~FrameParser() {}

void FrameParser::createTree() {
	pt::ptree root;
	pt::ptree frames;
	this->frames = frames;
	this->root = root;
}
void FrameParser::parseFrame(Model model) {
	std::stringstream ss;
	std::string text;
	pt::ptree frame;
	frame.put("frame", model.frame);
	pt::ptree values;
	int rid=0;
	for(auto & road: model.roads) {
		int lid = 0;
		for(auto & llane: road->getLanes(LEFT)) {
			llane->direction=LEFT;
			pt::ptree lane;
			pt::ptree cars;
			ss<<rid;
			ss<<"l";
			ss<<lid;
			ss>>text;
			lane.put("lane", text);
			ss=std::stringstream("");
			text="";
			for(auto & car_ptr: llane->lanes[0]) {
				if(!car_ptr)
					continue;
				pt::ptree car;
				car.put("id", car_ptr->id);
				car.put("position", car_ptr->position);
				car.put("length", car_ptr->length);
				cars.push_back(std::make_pair("", car));
			}
			lane.add_child("cars", cars);
			values.push_back(std::make_pair("", lane));
			++lid;

		}
		lid = 0;
		for(auto & rlane: road->getLanes(RIGHT)) {
			rlane->direction=RIGHT;
			pt::ptree lane;
			pt::ptree cars;
			ss<<rid;
			ss<<"r";
			ss<<lid;
			ss>>text;
			lane.put("lane", text);
			ss=std::stringstream("");
			text="";
			for(auto & car_ptr: rlane->lanes[0]) {
				if(!car_ptr)
					continue;
				pt::ptree car;
				car.put("id", car_ptr->id);
				car.put("position", car_ptr->position);
				car.put("length", car_ptr->length);
				cars.push_back(std::make_pair("", car));
			}
			lane.add_child("cars", cars);
			values.push_back(std::make_pair("", lane));
			++lid;
				}
		++rid;
	}
	frame.add_child("values", values);
	frames.push_back(std::make_pair("", frame));
}

void FrameParser::saveToFile(std::string filename) {
	root.add_child("frames", frames);
	pt::write_json(filename, this->root);
}
