#ifndef MODELS_H
#define MODELS_H

#include "globalHeaders.h"
#include "Texture.h"

typedef enum
{
	TRIANGLE = 0,
	RECTANGLE,
	PYRAMID,
	CUBE,
    TEXT,
	CYLINDER,
	SPHERE,
	DISK,
	READYMODEL,
	INVALIDSHAPE,
}ModelType;

typedef struct
{
	ModelType modeltype;

	GLint numberOfFaces;//for models with no fixed faces give negative value
    GLint numberOfVerticesPerFace;

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

	GLint customModelAttributesCount;
	GLfloat *customModelAttributes;

	char *text;

	char *readyModelFileName;
	struct CircularDoublyLinkedList* readyModelLLPtr;

}Model;

void initializeModelStructureToDefaultValues(Model *model);

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

void createSphere(Model *model);
void drawSphere(Model *model);

void createCylinder(Model *model);
void drawCylinder(Model *model);

void createDisk(Model *model);
void drawDisk(Model *model);

void createReadyModel(Model* model, const char* fileName);

void drawModel();

//Grid
void drawGridAroundSelectedModel(Model *model);
void drawGridForEntireScene(void);

char* getModelNameFromModelType(ModelType modelType);
ModelType getModelTypeFromModelName(char *modelName);

#endif








