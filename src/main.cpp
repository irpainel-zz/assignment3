//---------------------------------------------------------------------------
//
// Copyright (c) 2012 Taehyun Rhee
//
// This software is provided 'as-is' for assignment of COMP308
// in ECS, Victoria University of Wellington,
// without any express or implied warranty.
// In no event will the authors be held liable for any
// damages arising from the use of this software.
//
// The contents of this file may not be copied or duplicated in any form
// without the prior permission of its owner.
//
//----------------------------------------------------------------------------

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <GL/glut.h>

// My definition
#include "define.h"
#include "Display.h"
#include <iostream>

using namespace std;

// Global Variables
GLuint g_mainWnd;
GLuint g_nWinWidth  = G308_WIN_WIDTH;
GLuint g_nWinHeight = G308_WIN_HEIGHT;
Display *display = NULL;

void G308_Display() ;
void G308_Reshape(int w, int h) ;
void G308_SetCamera();
void G308_SetLight();
void keyboardListener(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(g_nWinWidth, g_nWinHeight);
    g_mainWnd = glutCreateWindow("COMP308 Assignment3");

    glutKeyboardFunc(keyboardListener);
    glutDisplayFunc(G308_Display);
    glutReshapeFunc(G308_Reshape);

    display = new Display();

	G308_SetLight();
	G308_SetCamera();
	glutMainLoop();

	if(display != NULL) delete display;

    return 0;
}

// Display function
void G308_Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_COLOR_MATERIAL);

	display->render();

//	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_LIGHTING);
//	glDisable(GL_COLOR_MATERIAL);

	glutSwapBuffers();
}

// Reshape function
void G308_Reshape(int w, int h)
{
    if (h == 0) h = 1;

	g_nWinWidth = w;
	g_nWinHeight = h;

    glViewport(0, 0, g_nWinWidth, g_nWinHeight);
}

// Set Light
void G308_SetLight()
{


}

// Set Camera Position
void G308_SetCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(G308_FOVY, (double) g_nWinWidth / (double) g_nWinHeight, G308_ZNEAR_3D, G308_ZFAR_3D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt(-30.0, 30, 50.0, 0.0, 2.5, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(-2.0, -6.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

}

void keyboardListener(unsigned char key, int x, int y) {
	/*  Exit on ESC */
	//printf("key:  %u \n", key);
	if (key==27) { //27 =- ESC key
		exit (0);
	}
	display->keyboardControl(key);
	glutPostRedisplay();
}














