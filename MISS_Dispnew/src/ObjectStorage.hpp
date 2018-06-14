/*
 * ObjectStorage.hpp
 *
 *  Created on: 03.12.2016
 *      Author: nepcia
 */

#ifndef SRC_OBJECTSTORAGE_HPP_
#define SRC_OBJECTSTORAGE_HPP_

#include <GL/glew.h>


class ObjectStorage {
protected:
	//vertex data
	GLuint vao;
	GLuint vdata;

public:
	ObjectStorage();
	virtual ~ObjectStorage();

	virtual void init()=0;
	virtual void preDraw()=0;
	virtual void draw()=0;
	virtual void postDraw()=0;
	virtual void deinit()=0;
};

#endif /* SRC_OBJECTSTORAGE_HPP_ */
