/*
 * MapParser.hpp
 *
 *  Created on: 17.01.2017
 *      Author: kamil
 */

#ifndef MAPPARSER_HPP_
#define MAPPARSER_HPP_

#include <map>
#include <vector>
#include "Model.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class MapParser {
private:
	Model model;

public:

	MapParser();
	virtual ~MapParser();

	Model readmap(std::string filename = "map.json");
	void constructRuleVector(std::string rule, std::vector<std::pair<Lane*, int> >& rules);
	Lane* extractLane(std::string rule);
	void addLaneConnections(boost::property_tree::ptree::value_type connectionNode, Crossroad* crossroad);
	void split(const std::string &s, char delim, std::vector<std::string> &elems);
	std::vector<std::string> split(const std::string &s, char delim);
	Road* extractRoad(std::string rule);

	void parseWays(boost::property_tree::ptree ptree);
	void parseNodes(boost::property_tree::ptree ptree);
	void parseLights(boost::property_tree::ptree ptree);
	void parseSpawner(boost::property_tree::ptree ptree);

};

#endif /* MAPPARSER_HPP_ */
