/*
 * cubedata.hpp
 *
 *  Created on: 18.01.2017
 *      Author: nepcia
 */

#ifndef SRC_OBJECTS_CUBEDATA_HPP_
#define SRC_OBJECTS_CUBEDATA_HPP_

static const GLfloat wallv[] = {
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

static const GLushort walli[] = {

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



#endif /* SRC_OBJECTS_CUBEDATA_HPP_ */