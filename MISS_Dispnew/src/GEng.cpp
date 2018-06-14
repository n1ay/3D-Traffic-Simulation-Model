/*
 * GEng.cpp
 *
 *  Created on: 03.12.2016
 *      Author: nepcia
 */

#include "GEng.hpp"

#include "glm/gtc/matrix_inverse.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

#include <cmath>


#include <X11/keysymdef.h>


#include "objects/GridObject.hpp"
#include "objects/MapObject.hpp"
#include "objects/CarObject.hpp"



GEng::GEngException::GEngException(std::string msg):
	std::runtime_error(msg)
{}


void GEngLog(std::string msg) {
	std::cout<<"{GEng} "<<msg<<std::endl;
}

void GEng::initObjects() {
	//load & compile shaders
	GLuint shader;
	setupshaders("grid", shader);
	shaders.push_back(shader);
	grid = new GridObject(shader);

	setupshaders("map", shader);
	shaders.push_back(shader);
	map = new MapObject(shader, sm);

	setupshaders("car", shader);
	shaders.push_back(shader);
	car = new CarObject(shader);
	car->countCarLengths(&sd);


	for(auto iter : objects)
		iter->init();
}

void GEng::deinitObjects() {
	delete map;
	delete grid;
	delete car;
}

void GEng::onResize(unsigned int width, unsigned int height) {
	//called on window resize
	rcx.winw = width;
	rcx.winh = height;

	//calculate new projection matrix & set viewport
	proj = glm::perspectiveFov(glm::pi<float>() / 2.0f, (float)width, (float)height, 0.1f, 200.0f);
	glViewport(0, 0, width, height);
	return;
}

