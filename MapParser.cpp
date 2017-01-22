#include <cstring>
#include "MapParser.hpp"

#include <vector>
#include <string>
#include <fstream>

MapParser::MapParser() {}

MapParser::~MapParser() {}

Model MapParser::readmap(std::string filename) {
	namespace pt = boost::property_tree;

	pt::ptree ptree;
	pt::json_parser::read_json(filename, ptree);

	parseWays(ptree);
	parseNodes(ptree);
	parseLights(ptree);
	parseSpawner(ptree);

	return model;
}

void MapParser::parseWays(boost::property_tree::ptree ptree) {
	for (const auto &map_way : ptree.get_child("ways")) {
		int left, right, length;
		length = map_way.second.get<unsigned int>("length");
		left = map_way.second.get<unsigned int>("left");
		right = map_way.second.get<unsigned int>("right");
		Road* road = new Road(length, left, right);
		model.addRoad(road);
		for(auto &iter: map_way.second.get_child("forbid")) {
			road->forbidLaneChange(extractLane(iter.second.get<std::string>("from")), extractLane(iter.second.get<std::string>("to")));
		}
	}
}

void MapParser::parseNodes(boost::property_tree::ptree ptree) {
	for (const auto &map_node : ptree.get_child("nodes")) {
		Crossroad* crossroad = new Crossroad;
		model.addCrossroad(crossroad);
		for(auto &iter: map_node.second.get_child("roads")) {
			int id = iter.second.get_value<unsigned int>();
			crossroad->addRoad(model.roads.at(id));
		}
		std::string text = map_node.second.get<std::string>("intersection");
		if(!text.compare("false"))
			model.crossroads.at(model.crossroads.size()-1)->setIntersection(false);
		else
			for(auto &iter: map_node.second.get_child("connections")) {
				addLaneConnections(iter, crossroad);
			}
	}
}

void MapParser::parseLights(boost::property_tree::ptree ptree) {
	for (const auto &map_node : ptree.get_child("lights")) {
		TrafficLight* trafficLight = new TrafficLight;
		model.addTrafficLight(trafficLight);
		TrafficLight::LightColor color;
		std::string colortxt = map_node.second.get<std::string>("color");
		int time = map_node.second.get<unsigned int>("time");
		int red = map_node.second.get<unsigned int>("red");
		int green = map_node.second.get<unsigned int>("green");
		if(!colortxt.compare("red"))
			color = TrafficLight::RED;
		else
			color = TrafficLight::GREEN;
		trafficLight->setState(color, time);
		trafficLight->setGreenToRedCycleTime(green);
		trafficLight->setRedToGreenCycleTime(red);
		for(auto &iter: map_node.second.get_child("lanes")) {
			extractLane(iter.second.get_value<std::string>())->setTrafficLight(trafficLight);
		}
	}
}

void MapParser::parseSpawner(boost::property_tree::ptree ptree) {
	for (const auto &map_node : ptree.get_child("spawner")) {
		Lane* lane = extractLane(map_node.second.get<std::string>("lane"));
		lane->setSpawnProbability(map_node.second.get<float>("prob"));
	}
}

void MapParser::addLaneConnections(boost::property_tree::ptree::value_type connectionNode, Crossroad* crossroad) {
	Lane* from = extractLane(connectionNode.second.get<std::string>("from"));
	from->setCrossInfo(true);
	std::vector<std::pair<Lane*, int>> rules;
	for(auto &iter: connectionNode.second.get_child("to")) {
		constructRuleVector(iter.second.get_value<std::string>(), rules);
	}
	crossroad->addRule(from, rules);

}

void MapParser::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::string> MapParser::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void MapParser::constructRuleVector(std::string rule, std::vector<std::pair<Lane*, int> >& rules) {
	std::vector<std::string> words = split(rule, ',');
	std::string to=words.at(0), prob=words.at(1);
	Lane* lane = extractLane(to);

	rules.push_back(std::pair<Lane*, int>(lane, atoi(prob.c_str())));
}

Lane* MapParser::extractLane(std::string rule) {
	int firstID, secondID;
	std::vector<std::string> words;
	Direction direction;

	int pos;
	pos = rule.find_first_of('l');
	if(pos<0) {
		direction = RIGHT;
		words = split(rule, 'r');
	}
	else {
		direction = LEFT;
		words = split(rule, 'l');
	}
	firstID = atoi(words.at(0).c_str());
	secondID = atoi(words.at(1).c_str());
	if(direction==LEFT)
		return model.roads.at(firstID)->lanesLeft.at(secondID);
	else
		return model.roads.at(firstID)->lanesRight.at(secondID);
}

Road* MapParser::extractRoad(std::string rule) {
	int firstID;
	std::vector<std::string> words;

	int pos;
	pos = rule.find_first_of('l');
	if(pos<0)
		words = split(rule, 'r');
	else
		words = split(rule, 'l');
	firstID = atoi(words.at(0).c_str());
	return model.roads.at(firstID);
}
