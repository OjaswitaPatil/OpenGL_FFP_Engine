#ifndef MODELS_H
#define MODELS_H

#include "globalHeaders.h"

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}vec3;

typedef enum
{
	TRIANGLE = 0,
	RECTANGLE,
    TEXT
}ModelType;

typedef struct
{
	ModelType modeltype;

	vec3 translate;
	vec3 scale;
	vec3 rotationAngle;

    GLfloat *vertices;
	GLint verticesSize;

    GLfloat *colors;
	GLint colorsSize;

    GLfloat *texcoords;
	GLint texcoordsSize;

    GLfloat *normals;
	GLint normalsSize;
	
	GLfloat *customModelAttributes;
}Model;

void createTriangle(Model *model);
void drawTriangle(Model *model);

void createQuad(Model *model);
void drawQuad(Model *model);

void createText(Model *model);
void drawText(Model *model);

void drawModel();

#endif