GEng::GEng(SimMap &map, SimData &sd):
	sm(map), sd(sd)
{
	GEngLog("starting...");

	rcx.winw = 1200;
	rcx.winh = 900;

	//requested opengl context
	XSetWindowAttributes winAttribs;
	GLint winmask, majVer = 0, minVer = 0;
	XVisualInfo *visualInfo;
	GLXFBConfig *fbConfigs;
	int numConfigs = 0;
	static int fbAttribs[] = {	GLX_RENDER_TYPE,	GLX_RGBA_BIT,
								GLX_X_RENDERABLE,	GL_TRUE,
								GLX_DRAWABLE_TYPE,	GLX_WINDOW_BIT,
								GLX_DOUBLEBUFFER,	GL_TRUE,
								GLX_RED_SIZE,		8,
								GLX_GREEN_SIZE,		8,
								GLX_BLUE_SIZE,		8,
								GLX_ALPHA_SIZE,		8,
								GLX_DEPTH_SIZE,		24,
								0	};
	rcx.dpy = XOpenDisplay(NULL);
	glXQueryVersion(rcx.dpy, &majVer, &minVer);
	GEngLog("GLX version "+std::to_string(majVer)+"."+std::to_string(minVer));
	if(majVer == 1 && minVer < 2) {
		XCloseDisplay(rcx.dpy);
		throw GEngException("GLX 1.2 is required to run this program!");
	}


	//initial pre GLEW opengl function pointers
	glXChooseFBConfig = (GLXFBConfig*(*)(Display *, int, const int *, int *))glXGetProcAddressARB((GLubyte*)"glXChooseFBConfig");
	glXGetVisualFromFBConfig = (XVisualInfo*(*)(Display *, GLXFBConfig))glXGetProcAddressARB((GLubyte*)"glXGetVisualFromFBConfig");
	glXCreateContextAttribsARB = (GLXContext(*)(Display *, GLXFBConfig, GLXContext, Bool, const int *))glXGetProcAddressARB((GLubyte*)"glXCreateContextAttribsARB");

	//get framebuffer configs
	fbConfigs = glXChooseFBConfig(rcx.dpy, DefaultScreen(rcx.dpy), fbAttribs, &numConfigs);
	visualInfo = glXGetVisualFromFBConfig(rcx.dpy, fbConfigs[0]);

	//setup and create window
	winAttribs.event_mask =	ExposureMask | VisibilityChangeMask |
							KeyPressMask | KeyReleaseMask | KeymapStateMask |
							PointerMotionMask | StructureNotifyMask | ClientMessage ;
	winAttribs.border_pixel = 0;
	winAttribs.bit_gravity = StaticGravity;
	winAttribs.colormap = XCreateColormap(rcx.dpy, RootWindow(rcx.dpy, visualInfo->screen), visualInfo->visual, AllocNone);
	winmask = CWBorderPixel | CWBitGravity | CWEventMask | CWColormap;

	rcx.win = XCreateWindow(rcx.dpy, DefaultRootWindow(rcx.dpy), 20, 20, rcx.winw, rcx.winh, 0, visualInfo->depth, InputOutput,
							visualInfo->visual, winmask, &winAttribs);

	//capture window close signal
	rcx.wmDeleteMessage = XInternAtom(rcx.dpy, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(rcx.dpy, rcx.win, &rcx.wmDeleteMessage, 1);

	XMapWindow(rcx.dpy, rcx.win);

	//select opengl context
	GLint attribs[] = {	GLX_CONTEXT_MAJOR_VERSION_ARB,	3,
						GLX_CONTEXT_MINOR_VERSION_ARB,	3,
						GLX_CONTEXT_PROFILE_MASK_ARB,	GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
						0	};

	rcx.ctx = glXCreateContextAttribsARB(rcx.dpy, fbConfigs[0], 0, GL_TRUE, attribs);
	glXMakeCurrent(rcx.dpy, rcx.win, rcx.ctx);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	XStoreName(rcx.dpy, rcx.win, "MISS_disp");

	const GLubyte * ver = []() {
		glewExperimental = GL_TRUE;
		int glewError = glewInit();
		if(glewError != GLEW_OK)
		{
			std::ostringstream errorstr;
			errorstr<<"GLEW error - "<<glewGetErrorString(glewError);
			throw GEngException(errorstr.str());
		}
		GLenum err = glGetError();
		if(err != GL_NO_ERROR && err != GL_INVALID_ENUM)
			throw GEngException("GLEW returned OpenGL error!");

		return glGetString(GL_VERSION);
	}();


	//setup initial state
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GEngLog("OpenGL version "+std::string((const char*)ver));

	initObjects();

	onResize(rcx.winw, rcx.winh);

	glPrimitiveRestartIndex(-1);

	GEngLog("available");

	inputs.grabMouse = false;
}


GEng::~GEng() {

	//delete shaders
	for(auto iter : shaders)
		glDeleteProgram(iter);

	//delete objects
	for(auto iter : objects) {
		iter->deinit();
		delete iter;
	}

	//detach context, close window
	GEngLog("closing...");
	deinitObjects();
	glXMakeCurrent(rcx.dpy, None, NULL);
	glXDestroyContext(rcx.dpy, rcx.ctx);
	rcx.ctx = NULL;

	XDestroyWindow(rcx.dpy, rcx.win);
	rcx.win = (Window)NULL;

	XCloseDisplay(rcx.dpy);
	rcx.dpy = 0;
	GEngLog("closed");
}


void GEng::mouseMove(float dt) {
	static const float moveval = 2.0f;

	if(inputs.grabMouse) {
		//calculate mouse movement since last time
		int	diffx = inputs.lastx - inputs.mx,
			diffy = inputs.lasty - inputs.my;

		//calculate camera rotation
		camera.pitch	+= diffy*moveval*(float)dt;
		camera.yaw		-= diffx*moveval*(float)dt;

		camera.pitch = glm::clamp(camera.pitch, -89.0f, 89.0f);

		glm::vec3 front;
			front.x = std::cos(glm::radians(camera.yaw)) * std::cos(glm::radians(camera.pitch));
			front.y = std::sin(glm::radians(camera.pitch));
			front.z = std::sin(glm::radians(camera.yaw)) * std::cos(glm::radians(camera.pitch));

		camera.cameraFront = glm::normalize(front);

		//warp mouse pointer to center
		if(inputs.mx < rcx.winw*0.05 || inputs.mx > rcx.winw*0.95 || inputs.my < rcx.winh*0.05 || inputs.my > rcx.winh*0.95)
		{
			inputs.mx = inputs.lastx = rcx.winw/2;
			inputs.my = inputs.lasty = rcx.winh/2;
			XWarpPointer(rcx.dpy, None, rcx.win, 0, 0, 0, 0, rcx.winw/2, rcx.winh/2);
		}
	}

	inputs.lastx = inputs.mx;
	inputs.lasty = inputs.my;

	return;
}

void GEng::keyboardMove(float dt) {
	static const float moveval = 5.0;

	//move camera
	auto moveF = [this, dt] (float val) {
		this->camera.position += val * dt  * this->camera.cameraFront;
	};

	auto moveU = [this, dt] (float val) {
		this->camera.position += val * dt  * this->camera.cameraUp;
	};

	auto moveR = [this, dt] (float val) {
		this->camera.position += glm::normalize(glm::cross(this->camera.cameraFront, this->camera.cameraUp)) * val * dt;
	};

	if(inputs.keys[XK_w]) {
		if(inputs.keys[XK_Control_L])
			moveF(5*moveval);
		else
			moveF(moveval);
	}

	if(inputs.keys[XK_s])
		moveF(-moveval);

	if(inputs.keys[XK_a])
		moveR(-moveval);
	if(inputs.keys[XK_d])
		moveR(moveval);

	if(inputs.keys[XK_space])
		moveU(moveval);
	if(inputs.keys[XK_Shift_L])
		moveU(-moveval);

	//grab mouse
	if(inputs.keys['g']) {
		XWarpPointer(rcx.dpy, None, rcx.win, 0, 0, 0, 0, rcx.winw/2, rcx.winh/2);
		inputs.mx = inputs.lastx = rcx.winw/2;
		inputs.my = inputs.lasty = rcx.winh/2;
		inputs.grabMouse = true;


	} else if(inputs.keys['h']) {
		inputs.grabMouse = false;


	//warp time
	} else if(inputs.keys['r']) {
		car->time = 0.0;
	} else if (inputs.keys['t']) {
		car->time = std::max(0.0, car->time - 0.03);
	} else if (inputs.keys[XK_bracketleft]) {
		car->time = std::max(0.0, car->time - 0.1);
	} else if (inputs.keys[XK_bracketright]) {
		car->time = std::max(0.0, car->time + 0.5);
	}
}


void GEng::render(float dt) {
	keyboardMove(dt);
	mouseMove(dt);

	//clear last frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//calculate current matrices
	glm::mat4 view = glm::lookAt(camera.position, camera.position + camera.cameraFront, camera.cameraUp);
	glm::mat3 normal = glm::inverseTranspose(glm::mat3(view));
	glm::mat4 mvp = proj * view;
	glm::vec4 light = view*glm::vec4(5.0f, 5.0f, 2.0f, 1.0f);

	//near (0,0) grid
	grid->preDraw();
		glUniformMatrix4fv(grid->shaderMVPloc, 1, GL_FALSE, &mvp[0][0]);
		grid->draw();
	grid->postDraw();

	//roads
	map->preDraw();
		//TODO: valid shader
		glUniformMatrix4fv(grid->shaderMVPloc, 1, GL_FALSE, &mvp[0][0]);
		map->draw();
	map->postDraw();

	//cars
	car->preDraw();
		glUniformMatrix3fv(car->upos_matN, 1, GL_FALSE, &normal[0][0]);
		glUniformMatrix4fv(car->upos_matMV, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(car->upos_matMVP, 1, GL_FALSE, &mvp[0][0]);
		glUniform3fv(car->upos_lightpos, 1, &light[0]);
		car->drawCars(dt, &sd, &sm);
	car->postDraw();

	//display
	glXSwapBuffers(rcx.dpy, rcx.win);
}


bool GEng::processEvents(double dt) {
	static const double renderStep = 1/50.0;
	static double renderSum=0.0;
	static bool windowMapped = false;

	renderSum += dt;

	// Watch for new X events
	if(XPending(rcx.dpy))
	{
		XEvent newEvent;
		XNextEvent(rcx.dpy, &newEvent);

		switch(newEvent.type)
		{
			case MapNotify:
			{
				windowMapped = true;
				break;
			}
			case UnmapNotify:
			{
				windowMapped = false;
				break;
			}
			case ConfigureNotify:
			{
				XWindowAttributes winData;
				XGetWindowAttributes(rcx.dpy, rcx.win, &winData);
				onResize(winData.width, winData.height);
				break;
			}
			case MotionNotify:
			{
				inputs.mx = newEvent.xmotion.x;
				inputs.my = newEvent.xmotion.y;
				break;
			}
			case KeymapNotify:
			{
				XRefreshKeyboardMapping(&newEvent.xmapping);
				break;
			}
			case KeyPress:
			{
				auto keysym = XLookupKeysym(&newEvent.xkey, 0);
				if(keysym != NoSymbol)
					inputs.keys[keysym]=true;

				if(keysym == XK_x)
					return false;

				break;
			}
			case KeyRelease:
			{
				auto keyReleased = [&newEvent, this]() {
					auto keysym = XLookupKeysym(&newEvent.xkey, 0);
					if(keysym != NoSymbol)
						inputs.keys[keysym]=false;
				};

				if(XEventsQueued(rcx.dpy, QueuedAfterReading))
				{
					XEvent nextev;
					XPeekEvent(rcx.dpy, &nextev);

					if(nextev.type == KeyPress &&
							nextev.xkey.time == newEvent.xkey.time &&
							nextev.xkey.keycode == newEvent.xkey.keycode )
						XNextEvent(rcx.dpy, &nextev); //remove false keyPress from queue
					else
						keyReleased();
				}
				else
					keyReleased();

				break;
			}
			case ClientMessage:
			{
				if( (unsigned int)newEvent.xclient.data.l[0]==rcx.wmDeleteMessage )
					return false;
				break;
			}
			case Expose:
			{
				//TODO: Expose event
				break;
			}
			case VisibilityNotify:
			{
				//TODO: Visibility event
				break;
			}
			case DestroyNotify:
				return false;
			default:
				//std::liout\tother"<<newEvent.type<<std::endl;
				break;
		}
	}

	if(windowMapped && renderSum>renderStep)
	{
		render(renderSum);
		renderSum = 0.0;
	}

	return true;
}

int GEng::start() {
	auto deltat = [](timeval &act, timeval &last) {
		return (act.tv_sec - last.tv_sec) + (act.tv_usec - last.tv_usec)/1000000.0;
	};

	timeval actTime, lastTime;
	double dt;

	gettimeofday(&lastTime, NULL);
	usleep(0);
	gettimeofday(&actTime, NULL);

	dt = deltat(actTime, lastTime);

	//process events until exit
	while( processEvents(dt) ) {
		lastTime = actTime;
		usleep(1000);
		gettimeofday(&actTime, NULL);
		dt = deltat(actTime, lastTime);
	}

	return 0;
}

void GEng::setupshaders(std::string shadername, GLuint &shadernr) {
	std::string vsfile("shaders/"), fsfile("shaders/");
	vsfile += shadername;	fsfile += shadername;
	vsfile += ".vs";		fsfile += ".fs";

	std::string vs,fs,tmp;
	std::ifstream vsIN(vsfile),fsIN(fsfile);
	if(!vsIN.good())
		throw GEngException("Vertex shader program source not exists!");
	if(!fsIN.good())
		throw GEngException("Fragment shader program source not exists!");
	while(vsIN.good())
	{
		getline(vsIN,tmp);
		vs+=tmp+"\n";
	}
	tmp="";
	while(fsIN.good())
	{
		getline(fsIN,tmp);
		fs+=tmp+"\n";
	}

	vsIN.close();
	fsIN.close();

	GLuint hvs,hfs;
	hvs=glCreateShader(GL_VERTEX_SHADER);
	hfs=glCreateShader(GL_FRAGMENT_SHADER);

	if(hvs==0 || hfs==0)
		throw GEngException(std::string("Can not create shader objects for '") + std::string(shadername) + std::string("'!"));

	const char *vsa = vs.c_str();
	const char *fsa = fs.c_str();

	GLint passFlag=0;
	char *errorinfo;
	glShaderSource(hvs, 1, &vsa, NULL);
	glShaderSource(hfs, 1, &fsa, NULL);

	glCompileShader(hvs);
	glGetShaderiv(hvs, GL_COMPILE_STATUS, &passFlag);
	if(passFlag!=GL_TRUE)
	{
		glGetShaderiv(hvs, GL_INFO_LOG_LENGTH, &passFlag);
		errorinfo=new char[passFlag];
		glGetShaderInfoLog(hvs, passFlag, NULL, errorinfo);
		std::cerr<<errorinfo<<std::endl;
		throw GEngException("Can not compile vertex shader!");
	}

	glCompileShader(hfs);
	glGetShaderiv(hfs, GL_COMPILE_STATUS, &passFlag);
	if(passFlag!=GL_TRUE)
	{
		glGetShaderiv(hfs, GL_INFO_LOG_LENGTH, &passFlag);
		errorinfo=new char[passFlag];
		glGetShaderInfoLog(hfs, passFlag, NULL, errorinfo);
		std::cerr<<errorinfo<<std::endl;
		throw GEngException("Can not compile fragment shader!");
	}
	shadernr = glCreateProgram();
	if(shadernr==0)
		throw GEngException("Can not create final shader object!");

	glAttachShader(shadernr,hvs);
	glAttachShader(shadernr,hfs);

	glLinkProgram(shadernr);
	glGetProgramiv(shadernr, GL_LINK_STATUS, &passFlag);
	if(passFlag!=GL_TRUE)
	{
		glGetProgramiv(shadernr, GL_INFO_LOG_LENGTH, &passFlag);
		errorinfo=new char[passFlag];
		glGetProgramInfoLog(shadernr, passFlag, NULL, errorinfo);
		std::cerr<<errorinfo<<std::endl;
		throw GEngException("Can not link shader!");
	}

	glDeleteShader(hvs);
	glDeleteShader(hfs);
}



























