/*
 * Display.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: Iury Roger Painelli
 */

#include "Display.h"

namespace std {

Display::Display() {
	char filename[200];

	strcpy(filename, "assets/Table.obj");
	table = new G308_Geometry(filename);
	strcpy(filename, "assets/Box.obj");
	box = new G308_Geometry(filename);
	strcpy(filename, "assets/Bunny.obj");
	bunny = new G308_Geometry(filename);
	strcpy(filename, "assets/Sphere.obj");
	sphere = new G308_Geometry(filename);
	strcpy(filename, "assets/Torus.obj");
	torus = new G308_Geometry(filename);
	strcpy(filename, "assets/teapot.obj");
	teapot = new G308_Geometry(filename);

	initTexture();
	createPolyGeometry();

	//spot light config
	spotPosition = glm::vec4(0.0, 10.0, 0.0, 1.0);
	spotDirection = glm::vec3(0.0, -1.0, 0.0);
	spotCutoff = 35;
	angleX = 0;
	angleZ = 270;

}

Display::~Display() {
	cout << "destroying geometry"<< endl;
	delete (table);
	delete (box);
	delete (bunny);
	delete (sphere);
	delete (torus);
	delete (teapot);
}

void Display::render()
{
	glPushMatrix();
	setLight();
	glPopMatrix();

	glPushMatrix();
	glRotated(th,0,1,0);
		//table
		glPushMatrix();
			glScalef(1.5f,1.f,1.5f);
			table->RenderGeometry();
		glPopMatrix();
		//box
		glPushMatrix();
			glScalef(1.4f, 1.4f, 1.4f);
			glTranslatef(3.f, 1.7, -3.f);
			box->RenderGeometry();
		glPopMatrix();
		//bunny
		glPushMatrix();
			glTranslatef(0.f, 0.5, 2.f);
			bunny->RenderGeometry();
		glPopMatrix();
		//torus
		glPushMatrix();
			glScalef(1.4,1.0,1.4);
			glTranslatef(3.f, 1.0, 5.f);
			torus->RenderGeometry();
		glPopMatrix();
		//teapot
		glPushMatrix();
			glScalef(1.0,0.7,1.0);
			glTranslatef(-8.f, 0.7, -1.f);
			teapot->RenderGeometry();
		glPopMatrix();
		//sphere
		glPushMatrix();
			glScalef(1.0,0.7,1.0);
			glTranslatef(-5.f, 2.2, 5.f);
			sphere->RenderGeometry();
		glPopMatrix();

	glPopMatrix();
}
void Display::createPolyGeometry()
{
	table->CreateGLPolyGeometry();
	box->CreateGLPolyGeometry();
	bunny->CreateGLPolyGeometry();
	torus->CreateGLPolyGeometry();
	teapot->CreateGLPolyGeometry();
	sphere->CreateGLPolyGeometry();
}

void Display::initTexture()
{
	char filename[200];
	strcpy(filename, "textures/wood.jpg");
	table->readTexture(filename, 6);
	strcpy(filename, "textures/brick.jpg");
	box->readTexture(filename, 5);
	cout<<"Texture loaded"<<endl;

	//materials
	torus->material->ambient = glm::vec4(1.0, 0.f, 0.f, 1.f);
	torus->material->diffuse = glm::vec4(1.f, 0.f, 0.f, 1.f);
	torus->material->specular = glm::vec4(0.6f, 0.6f, 0.6f, 1.f);
	torus->material->shininess =50;

	bunny->material->ambient = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	bunny->material->diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	bunny->material->specular = glm::vec4(1.f, 1.f, 1.f, 1.f);
	bunny->material->shininess = 50;

	box->material->ambient = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	box->material->diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	box->material->specular = glm::vec4(1.f, 1.f, 1.f, 1.f);
	box->material->shininess = 50;

	table->material->ambient = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	table->material->diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	table->material->specular = glm::vec4(1.f, 1.f, 1.f, 1.f);
	table->material->shininess = 10;

	teapot->material->ambient = glm::vec4( 0.105882f, 0.058824f, 0.113725f, 1.0f );
	teapot->material->diffuse = glm::vec4(0.427451f, 0.470588f, 0.541176f, 1.0f );
	teapot->material->specular = glm::vec4(0.333333f, 0.333333f, 0.521569f, 1.0f );
	teapot->material->shininess = 9.84615f;

	sphere->material->ambient = glm::vec4(  0.2125f, 0.1275f, 0.054f, 1.0f  );
	sphere->material->diffuse = glm::vec4( 0.714f, 0.4284f, 0.18144f, 1.0f );
	sphere->material->specular = glm::vec4(0.393548f, 0.271906f, 0.166721f, 1.0f );
	sphere->material->shininess = 25.6f;
}

void Display::setLight()
{
	//ambient
	float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float diffuse[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float specular[] ={ 1.0f, 1.0f, 1.0f, 1.0f };
	float position[] = { 200.0f, 300.0f, 100.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);


	//point light
	float pointAmbient[] = { 0.01f, 0.01f, 0.01f, 0.0f };
	float pointDiffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float pointSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float pointPosition[] = { 10.0f, 10.0f, 10.0f, 1.0f };

	glLightfv(GL_LIGHT2, GL_AMBIENT, pointAmbient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, pointDiffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, pointSpecular);
	glLightfv(GL_LIGHT2, GL_POSITION, pointPosition);

	//directional light
	float directionalAmbient[] = { 0.1f, 0.1f, 0.1f, 0.0f };
	float directionalDiffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float directionalSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float directionalPosition[] = { 200.0f, 200.0f, 200.0f, 0.0f };

	glLightfv(GL_LIGHT3, GL_AMBIENT, directionalAmbient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, directionalDiffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, directionalSpecular);
	glLightfv(GL_LIGHT3, GL_POSITION, directionalPosition);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);


	controlSpotlight();
	glEnable(GL_LIGHT1); //spotlight
}

void Display::controlSpotlight()
{

	glm::vec3 t;
	float angle;

	float material[] = { 1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, material);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialf(GL_FRONT, GL_SHININESS, 0);

	float coneHeight = 1;
	float coneBase = coneHeight*cos(spotCutoff);

	//calculate the rotation axis and angle
	t = glm::cross(spotDirection, glm::vec3(0.0,0.0,1.0));
	angle = acos(glm::dot(glm::vec3(0.0,0.0,1.0),spotDirection));
	glm::vec3 s = spotDirection;
	angle = (angle / glm::sqrt(s.x*s.x+s.y*s.y+s.z*s.z))*(180/M_PI);

	glPushMatrix();

		glTranslatef(spotPosition.x, spotPosition.y+0.5, spotPosition.z);
		glBegin(GL_LINES);
		glVertex3f(-10, 0, 0);
		glVertex3f(100, 0, 0);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0, 0, -10.0);
		glVertex3f(0, 0, 100.0);
		glEnd();
		glRotatef(angle, t.x, t.y, t.z);
		glutSolidSphere(0.5, 10, 10);

