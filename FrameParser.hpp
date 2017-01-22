/*
 * FrameParser.hpp
 *
 *  Created on: 19.01.2017
 *      Author: kamil
 */

#ifndef FRAMEPARSER_HPP_
#define FRAMEPARSER_HPP_

#include "Model.hpp"
#include "Car.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

class Car;

class FrameParser {
private:
	pt::ptree root;
	pt::ptree frames;
public:
	FrameParser();
	virtual ~FrameParser();
	void createTree();
	void parseFrame(Model model);
	void saveToFile(std::string filename="frames.json");
};

#endif /* FRAMEPARSER_HPP_ */
