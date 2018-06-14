/*
 * MapReader.cpp
 *
 *  Created on: 14.01.2017
 *      Author: nepcia
 */

#include "SimMap.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

SimMap::SimMap() {}

SimMap::~SimMap() {}

void SimMap::readmap(std::string filename) {
	namespace pt = boost::property_tree;

	//read data
	pt::ptree ptree;
	pt::json_parser::read_json(filename, ptree);

	//read nodes
	for (const auto &map_node : ptree.get_child("nodes")) {
		Node node;
		node.lat = map_node.second.get<float>("lat");
		node.lon = map_node.second.get<float>("lon");
		nodes.insert(std::make_pair(map_node.second.get<indextype>("id"), node));
	}

	//read ways
	for (const auto &map_way : ptree.get_child("ways")) {
		Way way;
		auto lanesl = map_way.second.get<unsigned int>("left");
		auto lanesr = map_way.second.get<unsigned int>("right");

		way.length = map_way.second.get<unsigned int>("length");
		way.lanes = lanesr;

		way.beg = map_way.second.get<indextype>("beg");
		way.end = map_way.second.get<indextype>("end");

		//insert way and opposite way
		auto id = 2*map_way.second.get<indextype>("id");
		ways.insert(std::make_pair(id, way));
		std::swap(way.beg, way.end);
		way.lanes = lanesl;
		ways.insert(std::make_pair(id+1, way));
	}

	//insert spawner
	spawn_node = nodes.rbegin()->first + 1;
	nodes.insert(std::make_pair(spawn_node, Node({100.0f, 100.0f})));
	spawn_way = ways.rbegin()->first + 1;
	ways.insert(std::make_pair(spawn_way, Way({1, 1, spawn_node, spawn_node})));
}
