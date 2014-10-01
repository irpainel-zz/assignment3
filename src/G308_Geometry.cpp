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

#include "G308_Geometry.h"


using namespace std;


G308_Geometry::G308_Geometry(const char *filename) {
//	m_pVertexArray = NULL;
//	m_pNormalArray = NULL;
//	m_pUVArray = NULL;
//	m_pTriangles = NULL;
//	m_nNumNormal = 0;
//	m_pVertexListArray = NULL;

	mode = G308_SHADE_POLYGON;

	m_nNumPoint = m_nNumUV = m_nNumPolygon = 0;
	m_glGeomListPoly = m_glGeomListWire = 0;

	ReadOBJ(filename); // 1) read OBJ function
	//CreateGLPolyGeometry(); // 2) create GL Geometry as polygon
	//CreateGLWireGeometry(); // 3) create GL Geometry as wireframe

	material = new Material();

	textureScale = 1.0;
	hasTexture = FALSE;
	hasCubemap = FALSE;

}

G308_Geometry::~G308_Geometry(void) {
	delete (material);
//	cout << "destroying geometry"<< endl;
//	if (m_pVertexArray != NULL)
//		delete[] m_pVertexArray;
//	if (m_pNormalArray != NULL)
//		delete[] m_pNormalArray;
//	if (m_pUVArray != NULL)
//		delete[] m_pUVArray;
//	if (m_pTriangles != NULL)
//		delete[] m_pTriangles;
//	if (m_pVertexListArray != NULL)
//		delete[] m_pVertexListArray;
}


