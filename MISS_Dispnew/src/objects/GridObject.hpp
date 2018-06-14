/*
 * objects.hpp
 *
 *  Created on: 03.12.2016
 *      Author: nepcia
 */

#ifndef SRC_GRID_OBJECT_HPP_
#define SRC_GRID_OBJECT_HPP_

#include <vector>
#include <GL/glew.h>

#include <stdexcept>

#include "../ObjectStorage.hpp"

class GEng;

class GridObject: public ObjectStorage {
	friend GEng;

	GLuint vcount;
	GLuint gridShader;
	GLint shaderMVPloc;

public:
	GridObject(GLuint shader):
		gridShader(shader)
	{
		shaderMVPloc = glGetUniformLocation(shader, "mvpmatrix");
		if(shaderMVPloc == GL_INVALID_VALUE || shaderMVPloc == GL_INVALID_OPERATION)
//			throw GEng::GEngException("Cannot find uniform location!");
			throw std::runtime_error("Cannot find uniform location!");

		static const unsigned int size = 5;
		static const float scale = 1.0f;
		vcount = (size*2-1)*2*2*4;
		std::vector<float> verts;
		verts.reserve(vcount);

		float lim = (size-1.0f)*scale;

		for(unsigned int i=1 ; i<size ; ++i) {
			float var = i*scale;
			//left
			verts.push_back(-var);
			verts.push_back(0.0f);
			verts.push_back(-lim);
			verts.push_back(1.0f);

			verts.push_back(-var);
			verts.push_back(0.0f);
			verts.push_back(lim);
			verts.push_back(1.0f);

			//right
			verts.push_back(var);
			verts.push_back(0.0f);
			verts.push_back(-lim);
			verts.push_back(1.0f);

			verts.push_back(var);
			verts.push_back(0.0f);
			verts.push_back(lim);
			verts.push_back(1.0f);


			//near
			verts.push_back(-lim);
			verts.push_back(0.0f);
			verts.push_back(var);
			verts.push_back(1.0f);

			verts.push_back(lim);
			verts.push_back(0.0f);
			verts.push_back(var);
			verts.push_back(1.0f);

			//far
			verts.push_back(-lim);
			verts.push_back(0.0f);
			verts.push_back(-var);
			verts.push_back(1.0f);

			verts.push_back(lim);
			verts.push_back(0.0f);
			verts.push_back(-var);
			verts.push_back(1.0f);
		}

		//X
		lim = size*scale;
		verts.push_back(-lim);
		verts.push_back(0.0f);
		verts.push_back(0.0f);
		verts.push_back(1.0f);

		verts.push_back(lim);
		verts.push_back(0.0f);
		verts.push_back(0.0f);
		verts.push_back(1.0f);

		//Z
		verts.push_back(0.0f);
		verts.push_back(0.0f);
		verts.push_back(-lim);
		verts.push_back(1.0f);

		verts.push_back(0.0f);
		verts.push_back(0.0f);
		verts.push_back(lim);
		verts.push_back(1.0f);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vdata);
		glBindBuffer(GL_ARRAY_BUFFER, vdata);
		glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindVertexArray(0);
	}

	void init() {}

	void preDraw() {
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glUseProgram(gridShader);
	}

	void postDraw() {
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	void draw() {
		glDrawArrays(GL_LINES, 0, vcount);
	}

	void deinit() {
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vdata);
	}
};


#endif /* SRC_GRID_OBJECT_HPP_ */
