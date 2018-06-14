/*
 * GEng.hpp
 *
 *  Created on: 03.12.2016
 *      Author: nepcia
 */

#ifndef GENG_HPP_
#define GENG_HPP_

#include <exception>
#include <stdexcept>

#include <string>

#include <vector>
#include <map>

#include <GL/glew.h>
#include <GL/glxew.h>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include <glm/glm.hpp>

#include <sys/time.h>
#include <unistd.h>

#include "objects/GridObject.hpp"
#include "objects/MapObject.hpp"
#include "objects/CarObject.hpp"
#include "SimMap.hpp"
#include "ObjectStorage.hpp"


class GEng {
public:
	class GEngException: public std::runtime_error {
//		std::string _msg;

	public:
		GEngException(std::string msg);
//		const char *what();
	};


private:
	//shaders & objects
	std::vector<GLuint> shaders;
	std::vector<ObjectStorage*> objects;
	GridObject *grid;
	MapObject *map;
	CarObject *car;

	//simulation data
	SimMap &sm;
	SimData &sd;

	//render_context
	struct windowContext {
		GLXContext ctx;
		Display *dpy;
		Window win;
		int winw;
		int winh;

		Atom wmDeleteMessage;
	} rcx;

	//mouse & keyboard
	struct _inputs {
		std::map <unsigned short, bool> keys;
		bool grabMouse;
		int mx, my;
		int lastx, lasty;
	} inputs;

	//camera
	struct _camera {
		glm::vec3 position, cameraUp, cameraFront;
		float pitch, yaw;

		_camera():
			position(), cameraUp(0.0f, 1.0f, 0.0f), cameraFront(0.0f, 0.0f, -1.0f), pitch(0.0f), yaw(270.0f)
		{}
	} camera;

	//projection matrix
	glm::mat4 proj;

	static void setupshaders(std::string shadername, GLuint &shadernr);

	void initObjects();
	void deinitObjects();

	void onResize(unsigned int width, unsigned int height);

	bool processEvents(double dt);

	void mouseMove(float dt);
	void keyboardMove(float dt);

	void render(float dt);

public:

	int start();

	GEng(SimMap &map, SimData &sd);
	virtual ~GEng();
};

#endif /* GENG_HPP_ */













































