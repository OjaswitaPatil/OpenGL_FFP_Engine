#ifndef DRAWPRIMITIVEMODELFUNCTIONS_H
#define DRAWPRIMITIVEMODELFUNCTIONS_H

// win32 headers
#include<windows.h>

// openGl related header files
#include<gl/GL.h>
#include<gl/GLU.h>

#include <stdlib.h>

struct Model
{
    int numberOfFaces;
	int noOfVerticesPerFace;
	GLfloat *colors;
    GLuint *textureVariables;
    GLfloat *customModelAttributes;
};

extern GLUquadric *quadric;

void drawTRIANGLEModel(Model *model);
void drawRECTANGLEModel(Model *model);
void drawPYRAMIDModel(Model *model);
void drawCUBEModel(Model *model);
void drawSPHEREModel(Model *model);
void drawCYLINDERModel(Model *model);
void drawDISKModel(Model *model);

#endif