void G308_Geometry::ReadOBJ(const char *filename)
{
	FILE* fp;
	char mode, vmode;
	char str[200];
	G308_UVcoord uv;
	G308_Normal tNormal;
	G308_Point tPoint;
	G308_Triangle tTriang;
	int v1, v2, v3, n1, n2, n3, t1, t2, t3;
	int numVert, numNorm, numUV, numFace;
	float x, y, z;
	float u, v;


	numVert = numNorm = numUV = numFace = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
		printf("Error reading %s file\n", filename);
	else
		printf("Reading %s file\n", filename);

	// Check number of vertex, normal, uvCoord, and Face
	while (fgets(str, 200, fp) != NULL) {
		sscanf(str, "%c%c", &mode, &vmode);
		switch (mode) {
		case 'v': /* vertex, uv, normal */
			if (vmode == 't') // uv coordinate
				numUV++;
			else if (vmode == 'n') // normal
				numNorm++;
			else if (vmode == ' ') // vertex
				numVert++;
			break;
		case 'f': /* faces */
			numFace++;
			break;
		}
	}

	m_nNumPoint = numVert;
	m_nNumUV = numUV;
	m_nNumPolygon = numFace;
	m_nNumNormal = numNorm;

	printf("Number of Point %d, UV %d, Normal %d, Face %d\n", numVert, numUV,
			numNorm, numFace);
	//-------------------------------------------------------------
	//	Allocate memory for array
	//-------------------------------------------------------------
//
//	if (m_pVertexArray != NULL)
//		delete[] m_pVertexArray;
//	m_pVertexArray = new G308_Point[m_nNumPoint];
//
//	if (m_pNormalArray != NULL)
//		delete[] m_pNormalArray;
//	m_pNormalArray = new G308_Normal[m_nNumNormal];
//
//	if (m_pUVArray != NULL)
//		delete[] m_pUVArray;
//	m_pUVArray = new G308_UVcoord[m_nNumUV];
//
//	if (m_pTriangles != NULL)
//		delete[] m_pTriangles;
//	m_pTriangles = new G308_Triangle[m_nNumPolygon];
//
//	if (m_pVertexListArray != NULL)
//		delete[] m_pVertexListArray;
//	m_pVertexListArray = new vertexListArray[m_nNumPoint];

	m_pVertexArray.reserve(m_nNumPoint);
	m_pNormalArray.reserve(m_nNumNormal);
	m_pUVArray.reserve(m_nNumUV);
	m_pUVArray.reserve(m_nNumUV);
	m_pUVArray.reserve(m_nNumPolygon);
//	m_pVertexListArray.reserve(m_nNumPoint);


	//-----------------------------------------------------------
	//	Read obj file
	//-----------------------------------------------------------
	numVert = numNorm = numUV = numFace = 0;

	fseek(fp, 0L, SEEK_SET);
	while (fgets(str, 200, fp) != NULL)
	{
		sscanf(str, "%c%c", &mode, &vmode);
		switch (mode)
		{
		case 'v': /* vertex, uv, normal */

			if (vmode == 't') // uv coordinate
			{
				sscanf(str, "vt %f %f", &uv.u, &uv.v);
				m_pUVArray.push_back(uv);
//				m_pUVArray[numUV].u = u;
//				m_pUVArray[numUV].v = v;
				numUV++;

			} else if (vmode == 'n') // normal
			{
				sscanf(str, "vn %f %f %f", &tNormal.x, &tNormal.y, &tNormal.z);
				m_pNormalArray.push_back(tNormal);
//				m_pNormalArray[numNorm].x = x;
//				m_pNormalArray[numNorm].y = y;
//				m_pNormalArray[numNorm].z = z;
				numNorm++;
			} else if (vmode == ' ') // vertex
			{
				sscanf(str, "v %f %f %f", &tPoint.x, &tPoint.y, &tPoint.z);
				m_pVertexArray.push_back(tPoint);
//				m_pVertexArray[numVert].x = x;
//				m_pVertexArray[numVert].y = y;
//				m_pVertexArray[numVert].z = z;
				numVert++;
			}
			break;
		case 'f': /* faces : stored value is index - 1 since our index starts from 0, but obj starts from 1 */

			//if no normal and UV were found, read just face
			if ((numNorm==0)&&(numUV==0)){
				sscanf(str, "f %d %d %d", &v1, &v2, &v3);
			}
			//if no normal was found, read face and uv
				else if ((numNorm==0)){
					sscanf(str, "f %d/%d/ %d/%d/ %d/%d/", &v1, &t1, &v2, &t2, &v3, &t3);
				}
			//if no uv was found, read just face and normals
					else if (numUV==0) {
						sscanf(str, "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
					}
			//read face/uv/normal
						else {
							sscanf(str, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);
						}

			tTriang.v1 = 0;
			tTriang.v2 = 0;
			tTriang.v3 = 0;
			tTriang.n1 = 0;
			tTriang.n2 = 0;
			tTriang.n3 = 0;
			tTriang.t1 = 0;
			tTriang.t2 = 0;
			tTriang.t3 = 0;

			// Vertex indicies for triangle:
			if (numVert != 0) {
				tTriang.v1 = v1 - 1;
				tTriang.v2 = v2 - 1;
				tTriang.v3 = v3 - 1;
//				m_pTriangles[numFace].v1 = v1 - 1;
//				m_pTriangles[numFace].v2 = v2 - 1;
//				m_pTriangles[numFace].v3 = v3 - 1;

//				if (numNorm == 0)
//				{
//					//push current face to face-vertex array for each vertex
//					m_pVertexListArray[v1-1].facesVertexListArray.push_back(numFace);
//					m_pVertexListArray[v2-1].facesVertexListArray.push_back(numFace);
//					m_pVertexListArray[v3-1].facesVertexListArray.push_back(numFace);
//
//					//calculate normal for the face
//					G308_Point  V1, V2, V3;
//					V1 = m_pVertexArray[m_pTriangles[numFace].v1];
//					V2 = m_pVertexArray[m_pTriangles[numFace].v2];
//					V3 = m_pVertexArray[m_pTriangles[numFace].v3];
//					m_pTriangles[numFace].faceNormal = calcNormal(V1, V2, V3);
//
//					//cout << "face normal (" << m_pTriangles[numFace].faceNormal.x <<  ", "
//					//						<< m_pTriangles[numFace].faceNormal.y <<  ", "
//					//						<< m_pTriangles[numFace].faceNormal.z <<  ")\n";
//				}
			}

			// Normal indicies for triangle
			if (numNorm != 0) {
				tTriang.n1 =  n1 - 1;
				tTriang.n2 =  n2 - 1;
				tTriang.n3 =  n3 - 1;
//				m_pTriangles[numFace].n1 = n1 - 1;
//				m_pTriangles[numFace].n2 = n2 - 1;
//				m_pTriangles[numFace].n3 = n3 - 1;
			}

			// UV indicies for triangle
			if (numUV != 0) {
				tTriang.t1 =  t1 - 1;
				tTriang.t2 =  t2 - 1;
				tTriang.t3 =  t3 - 1;
//				m_pTriangles[numFace].t1 = t1 - 1;
//				m_pTriangles[numFace].t2 = t2 - 1;
//				m_pTriangles[numFace].t3 = t3 - 1;
			}
			m_pTriangles.push_back(tTriang);
			numFace++;
			break;
		default:
			break;
		}
	}


//	for (int i=0; i<m_nNumPoint; i++)
//	{
//		cout << i << "(";
//		for(unsigned int j=0; j < m_pVertexListArray[i].facesVertexListArray.size(); j++)
//		{
//			cout<<m_pVertexListArray[i].facesVertexListArray[j]<<" ";
//		}
//		cout << ")\n";
//	}

	fclose(fp);
	printf("Reading OBJ file is DONE.\n");
}

void G308_Geometry::CreateGLPolyGeometry() {


	cout << "Creating PolyGeometry!\n";
	if (m_glGeomListPoly != 0){
		glDeleteLists(m_glGeomListPoly, 1);
	}

	// Assign a display list; return 0 if err
	m_glGeomListPoly = glGenLists(1);
	glNewList(m_glGeomListPoly, GL_COMPILE);


	int nface;
	G308_Point vertexNormalCalculated;

	for (nface = 0; nface < m_nNumPolygon; nface ++)
	{

		glShadeModel(GL_SMOOTH);
		glBegin(GL_TRIANGLES);


		if (m_nNumUV!=0){
		glTexCoord2f(m_pUVArray[m_pTriangles[nface].t1].u,
				     m_pUVArray[m_pTriangles[nface].t1].v);
		}
		if (m_nNumNormal!=0){
		glNormal3f(m_pNormalArray[m_pTriangles[nface].n1].x,
				   m_pNormalArray[m_pTriangles[nface].n1].y,
				   m_pNormalArray[m_pTriangles[nface].n1].z);
		}
//		else
//		{
//			vertexNormalCalculated = calcVertexNormal(m_pTriangles[nface].v1);
//			//cout << "normal x vertex 1: " << vertexNormalCalculated.x << "\n";
//			glNormal3f(vertexNormalCalculated.x, vertexNormalCalculated.y, vertexNormalCalculated.z);
//		}
		glVertex3f(m_pVertexArray[m_pTriangles[nface].v1].x,
				   m_pVertexArray[m_pTriangles[nface].v1].y,
				   m_pVertexArray[m_pTriangles[nface].v1].z);
		if (m_nNumUV!=0){
		glTexCoord2f(m_pUVArray[m_pTriangles[nface].t2].u,
					 m_pUVArray[m_pTriangles[nface].t2].v);
		}
		if (m_nNumNormal!=0){
		glNormal3f(m_pNormalArray[m_pTriangles[nface].n2].x,
				   m_pNormalArray[m_pTriangles[nface].n2].y,
				   m_pNormalArray[m_pTriangles[nface].n2].z);
		}
//		else {
//			vertexNormalCalculated = calcVertexNormal(m_pTriangles[nface].v2);
//			glNormal3f(vertexNormalCalculated.x, vertexNormalCalculated.y, vertexNormalCalculated.z);
//		}
		glVertex3f(m_pVertexArray[m_pTriangles[nface].v2].x,
				   m_pVertexArray[m_pTriangles[nface].v2].y,
				   m_pVertexArray[m_pTriangles[nface].v2].z);
		if (m_nNumUV!=0){
		glTexCoord2f(m_pUVArray[m_pTriangles[nface].t3].u,
					 m_pUVArray[m_pTriangles[nface].t3].v);
		}
		if (m_nNumNormal!=0){
		glNormal3f(m_pNormalArray[m_pTriangles[nface].n3].x,
				   m_pNormalArray[m_pTriangles[nface].n3].y,
				   m_pNormalArray[m_pTriangles[nface].n3].z);
		}
//		else
//		{
//			vertexNormalCalculated = calcVertexNormal(m_pTriangles[nface].v3);
//			glNormal3f(vertexNormalCalculated.x, vertexNormalCalculated.y, vertexNormalCalculated.z);
//		}
		glVertex3f(m_pVertexArray[m_pTriangles[nface].v3].x,
				   m_pVertexArray[m_pTriangles[nface].v3].y,
				   m_pVertexArray[m_pTriangles[nface].v3].z);
		glEnd();
	}

	glEndList();

}


//--------------------------------------------------------------
// [Assignment1] 
// Fill the following function to create display list
// of the obj file to show it as wireframe 
//--------------------------------------------------------------
void G308_Geometry::CreateGLWireGeometry() {
	cout << "\nCreating WireGeometry!\n";

//	if (m_glGeomListWire != 0){
//		glDeleteLists(m_glGeomListWire, 1);
//	}
//	// Assign a display list; return 0 if err
//	m_glGeomListWire = glGenLists(1);
//	glNewList(m_glGeomListWire, GL_COMPILE);
//
//	//YOUR CODE GOES HERE
//	// .....
//
//	int nface;
//	G308_Point vertexNormalCalculated;
//
//	for (nface = 0; nface < m_nNumPolygon; nface ++)
//	{
//		glShadeModel(GL_SMOOTH);
//		glBegin(GL_LINE_STRIP);
//
//		if (numNorm!=0){
//		glNormal3f(m_pNormalArray[m_pTriangles[nface].n1].x,
//				   m_pNormalArray[m_pTriangles[nface].n1].y,
//				   m_pNormalArray[m_pTriangles[nface].n1].z);
//		}
//		else
//			{
//				vertexNormalCalculated = calcVertexNormal(m_pTriangles[nface].v1);
//				//cout << "normal x vertex 1: " << vertexNormalCalculated.x << "\n";
//				glNormal3f(vertexNormalCalculated.x, vertexNormalCalculated.y, vertexNormalCalculated.z);
//			}
//		glVertex3f(m_pVertexArray[m_pTriangles[nface].v1].x,
//				   m_pVertexArray[m_pTriangles[nface].v1].y,
//				   m_pVertexArray[m_pTriangles[nface].v1].z);
//
//		if (numNorm!=0){
//		glNormal3f(m_pNormalArray[m_pTriangles[nface].n2].x,
//				   m_pNormalArray[m_pTriangles[nface].n2].y,
//				   m_pNormalArray[m_pTriangles[nface].n2].z);
//		}
//		else
//			{
//				vertexNormalCalculated = calcVertexNormal(m_pTriangles[nface].v1);
//				//cout << "normal x vertex 1: " << vertexNormalCalculated.x << "\n";
//				glNormal3f(vertexNormalCalculated.x, vertexNormalCalculated.y, vertexNormalCalculated.z);
//			}
//		glVertex3f(m_pVertexArray[m_pTriangles[nface].v2].x,
//				   m_pVertexArray[m_pTriangles[nface].v2].y,
//				   m_pVertexArray[m_pTriangles[nface].v2].z);
//
//		if (numNorm!=0){
//		glNormal3f(m_pNormalArray[m_pTriangles[nface].n3].x,
//				   m_pNormalArray[m_pTriangles[nface].n3].y,
//				   m_pNormalArray[m_pTriangles[nface].n3].z);
//		}
//		else
//			{
//				vertexNormalCalculated = calcVertexNormal(m_pTriangles[nface].v1);
//				//cout << "normal x vertex 1: " << vertexNormalCalculated.x << "\n";
//				glNormal3f(vertexNormalCalculated.x, vertexNormalCalculated.y, vertexNormalCalculated.z);
//			}
//		glVertex3f(m_pVertexArray[m_pTriangles[nface].v3].x,
//				   m_pVertexArray[m_pTriangles[nface].v3].y,
//				   m_pVertexArray[m_pTriangles[nface].v3].z);
//		glEnd();
//	}
//	glEndList();
}


//Assignment -- Calculate Normals
G308_Point G308_Geometry::calcNormal(G308_Point v1, G308_Point v2, G308_Point v3){
	G308_Point normal;
	G308_Point u;
	G308_Point v;


	//U = V2 - V1
	u.x = v2.x - v1.x;
	u.y = v2.y - v1.y;
	u.z = v2.z - v1.z;

	//V = V3 - V1
	v.x = v3.x - v1.x;
	v.y = v3.y - v1.y;
	v.z = v3.z - v1.z;

	//Nx = UyVz - UzVy
	//Ny = UzVx - UxVz
	//Nz = UxVy - UyVx
	normal.x = ((u.y*v.z) - (u.z*v.y));
	normal.y = ((u.z*v.x) - (u.x*v.z));
	normal.z = ((u.x*v.y) - (u.y*v.x));


	return normal;
}

//Assignment -- Calculate Vertex Normal
G308_Point G308_Geometry::calcVertexNormal(int vertex){
	G308_Point normal;
//	unsigned int j;
//	float length;
//
//	for(j=0; j < m_pVertexListArray[vertex].facesVertexListArray.size(); j++)
//				{
//					normal.x += m_pTriangles[m_pVertexListArray[vertex].facesVertexListArray[j]].faceNormal.x;
//					normal.y += m_pTriangles[m_pVertexListArray[vertex].facesVertexListArray[j]].faceNormal.y;
//					normal.z += m_pTriangles[m_pVertexListArray[vertex].facesVertexListArray[j]].faceNormal.z;
//
//					//cout<<m_pVertexListArray[vertex].facesVertexListArray[j]<<" ";
//				}
//	//normalizing vector
//		length = sqrt((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));
//		normal.x = normal.x/length;
//		normal.y = normal.y/length;
//		normal.z = normal.z/length;

	return normal;
}


void G308_Geometry::toggleMode() {
	if (mode == G308_SHADE_POLYGON) {
		mode = G308_SHADE_WIREFRAME;
	} else {
		mode = G308_SHADE_POLYGON;
	}
}


void G308_Geometry::RenderGeometry() {

	if (hasTexture)
	{
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glScalef(textureScale, textureScale, 1.f);
		//If we're using alpha, we need to do this
		if (t.hasAlpha) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_ALPHA);
		}
		glEnable(GL_TEXTURE_2D);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texName);
	}
	if (hasCubemap)
	{
		makeCubeMap();
	}
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, &material->ambient[0]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &material->diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &material->specular[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

	glMatrixMode(GL_MODELVIEW);
	glCallList(m_glGeomListPoly);

	if (hasTexture)
	{
		glFlush();
		if (t.hasAlpha) {
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA);
		}
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if (hasCubemap)
	{
		glDisable(GL_TEXTURE_CUBE_MAP);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
	}
}

