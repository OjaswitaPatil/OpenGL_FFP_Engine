#ifndef MODELS_H
#define MODELS_H

#include "globalHeaders.h"
#include "Texture.h"

typedef enum
{
	TRIANGLE = 0,
	RECTANGLE,
    TEXT,
	PYRAMID,
	CUBE,
}ModelType;

typedef struct
{
	ModelType modeltype;

	GLint numberOfFaces;//for models with no fixed faces give negative value

	vec3 translate;
	vec3 scale;
	vec3 rotationAngle;

    GLfloat *vertices;
	GLint verticesSize;

    GLfloat *colors;
	GLint colorsSize;

    GLfloat *texcoords;
	GLint texcoordsSize;
	GLuint *textureVariables;

    GLfloat *normals;
	GLint normalsSize;
	
	GLfloat *customModelAttributes;
	char *text;
}Model;

void createTriangle(Model *model);
void drawTriangle(Model *model);

void createQuad(Model *model);
void drawQuad(Model *model);

void createText(Model *model);
void drawText(Model *model);

void createPyramid(Model *model);
void drawPyramid(Model *model);

void createCube(Model *model);
void drawCube(Model *model);

void drawModel();

//Grid
void drawGridAroundSelectedModel(Model *model);
void drawGridForEntireScene(void);

#endif

