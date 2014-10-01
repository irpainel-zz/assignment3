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

#pragma once

#include "define.h"
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>


#include <iostream>
#include <string>
#include "string.h"
#include <vector>
#include "G308_ImageLoader.h"
#include "Material.h"

using namespace std;
class G308_Geometry
{
public:
	G308_Geometry(const char *filename);
	~G308_Geometry(void);

	// Array for Geometry
	vector<G308_Point> m_pVertexArray;		// Vertex Array
	vector<G308_Normal> m_pNormalArray;	// Normal Array
	vector<G308_Triangle> m_pTriangles;	// Trianglem_glGeomListMap Array
	vector<G308_UVcoord> m_pUVArray;	    // Texture Coordinate Array

//	vector<vertexListArray> m_pVertexListArray; //Face-Vertex Meshes Array

	// Data for Geoemetry
	int m_nNumPoint;
	int m_nNumUV;
	int m_nNumPolygon;
	int m_nNumNormal;

	int mode; // Which mode to display

	// Data for Rendering
	int m_glGeomListPoly;	// Display List for Polygon
	int m_glGeomListWire;	// Display List for Wireframe

	//texture
	TextureInfo t;
	TextureInfo tCubeMap;
	GLuint texCubeName;
	GLuint texName;
	int hasTexture;
	int hasCubemap;

	//material
	Material *material;

	void RenderGeometry();     // mode : G308_SHADE_POLYGON, G308_SHADE_WIREFRAME
	void toggleMode(); //Switch between showing filled polygons and wireframes
	void readTexture(char* filename, float texScale);
	void CreateGLPolyGeometry(); // [Assignment1] Create GL Display List for Polygon Geometry
	void CreateGLWireGeometry(); // [Assignment1] Create GL Display List for Wireframe Geometry
	void toggleCubemap();
private:

	float textureScale;

	void ReadOBJ(const char* filename);


	G308_Point calcNormal(G308_Point v1, G308_Point v2, G308_Point v3);
	G308_Point calcVertexNormal(int vertex);
	void loadFace(GLenum target, const char *fn);
	void makeCubeMap();
};



