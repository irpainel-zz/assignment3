/*
 * Display.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: Iury Roger Painelli
 */

#include "Display.h"

using namespace std;
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
	skybox = new Skybox();

	initTexture();
	createPolyGeometry();

	rotate =FALSE;

	//spot light config
	spotPosition = glm::vec4(0.0, 10.0, 0.0, 1.0);
	spotDirection = glm::vec3(0.0, -1.0, 0.0);
	spotCutoff = 35;
	spotPitch = 0;
	spotYaw = 270;

	quad = gluNewQuadric(); //Create a new quadric to allow you to draw cylinders
	if (quad == 0) {
		printf("Not enough memory to allocate space to draw\n");
		exit(EXIT_FAILURE);
	}

	//camera control
	glm::vec3 center(0,0,0);
	glm::mat4 screenToTCS= glm::mat4();
	arcball = new Arcball(center, 0.75, screenToTCS);
	resetArc = FALSE;
}

Display::~Display() {
	cout << "destroying geometry"<< endl;
	gluDeleteQuadric(quad);
	delete (table);
	delete (box);
	delete (bunny);
	delete (sphere);
	delete (torus);
	delete (teapot);
	delete (skybox);
	delete(arcball);
}

void Display::render()
{
	glPushMatrix();
	if (resetArc)
	{
		//reducing user's frustration
		glm::vec3 center(0,0,0);
		glm::mat4 screenToTCS= glm::mat4();
		delete (arcball);
		arcball = new Arcball(center, 0.75, screenToTCS);
		resetArc = FALSE;
	}
	glm::mat4 arcRotation = arcball->getTransformation();
	glMultMatrixf(&arcRotation[0][0]);
	glPushMatrix();
	setLight();
	glPopMatrix();

	glPushMatrix();
		//glUseProgram(cubemap);
		skybox->drawBox();
		glRotated(th,0,1,0);
		//table
		glPushMatrix();
			glUseProgram(tex);
			glScalef(1.5f,1.f,1.5f);
			table->RenderGeometry();
		glPopMatrix();
		//box
		glPushMatrix();
			glUseProgram(tex);
			glScalef(1.4f, 1.4f, 1.4f);
			glTranslatef(3.f, 1.7, -3.f);
			box->RenderGeometry();
		glPopMatrix();
		//bunny
		glPushMatrix();
			glUseProgram(phong);
			glTranslatef(0.f, 0.5, 2.f);
			bunny->RenderGeometry();
		glPopMatrix();
		//torus
		glPushMatrix();
			glUseProgram(bump);
			glScalef(1.4,1.0,1.4);
			glTranslatef(3.f, 1.0, 5.f);
			torus->RenderGeometry();
		glPopMatrix();
		//teapot
		glPushMatrix();
			glUseProgram(phong);
			glScalef(1.0,0.7,1.0);
			glTranslatef(-8.f, 0.7, -1.f);
			teapot->RenderGeometry();
		glPopMatrix();
		//sphere
		glPushMatrix();
			glUseProgram(phong);
			glScalef(1.0,0.7,1.0);
			glTranslatef(-5.f, 2.2, 5.f);
			sphere->RenderGeometry();
		glPopMatrix();

	glPopMatrix();
	//rotate table
	rotateTable();
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


	strcpy(filename, "textures/normal.jpg");
	torus->readTexture(filename, 1);

	cout<<"Texture loaded"<<endl;

	sphere->toggleCubemap();
	teapot->toggleCubemap();

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

void Display::setShaders()
{
	phong = createProgram("shaders/phong.frag", "shaders/phong.vert");
	tex = createProgram("shaders/phong_tex.frag", "shaders/phong_tex.vert");
	bump = createProgram("shaders/phong_bump.frag", "shaders/phong_bump.vert");
	cubemap = createProgram("shaders/skybox.frag", "shaders/skybox.vert");


}

GLuint Display::createProgram(const char ffile[],const char vfile[])
{

	GLuint program;
	GLuint v,f;
	char *vs = NULL,*fs = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead(vfile);
	fs = textFileRead(ffile);

	const char * ff = fs;
	const char * vf = vs;

	glShaderSource(v, 1, &vf,NULL);
	glShaderSource(f, 1, &ff,NULL);

	glCompileShader(v);
	glCompileShader(f);

	GLint status;
	glGetShaderiv(v, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		int loglen;
		char logbuffer[1000];
		glGetShaderInfoLog(v, sizeof(logbuffer), &loglen, logbuffer);
		fprintf(stderr, "Vertice Shader Compile Error:%d:\n%s", loglen, logbuffer);
	}

	glGetShaderiv(f, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		int loglen;
		char logbuffer[1000];
		glGetShaderInfoLog(f, sizeof(logbuffer), &loglen, logbuffer);
		fprintf(stderr, "Fragment Shader Compile Error:%d:\n%s", loglen, logbuffer);
	}

	program = glCreateProgram();
	glAttachShader(program,f);
	glAttachShader(program,v);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		int loglen;
		char logbuffer[1000];
		glGetProgramInfoLog(program, sizeof(logbuffer), &loglen, logbuffer);
		fprintf(stderr, "OpenGL Program Linker Error:\n%.*s", logbuffer);
	}
	free(vs);
	free(fs);
	return program;

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
	float x, y, z;
	float yaw = spotYaw*(M_PI/180), pitch = spotPitch*(M_PI/180);

	//Convert Euler Angles to Vector
	x = sin(pitch);
	y = sin(yaw)*cos(pitch);
	z = cos(yaw)*cos(pitch);
	//printf ("x %f, y %f, z %f\n", v.x, v.y, v.z);
	spotDirection = glm::vec3(x, y, -z);

	float material[] = { 1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, material);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialf(GL_FRONT, GL_SHININESS, 0);

	float coneHeight = 1;
	float coneBase = coneHeight*tan(spotCutoff*(M_PI/180));

	glPushMatrix();
		glTranslatef(spotPosition.x, spotPosition.y, spotPosition.z);
		glRotatef(spotPitch, 0, 0, 1);
		glRotatef(spotYaw, 1, 0, 0);
		glutSolidSphere(0.5, 10, 10);
		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, 0, -1.5);
			gluCylinder(quad, 0.1, 0.1, 3, 10, 10);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 0.0, -coneHeight-0.5);
			glutWireCone(coneBase, coneHeight, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 0.0, -6.0);
			glutSolidCone(0.5, -1, 10, 10);
		glPopMatrix();
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
		case 'a': sDirection(PF); break;
		case 'd': sDirection(PB); break;
		case 'w': sDirection(YF); break;
		case 's': sDirection(YB); break;
		case 'z': spotCutoff++; break;
		case 'x': spotCutoff--; break;
		case 'j': spotPosition.x-=0.5; break;
		case 'l': spotPosition.x+=0.5; break;
		case 'k': spotPosition.z+=0.5; break;
		case 'i': spotPosition.z-=0.5; break;
		case 'u': spotPosition.y+=0.5; break;
		case 'o': spotPosition.y-=0.5; break;
		case 't': rotate= TRUE-rotate; break;
		case 'r': resetArc = TRUE; break;
		default: break;
	}
}