		glPushMatrix();
			glTranslatef(0.0, 0.0, -coneHeight-0.5);
			glutWireCone(coneBase, coneHeight, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 0.0, -6.0);
			glutSolidCone(0.5, -1, 10, 10);
		glPopMatrix();


	//spot light
	float spotDiffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float spotAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	float spotSpecular[] ={ 0.7f, 0.7f, 0.7f, 1.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, &spotPosition[0]);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, &spotDirection[0]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spotDiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, spotAmbient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spotSpecular);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);

}

void Display::keyboardControl(unsigned char key)
{
	switch(key) {
		case 'q': rotTh(-5); break;
		case 'e': rotTh(5); break;
		case 'a': sDirection(1, X); break;
		case 'd': sDirection(-1, X); break;
		case 'w': sDirection(1, Z); break;
		case 's': sDirection(-1, Z); break;
		default: break;
	}
}

void Display::sDirection(float t, int value)
{
	switch (value) {
		case X:
			if (t<0)
				(angleX > -90) ? angleX+=2 : t;
			else
				(angleX < 90) ? angleX-=2 : t;
			break;
		case Z:
			if (t<0)
				(angleZ > 180) ? angleZ-=2 : t;
			else
				(angleZ < 360) ? angleZ+=2 : t;
			break;
		default:
			break;
	}
	cout << angleZ << endl;
}

void Display::rotTh(int v)
{
	this->th += v;
	this->th = th%360;
}

} /* namespace std */
