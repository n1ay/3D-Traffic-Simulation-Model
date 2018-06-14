/*
 * MapObject.hpp
 *
 *  Created on: 16.01.2017
 *      Author: nepcia
 */

#ifndef SRC_OBJECTS_MAPOBJECT_HPP_
#define SRC_OBJECTS_MAPOBJECT_HPP_

#include "../SimMap.hpp"
#include "../ObjectStorage.hpp"

#include <iostream>

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>

class CarObject;

class MapObject: public ObjectStorage {
	friend CarObject;

	GLuint shader;

	GLuint vcount;
	GLuint nodeDataBuffer, waysBuffer;

public:

	GLuint nodeBuffer, nodeTexture;

	MapObject(GLuint shader, const SimMap &map) :
		shader(shader)
	{
		float viewWidth = 10, viewHeight = 10;
		auto lat_minmax = std::minmax_element(map.nodes.begin(), map.nodes.end(),
				[](auto e1, auto e2){
					return e1.second.lat < e2.second.lat;
		});

		auto lon_minmax = std::minmax_element(map.nodes.begin(), map.nodes.end(),
				[](auto e1, auto e2){
					return e1.second.lon < e2.second.lon;
		});

		float
			lat_min = lat_minmax.first->second.lat,
			lat_max = lat_minmax.second->second.lat,
			lon_min = lon_minmax.first->second.lon,
			lon_max = lon_minmax.second->second.lon;

		float contentHeight = lat_max - lat_min, contentWidth = lon_max - lon_min;
		float viewToContentRatioX = viewWidth/contentWidth, viewToContentRatioY = viewHeight/contentHeight;
		float relevantRatio = viewToContentRatioY;
		if (viewToContentRatioX < viewToContentRatioY) {
			relevantRatio =  viewToContentRatioX;
		}

		glm::mat4 trans(relevantRatio, 0, 0, 0,
				0, relevantRatio, 0, 0,
				0, 0, relevantRatio, 0,
				-5 - lat_min * relevantRatio, 0, -5 - lon_min * relevantRatio, 1);

		auto nodes_max = map.nodes.rbegin()->first;
		std::vector<float> nodedata((nodes_max+1)*4);
		for(const auto &n : map.nodes) {
			auto v = /*trans **/ glm::vec4(n.second.lon, 0.0f, n.second.lat, 1.0f);
			nodedata.at(4*n.first) = v.x;
			nodedata.at(4*n.first+1)=v.y;
			nodedata.at(4*n.first+2)=v.z;
			nodedata.at(4*n.first+3)=1.0f;
		}

		std::vector<glm::vec4> rawnodes;
		rawnodes.resize(nodes_max+1);
		glGenBuffers(1, &nodeBuffer);
		glGenTextures(1, &nodeTexture);
		glBindBuffer(GL_ARRAY_BUFFER, nodeBuffer);
		for(const auto &n : map.nodes) {
			rawnodes[n.first] = glm::vec4(n.second.lon, 0.0f, n.second.lat, 1.0f);
		}
		glBufferData(GL_ARRAY_BUFFER,
				sizeof(glm::vec4) * rawnodes.size(),
				rawnodes.data(),
				GL_STATIC_DRAW);



		glGenBuffers(1, &nodeDataBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, nodeDataBuffer);
		glBufferData(GL_ARRAY_BUFFER,
				sizeof(float) * nodedata.size(),
				nodedata.data(),
				GL_STATIC_DRAW);

		vcount = map.ways.size();
		std::vector<unsigned int> waynodes;
		waynodes.reserve(vcount);
		for( const auto &w : map.ways ) {
			if(w.first % 2 == 0) {
				waynodes.push_back(w.second.beg);
				waynodes.push_back(w.second.end);
			}
		}

		glGenBuffers(1, &waysBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, waysBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				sizeof(unsigned int) * waynodes.size(),
				waynodes.data(),
				GL_STATIC_DRAW);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, waysBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, nodeDataBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	}

	virtual ~MapObject() {
		deinit();
	}


	void init() {}

	void preDraw() {
		glBindVertexArray(vao);
		glUseProgram(shader);
	}

	void postDraw() {
		glBindVertexArray(0);
	}

	void draw() {
		glDrawElements(GL_LINES, vcount, GL_UNSIGNED_INT, 0);
	}

	void deinit() {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &nodeDataBuffer);
		glDeleteBuffers(1, &waysBuffer);
	}
};


#endif /* SRC_OBJECTS_MAPOBJECT_HPP_ */




















