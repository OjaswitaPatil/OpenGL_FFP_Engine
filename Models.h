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
    CUBE,
	LINE
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

extern Model Triangle1;
extern Model Triangle2;

void createTriangle(Model *Triangle);
void drawTriangle(Model *Triangle);




#endif