void Display::sDirection(int value)
{
	switch (value) {
		case PF:	spotPitch += 2; break;
		case PB: spotPitch -= 2; break;
		case YF: spotYaw += 2; break;
		case YB: spotYaw -= 2; break;
		default:
			break;
	}
	spotPitch = spotPitch % 360;
	spotYaw = spotYaw % 360;
}

void Display::rotTh(int v)
{
	this->th += v;
	this->th = th%360;
}

void Display::rotateTable()
{
	if (rotate)
	{
		this->th += 2;
		if (this->th >= 360)
		{
			rotate = FALSE;
			this->th = 0;
		}
		glutPostRedisplay();
	}
}

void Display::arcStart(int w, int h, int x, int y)
{
	glm::vec2 coords(0,0);
	coords.x = (x / ((w - 1.0f) * 0.5f) - 1.0f) * (-1);
	coords.y = (1.0f - y / ((h - 1.0f) * 0.5f)) * (-1);
	arcball->beginDrag(coords);
}

void Display::arcDrag(int w, int h, int x, int y)
{
	glm::vec2 coords(0,0);
	coords.x = (x / ((w - 1.0f) * 0.5f) - 1.0f) * (-1);
	coords.y = (1.0f - y / ((h - 1.0f) * 0.5f)) * (-1);
	arcball->drag(coords);
}


