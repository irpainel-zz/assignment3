Assignment 1 - READ ME
Author: Iury Roger Painelli
Student ID: 300333846

To show the teapot.obj and bunny_new.obj, uncomment line 140 and comment 141 in main.cpp
To show the dragon.obj, uncomment line 141 and comment 140 in main.cpp

Steps of what I did to get everything working:
-->	In order to read teapot.obj and Sphere.obj, I added to the functions CreateGLPolyGeometry() and CreateGLWireGeometry(), a for 
	 that starts in face 0 and goes until the last face, generating the normals, the UVs,
	 and the triangles (using the vertices) for the respective face.
	 
-->	In order to read bunny_new.obj, I changed the function ReadOBJ() to read a file without UVs,
	 so if zero UV is found, the function reads the faces from the obj file without the UVs.
	Example: sscanf(str, "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
	I also changed the functions CreateGLPolyGeometry() and CreateGLWireGeometry() to do not create the UVs if they were not found.
	
--> In order to read dragon.obj,  I changed the function ReadOBJ() to read a file without normals, so if zero normal is found,
	 the function reads the faces from the obj file without the normals. 
	Example: sscanf(str, "f %d/%d/ %d/%d/ %d/%d/", &v1, &t1, &v2, &t2, &v3, &t3);
	After that, the function pushes the faces to a face-vertex array, so the function calculates the face normals
	 using the function calcNormal(G308_Point v1, G308_Point v2, G308_Point v3).
	I also changed the functions CreateGLPolyGeometry() and CreateGLWireGeometry() to calculate and normalize the vertex normals
	 using the function calcVertexNormal(int vertex) for the vertices using the (previously) calculated faces' normals.
	IMPORTANT: I had to change the function G308_SetCamera() in main.cpp (line 140 and 141) to show the dragon properly. 
	 IMPORTANT: I commented the original gluLookAt() and created a new one in the next line.
	 