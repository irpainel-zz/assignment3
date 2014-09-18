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
#include <GL/glut.h>

// My definition
#include "define.h"
#include <iostream>
#include "string.h"
#include <glm/glm.hpp>
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"

#include "G308_Geometry.h"

#define X 0
#define Y 1
#define Z 2

namespace std {

class Display {
public:
	Display();
	virtual ~Display();
	void render();
	void rotTh(int v);
	void keyboardControl(unsigned char key);

private:
	G308_Geometry *table;
	G308_Geometry *box;
	G308_Geometry *bunny;
	G308_Geometry *sphere;
	G308_Geometry *torus;
	G308_Geometry *teapot;

	int th;

	//spot light control
	glm::vec4 spotPosition;
	glm::vec3 spotDirection;
	float spotCutoff;
	int spotSelected;
	float angleX, angleZ;


	void initTexture();
	void createPolyGeometry();
	void setLight();
	void controlSpotlight();
	void processPicking();
	void sDirection(float t, int value);

};

} /* namespace std */

#endif /* DISPLAY_H_ */