void G308_Geometry::readTexture(char* filename, float texScale) {
	glEnable(GL_DEPTH_TEST);

	unsigned int i;
	for (i = 0; i < strlen(filename); i++) {
		if (filename[i] == '.') {
			break;
		}
	}
	char extension[5];
	strcpy(extension, &filename[i + 1]);
	//printf(extension);
	if (strcmp(extension, "jpg") == 0 || strcmp(extension, "jpeg") == 0)
		G308_ImageLoader::loadTextureFromJPEG(filename, &t);
	else if (strcmp(extension, "png") == 0)
		G308_ImageLoader::loadTextureFromPNG(filename, &t);
	else {
		printf("Invalid format. Only supports JPEG and PNG.\n");
		exit(1);
	}

	//Init the texture storage, and set some parameters.
	//(I high recommend reading up on these commands)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);



	//glGenerateMipmap(GL_TEXTURE_2D);
	//printf("version %s", glGetString(GL_VERSION));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	//Only useful for PNG files, since JPEG doesn't support alpha
	if (t.hasAlpha) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t.width, t.height, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, t.textureData);
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t.width, t.height, 0, GL_RGB,
				GL_UNSIGNED_BYTE, t.textureData);
	}

	//Once the texture has been loaded by GL, we don't need this anymore.
	free(t.textureData);

	hasTexture = TRUE;
	textureScale = texScale;
}


void G308_Geometry::makeCubeMap()
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

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
}

void G308_Geometry::loadFace(GLenum target, const char *fn)
{
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

void G308_Geometry::toggleCubemap()
{
	hasCubemap = TRUE-hasCubemap;
}










