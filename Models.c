#include "Models.h"

Model Triangle1;
Model Triangle2;

void createTriangle(Model *Triangle)
{
    GLfloat triangleVertices[] = {
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
        };
    
    GLfloat triangleColors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
        };

    Triangle->vertices = NULL;
    Triangle->verticesSize = sizeof(triangleVertices) / sizeof(triangleVertices[0]);
    Triangle->vertices = (GLfloat*)malloc(sizeof(GLfloat) * Triangle->verticesSize);
    
    for(GLint i = 0; i < Triangle->verticesSize; i++)
    {
        Triangle->vertices[i] = triangleVertices[i];
    }

    Triangle->colors = NULL;
    Triangle->colorsSize = sizeof(triangleColors) / sizeof(triangleColors[0]);
    Triangle->colors = (GLfloat*)malloc(sizeof(GLfloat) * Triangle->colorsSize);

    for(GLint i = 0; i < Triangle->colorsSize; i++)
    {
        Triangle->colors[i] = triangleColors[i];
    }

    Triangle->modeltype = TRIANGLE;

    Triangle->translate.x = 0.0f;
    Triangle->translate.y = 0.0f;
    Triangle->translate.z = 0.0f;

    Triangle->scale.x = 1.0f;
    Triangle->scale.y = 1.0f;
    Triangle->scale.z = 1.0f;

    Triangle->rotationAngle.x = 0.0f;
    Triangle->rotationAngle.y = 0.0f;
    Triangle->rotationAngle.z = 0.0f;

    Triangle->customModelAttributes = NULL;

    //texcoords
    Triangle->texcoords = NULL;
    Triangle->texcoordsSize = 0;

    //normals
    Triangle->normals = NULL;
    Triangle->normalsSize = 0;
}

void drawTriangle(Model *Triangle)
{
    
    glTranslatef(Triangle->translate.x, Triangle->translate.y, Triangle->translate.z);
    glRotatef(Triangle->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(Triangle->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(Triangle->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(Triangle->scale.x, Triangle->scale.y, Triangle->scale.z);

    glBegin(GL_TRIANGLES);

    for(GLint i = 0; i < Triangle->verticesSize; i+=3)
    {
        glColor3f(Triangle->colors[i], Triangle->colors[i+1], Triangle->colors[i+2]);
        glVertex3f(Triangle->vertices[i], Triangle->vertices[i+1], Triangle->vertices[i+2]);
    }

    glEnd();
}










// void drawTriangle()
// {
//     // translate triangle backword by Z
//     glTranslatef(-1.5f, 0.0f, -6.0f);
//     glRotatef(angleTriangle, 0.0f, 1.0f, 0.0f);

//     // drawing code of triangle
//     glBegin(GL_TRIANGLES);
//     glColor3f(1.0f, 0.0f, 0.0f);
//     glVertex3f(0.0f, 1.0f, 0.0f);
//     glColor3f(0.0f, 1.0f, 0.0f);
//     glVertex3f(-1.0f, -1.0f, 0.0f);
//     glColor3f(0.0f, 0.0f, 1.0f);
//     glVertex3f(1.0f, -1.0f, 0.0f);
//     glEnd();
// }

// void drawRectangle()
// {
//     // translate triangle backword x y Z
//     glTranslatef(1.5f, 0.0f, -6.0f);
//     glRotatef(angleRectangle, 1.0f, 0.0f, 0.0f);

//     // drawing code of triangle
//     glBegin(GL_QUADS);
//     glColor3f(0.0f, 0.0f, 1.0f);
//     glVertex3f(1.0f, 1.0f, 0.0f);
//     glVertex3f(-1.0f, 1.0f, 0.0f);
//     glVertex3f(-1.0f, -1.0f, 0.0f);
//     glVertex3f(1.0f, -1.0f, 0.0f);
//     glEnd();
// }
