/*
 * Skybox.h
 *
 *  Created on: Sep 19, 2014
 *      Author: Iury Roger Painelli
 */

#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "define.h"
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>


#include <iostream>
#include <string>
#include "string.h"
#include <vector>
#include "G308_ImageLoader.h"

namespace std {

class Skybox {
public:
	Skybox();
	virtual ~Skybox();
	void drawBox();
	void createSkybox();
	void loadFace(GLenum target, const char *fn);

private:

	//texture
	TextureInfo t;
	GLuint texName;
	TextureInfo tCubeMap;
	GLuint texCubeName;
};

} /* namespace std */

#endif /* SKYBOX_H_ */
