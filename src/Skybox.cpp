/*
 * Skybox.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: Iury Roger Painelli
 */

#include "Skybox.h"

Skybox::Skybox() {
	createSkybox();

}

Skybox::~Skybox() {
	// TODO Auto-generated destructor stub
}

void Skybox::drawBox()
{

	glDepthMask (GL_FALSE);
	glActiveTexture (GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_CUBE_MAP, texCubeName);

	glPushMatrix();
	glScalef(10, 10, 10);
	//left
	glBegin(GL_QUADS);
	       glTexCoord2f(0, 0); glVertex3f(  -10.f, -10.f, -10.f );
	       glTexCoord2f(1, 0); glVertex3f( 	 -10.f, -10.f, 10.f );
	       glTexCoord2f(1, 1); glVertex3f(   -10.f,10.f, 10.f );
	       glTexCoord2f(0, 1); glVertex3f(  -10.f,10.f, -10.f );
	glEnd();
	//front
	glBegin(GL_QUADS);
	       glTexCoord2f(0, 0); glVertex3f(   -10.f, -10.f, 10.f );
	       glTexCoord2f(1, 0); glVertex3f(  10.f, -10.f,10.f );
	       glTexCoord2f(1, 1); glVertex3f(   10.f,10.f,10.f );
	       glTexCoord2f(0, 1); glVertex3f(   -10.f,10.f, 10.f );
	glEnd();
	//right
	glBegin(GL_QUADS);
	       glTexCoord2f(0, 0); glVertex3f(  10.f, -10.f,10.f );
	       glTexCoord2f(1, 0); glVertex3f( 	10.f,-10.f,-10.f );
	       glTexCoord2f(1, 1); glVertex3f(  10.f,10.f,-10.f );
	       glTexCoord2f(0, 1); glVertex3f(   10.f, 10.f,10.f );
	glEnd();
	//back
	glBegin(GL_QUADS);
	       glTexCoord2f(0, 0); glVertex3f(  10.f, -10.f,-10.f );
	       glTexCoord2f(1, 0); glVertex3f( 	-10.f, -10.f, -10.f );
	       glTexCoord2f(1, 1); glVertex3f(  -10.f,10.f, -10.f );
	       glTexCoord2f(0, 1); glVertex3f(  10.f,10.f,-10.f );
	glEnd();
	//top
	glBegin(GL_QUADS);
	       glTexCoord2f(0, 0); glVertex3f(  -10.f, 10.f, 10.f );
	       glTexCoord2f(1, 0); glVertex3f( 	 10.f, 10.f, 10.f );
	       glTexCoord2f(1, 1); glVertex3f(   10.f, 10.f,-10.f );
	       glTexCoord2f(0, 1); glVertex3f(  -10.f, 10.f,-10.f );
	glEnd();
	//bottom
	glBegin(GL_QUADS);
	       glTexCoord2f(0, 0); glVertex3f(  -10.f,-10.f,-10.f );
	       glTexCoord2f(1, 0); glVertex3f( 	10.f,-10.f, -10.f );
	       glTexCoord2f(1, 1); glVertex3f(   10.f,-10.f, 10.f );
	       glTexCoord2f(0, 1); glVertex3f(   -10.f,-10.f,10.f );
	glEnd();
	glPopMatrix();


	glFlush();

	glDepthMask (GL_TRUE);
}

void Skybox::createSkybox()
{
	int i;
	//glEnable(GL_DEPTH_TEST);
	static GLenum faceTarget[6] = {
	  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	const char *faceFile[6] =  {
	  "textures/left.jpg",
	  "textures/right.jpg",
	  "textures/top.jpg",
	  "textures/bottom.jpg",
	  "textures/back.jpg",
	  "textures/front.jpg",
	};
	glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &texCubeName);
	for (i=0; i<6; i++) {
		loadFace(faceTarget[i], faceFile[i]);
	}

  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Skybox::loadFace(GLenum target, const char *fn)
{
	glBindTexture (GL_TEXTURE_CUBE_MAP, texCubeName);
	unsigned int i;
	char filename[50];
	strcpy(filename, fn);

		for (i = 0; i < strlen(filename); i++) {
			if (filename[i] == '.') {
				break;
			}
		}
		char extension[5];
		strcpy(extension, &filename[i + 1]);
		//printf(extension);
		if (strcmp(extension, "jpg") == 0 || strcmp(extension, "jpeg") == 0)
			G308_ImageLoader::loadTextureFromJPEG(filename, &tCubeMap);
		else if (strcmp(extension, "png") == 0)
			G308_ImageLoader::loadTextureFromPNG(filename, &tCubeMap);
		else {
			printf("Invalid format. Only supports JPEG and PNG.\n");
			exit(1);
		}

		//Only useful for PNG files, since JPEG doesn't support alpha
		if (tCubeMap.hasAlpha) {
			glTexImage2D(target, 0, GL_RGBA, tCubeMap.width, tCubeMap.height, 0, GL_RGBA,
					GL_UNSIGNED_BYTE, tCubeMap.textureData);
		} else {
			glTexImage2D(target, 0, GL_RGB, tCubeMap.width, tCubeMap.height, 0, GL_RGB,
					GL_UNSIGNED_BYTE, tCubeMap.textureData);
		}

		//Once the texture has been loaded by GL, we don't need this anymore.
		free(tCubeMap.textureData);

}
