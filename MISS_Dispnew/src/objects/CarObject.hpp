/*
 * CarObject.hpp
 *
 *  Created on: 18.01.2017
 *      Author: nepcia
 */

#ifndef SRC_OBJECTS_CAROBJECT_HPP_
#define SRC_OBJECTS_CAROBJECT_HPP_

#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../ObjectStorage.hpp"
#include "../SimData.hpp"
#include "../SimMap.hpp"

class GEng;

class CarObject: public ObjectStorage {
	friend GEng;

	double time = 0.0;

	GLuint vertexDataBuffer, vertexIndexesBuffer;
	GLuint carWayNodesBuffer, carWayNodesTexture;
	GLuint carColorBuffer;

	GLuint carShader,
		upos_matN,
		upos_matMV,
		upos_matMVP,
		upos_lightpos,
		upos_time;

	//car lengths
	GLuint l4, l5, l6, l14;
	GLuint o5, o6, o14;

public:
	CarObject(GLuint shader) {
		l4 = l5 = l6 = l14 = 0;
		o5 = o6 = o14 = 0;

		static const GLfloat raw_vertex_data[] = {
			//positions + normals

			//back
			-1.0f,	-1.0f,	-1.0f,	1.0f,
			 0.0f,	 0.0f,	-1.0f,	0.0f,

			-1.0f,	 1.0f,	-1.0f,	1.0f,
			 0.0f,	 0.0f,	-1.0f,	0.0f,

			 1.0f,	-1.0f,	-1.0f,	1.0f,
			 0.0f,	 0.0f,	-1.0f,	0.0f,

			 1.0f,	 1.0f,	-1.0f,	1.0f,
			 0.0f,	 0.0f,	-1.0f,	0.0f,



			 //right
			 1.0f,	-1.0f,	-1.0f,	1.0f,
			 1.0f,	 0.0f,	 0.0f,	0.0f,

			 1.0f,	 1.0f,	-1.0f,	1.0f,
			 1.0f,	 0.0f,	 0.0f,	0.0f,

			 1.0f,	-1.0f,	 1.0f,	1.0f,
			 1.0f,	 0.0f,	 0.0f,	0.0f,

			 1.0f,	 1.0f,	 1.0f,	1.0f,
			 1.0f,	 0.0f,	 0.0f,	0.0f,



			 //front
			 1.0f,	-1.0f,	 1.0f,	1.0f,
			 0.0f,	 0.0f,	 1.0f,	0.0f,

			 1.0f,	 1.0f,	 1.0f,	1.0f,
			 0.0f,	 0.0f,	 1.0f,	0.0f,

			-1.0f,	-1.0f,	 1.0f,	1.0f,
			 0.0f,	 0.0f,	 1.0f,	0.0f,

			-1.0f,	 1.0f,	 1.0f,	1.0f,
			 0.0f,	 0.0f,	 1.0f,	0.0f,



			 //left
			-1.0f,	-1.0f,	 1.0f,	1.0f,
			-1.0f,	 0.0f,	 0.0f,	0.0f,

			-1.0f,	 1.0f,	 1.0f,	1.0f,
			-1.0f,	 0.0f,	 0.0f,	0.0f,

			-1.0f,	-1.0f,	-1.0f,	1.0f,
			-1.0f,	 0.0f,	 0.0f,	0.0f,

			-1.0f,	 1.0f,	-1.0f,	1.0f,
			-1.0f,	 0.0f,	 0.0f,	0.0f,



			//bottom
			-1.0f,	-1.0f,	-1.0f,	1.0f,
			 0.0f,	-1.0f,	 0.0f,	0.0f,

			 1.0f,	-1.0f,	-1.0f,	1.0f,
			 0.0f,	-1.0f,	 0.0f,	0.0f,

			 1.0f,	-1.0f,	 1.0f,	1.0f,
			 0.0f,	-1.0f,	 0.0f,	0.0f,

			-1.0f,	-1.0f,	 1.0f,	1.0f,
			 0.0f,	-1.0f,	 0.0f,	0.0f,



			 //top
			-1.0f,	 1.0f,	-1.0f,	1.0f,
			 0.0f,	 1.0f,	 0.0f,	0.0f,

			 1.0f,	 1.0f,	-1.0f,	1.0f,
			 0.0f,	 1.0f,	 0.0f,	0.0f,

			 1.0f,	 1.0f,	 1.0f,	1.0f,
			 0.0f,	 1.0f,	 0.0f,	0.0f,

			-1.0f,	 1.0f,	 1.0f,	1.0f,
			 0.0f,	 1.0f,	 0.0f,	0.0f,
		};

		static const GLushort raw_index_data[] = {

			//back
			0, 1, 2,
			2, 1, 3,

			//right
			4, 5, 6,
			6, 5, 7,

			//front
			8,	9,	10,
			10,	9,	11,

			//left
			12,	13,	14,
			14,	13,	15,

			//bottom
			19,	16,	17,
			17,	18, 19,

			//top
			23,	22,	21,
			23,	21,	20
		};

		//read shader variables location
		this->carShader = shader;
		upos_matN = glGetUniformLocation(shader, "mat_n");
		upos_matMV = glGetUniformLocation(shader, "mat_mv");
		upos_matMVP = glGetUniformLocation(shader, "mat_mvp");
		upos_lightpos = glGetUniformLocation(shader, "vLightPosition");
		upos_time = glGetUniformLocation(shader, "t");




		//generate vertices for cars of all lengths
		const int car_max_length = 20;
		std::vector<glm::vec4> vdata;
		{
			vdata.reserve(car_max_length * 48);

			for(int i=1 ; i<=car_max_length ; ++i) {
				//calculate vdata
				float zscale = i - 0.4f;
				glm::mat4
					trans_matrix1= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
					trans_matrix2= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.2f)),
					scale_matrix = glm::scale(glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)), glm::vec3(2.5f, 1.5f, zscale));

				for(int v=0 ; v < 192 ; v+=8) {
					glm::vec4 vertex =
							trans_matrix2 *
							(scale_matrix *
							(trans_matrix1 * glm::vec4(raw_vertex_data[v+0], raw_vertex_data[v+1], raw_vertex_data[v+2], raw_vertex_data[v+3])));

					vdata.push_back(vertex);
					vdata.push_back(glm::vec4(raw_vertex_data[v+4], raw_vertex_data[v+5], raw_vertex_data[v+6], raw_vertex_data[v+7]));
				}
			}
		}

		//genereate vertices indexes for all langth cars
		std::vector<float> cdata;
		{
			std::ifstream colors_in("colors.bin", std::ifstream::ate | std::ifstream::binary);
			auto colors_size = colors_in.tellg()/4;
			cdata.reserve(colors_size);
			colors_in.clear();
			colors_in.seekg(0, std::ios::beg);
			float tmp;
			for(long int i=0 ; i<colors_size ; ++i) {
				colors_in.read((char*)&tmp, sizeof(tmp));
				cdata.push_back(tmp);
			}
		}

		//generate buffers
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vertexDataBuffer);
		glGenBuffers(1, &vertexIndexesBuffer);

		glGenBuffers(1, &carWayNodesBuffer);
		glGenTextures(1, &carWayNodesTexture);

		glGenBuffers(1, &carColorBuffer);

		//fill buffers with data
		glBindBuffer(GL_ARRAY_BUFFER, vertexDataBuffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(glm::vec4)*vdata.size(),
			vdata.data(),
			GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndexesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(raw_index_data),
			raw_index_data,
			GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, carColorBuffer);
		glBufferData(GL_ARRAY_BUFFER,
				sizeof(float)*cdata.size(),
				cdata.data(),
				GL_STATIC_DRAW);

		//configure vertex attributes
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexDataBuffer);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertexDataBuffer);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid *)(4*sizeof(float)));

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, carColorBuffer);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
		glVertexAttribDivisor(2, 1);

		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, carWayNodesBuffer);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
		glVertexAttribDivisor(3, 1);

		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, carWayNodesBuffer);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid *)(4*sizeof(float)));
		glVertexAttribDivisor(4, 1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void countCarLengths(const SimData *sd) {
		for (const auto &c : sd->cars) {
			if (c.length == 4)
				++l4;
			else if (c.length == 5)
				++l5;
			else if (c.length == 6)
				++l6;
			else if (c.length == 14)
				++l14;
			else
				throw std::runtime_error("Car with unsupported length "+std::to_string(c.length));
		}
		o5 = l4;
		o6 = o5 + l5;
		o14= o6 + l6;
	}

	virtual ~CarObject() {}

	void init() {}

	void preDraw() {
		glBindVertexArray(vao);
		glUseProgram(carShader);
	}

	void postDraw() {
		glBindVertexArray(0);
	}

	void draw() {
		draw(2);
	}

	void draw(int i) {
		glDrawElementsBaseVertex(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, 24*(i-1));
	}

	void deinit() {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vertexIndexesBuffer);
		glDeleteBuffers(1, &vertexDataBuffer);
	}

	void drawCars(float dt, SimData *sd, SimMap *map) {
		time += dt;
		unsigned int simstep = std::min(std::floor(time), (double)sd->framemax-1);
		float time_step = (time > sd->framemax)? 1.0f : time - (unsigned int)time;

		//calculate position of cars in current frame
		unsigned int pos4, pos5, pos6, pos14;
		pos4=0; pos5=o5*2; pos6=o6*2; pos14=o14*2;

		std::vector<glm::vec4> pos_offsets;
		pos_offsets.resize(2*sd->cars.size());
		for (const auto &c : sd->cars) {
			auto last = c.steps[simstep];
			auto next = c.steps[simstep+1];
			SimMap::Node beg_node, end_node;
			glm::vec4 begv, endv, rotv;
			float offset_value;

			if(last.road == next.road) {
				beg_node = map->nodes[map->ways[last.road].beg];
				end_node = map->nodes[map->ways[next.road].end];

				begv = glm::vec4(beg_node.lon, 0.0f, beg_node.lat, 0.0f);
				endv = glm::vec4(end_node.lon, 0.0f, end_node.lat, 0.0f);

				auto dir = endv - begv;
				auto r = glm::cross(glm::vec3(glm::normalize(dir)), glm::vec3(0.0f, 1.0f, 0.0f));

				{
					auto dot = -glm::normalize(dir).z;
					auto sin = -glm::sign(dir.x) * std::sqrt(1.0 - dot*dot);
					rotv = glm::vec4(dot, sin, -sin, dot);
				}

				if (last.lane == next.lane) {
					float beg_dist = (last.position+1) / (float)map->ways[last.road].length;
					float end_dist = (next.position+1) / (float)map->ways[last.road].length;

					begv += glm::vec4(3.0f*last.lane*r, 0.0f);
					endv += glm::vec4(3.0f*next.lane*r, 0.0f);

					offset_value = time_step * (end_dist - beg_dist) + beg_dist;


				} else {
					auto road_length = (float)map->ways[last.road].length;
					auto last_zoffset = (last.position+1) / road_length, next_zoffset = (next.position+1) / road_length;

					begv += glm::vec4(3.0f*last.lane*r, 0.0f) + last_zoffset*dir;
					endv = glm::vec4(beg_node.lon, 0.0f, beg_node.lat, 0.0f) + glm::vec4(3.0f*next.lane*r, 0.0f) + next_zoffset*dir;

					offset_value = time_step;
				}

				if (!last.forward) {
					begv += glm::vec4(3.0f*r, 0.0f);
					endv += glm::vec4(3.0f*r, 0.0f);
				}


			} else {
				beg_node = map->nodes[map->ways[last.road].end];
				end_node = map->nodes[map->ways[next.road].beg];

				begv = glm::vec4(beg_node.lon, 0.0f, beg_node.lat, 0.0f);
				endv = glm::vec4(end_node.lon, 0.0f, end_node.lat, 0.0f);

				auto dir = endv - begv;
				{
					auto dot = -glm::normalize(dir).z;
					auto sin = -glm::sign(dir.x) * std::sqrt(1.0 - dot*dot);
					rotv = glm::vec4(dot, sin, -sin, dot);
				}

				offset_value = time_step;
			}

			auto offset = glm::mix(
					begv,
					endv,
					offset_value );

//			std::cout<<begv.x<<" "<<begv.y<<" "<<begv.z<<"\n"<<endv.x<<" "<<endv.y<<" "<<endv.z<<"\n"<<std::endl;

			if(c.length == 4) {
				pos_offsets.at(pos4++) = offset;
				pos_offsets.at(pos4++) = rotv;

			} else if(c.length == 5) {
				pos_offsets.at(pos5++) = offset;
				pos_offsets.at(pos5++) = rotv;

			} else if(c.length == 6) {
				pos_offsets.at(pos6++) = offset;
				pos_offsets.at(pos6++) = rotv;

			} else if(c.length == 14) {
				pos_offsets.at(pos14++) = offset;
				pos_offsets.at(pos14++) = rotv;

			}
		}

		//update data
		glBindBuffer(GL_TEXTURE_BUFFER, carWayNodesBuffer);
		glBufferData(GL_TEXTURE_BUFFER, sizeof(glm::vec4) * pos_offsets.size(), pos_offsets.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);

		glUniform1f(upos_time, time_step);

		//draw cars
		glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, l4, 24*(4-1), 0);
		glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, l5, 24*(5-1), o5);
		glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, l6, 24*(6-1), o6);
		glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, l14, 24*(14-1), o14);

		glBindVertexArray(0);
	}
};

#endif /* SRC_OBJECTS_CAROBJECT_HPP_ */



























