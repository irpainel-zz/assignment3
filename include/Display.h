/*
 * Display.h
 *
 *  Created on: Sep 15, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/glut.h>

// My definition
#include "define.h"
#include "textfile.h"
#include <iostream>
#include "string.h"
#include <glm/glm.hpp>
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"

#include "Arcball.h"
#include "G308_Geometry.h"
#include "Skybox.h"

//YAW FORWARD and BACK
#define YF 0
#define YB 1
//PITCH FORWARD and BACK
#define PF 2
#define PB 3

using namespace std;

class Display {
public:
	Display();
	virtual ~Display();
	void render();
	void rotTh(int v);
	void keyboardControl(unsigned char key);
	void arcStart(int w, int h, int x, int y);
	void arcDrag(int w, int h, int x, int y);
	void setShaders();



private:
	G308_Geometry *table;
	G308_Geometry *box;
	G308_Geometry *bunny;
	G308_Geometry *sphere;
	G308_Geometry *torus;
	G308_Geometry *teapot;
	Skybox * skybox;

	int th;
	int rotate;

	Arcball * arcball;
	int resetArc;

	//spot light control
	glm::vec4 spotPosition;
	glm::vec3 spotDirection;
	float spotCutoff;
	int spotSelected;
	int spotYaw, spotPitch;
	GLUquadric* quad;

	//shader
	GLuint phong, tex, bump, cubemap;



	void initTexture();
	void createPolyGeometry();
	void setLight();
	void controlSpotlight();
	void processPicking();
	void sDirection(int value);
	void rotateTable();
	GLuint createProgram(const char ffile[],const char vfile[]);

};


#endif /* DISPLAY_H_ */
