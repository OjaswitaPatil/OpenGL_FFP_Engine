#include "Models.h"

Model triangle;
Model quad;

void createTriangle(Model *triangle)
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

    triangle->vertices = NULL;
    triangle->verticesSize = sizeof(triangleVertices) / sizeof(triangleVertices[0]);
    triangle->vertices = (GLfloat*)malloc(sizeof(GLfloat) * triangle->verticesSize);
    
    for(GLint i = 0; i < triangle->verticesSize; i++)
    {
        triangle->vertices[i] = triangleVertices[i];
    }

    triangle->colors = NULL;
    triangle->colorsSize = sizeof(triangleColors) / sizeof(triangleColors[0]);
    triangle->colors = (GLfloat*)malloc(sizeof(GLfloat) * triangle->colorsSize);

    for(GLint i = 0; i < triangle->colorsSize; i++)
    {
        triangle->colors[i] = triangleColors[i];
    }

    triangle->modeltype = TRIANGLE;

    triangle->translate.x = -1.5f;
    triangle->translate.y = 0.0f;
    triangle->translate.z = -6.0f;

    triangle->scale.x = 1.0f;
    triangle->scale.y = 1.0f;
    triangle->scale.z = 1.0f;

    triangle->rotationAngle.x = 0.0f;
    triangle->rotationAngle.y = 0.0f;
    triangle->rotationAngle.z = 0.0f;

    triangle->customModelAttributes = NULL;

    //texcoords
    triangle->texcoords = NULL;
    triangle->texcoordsSize = 0;

    //normals
    triangle->normals = NULL;
    triangle->normalsSize = 0;
}

void drawTriangle(Model *triangle)
{
    glLoadIdentity();
    glTranslatef(triangle->translate.x, triangle->translate.y, triangle->translate.z);
    glRotatef(triangle->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(triangle->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(triangle->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(triangle->scale.x, triangle->scale.y, triangle->scale.z);

    glBegin(GL_TRIANGLES);

    for(GLint i = 0; i < triangle->verticesSize; i+=3)
    {
        glColor3f(triangle->colors[i], triangle->colors[i+1], triangle->colors[i+2]);
        glVertex3f(triangle->vertices[i], triangle->vertices[i+1], triangle->vertices[i+2]);
    }

    glEnd();
}

void createQuad(Model *quad)
{
    GLfloat quadVertices[] = {
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
        };
    
    GLfloat quadColors[] = {
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f
        };

    quad->vertices = NULL;
    quad->verticesSize = sizeof(quadVertices) / sizeof(quadVertices[0]);
    quad->vertices = (GLfloat*)malloc(sizeof(GLfloat) * quad->verticesSize);
    
    for(GLint i = 0; i < quad->verticesSize; i++)
    {
        quad->vertices[i] = quadVertices[i];
    }

    quad->colors = NULL;
    quad->colorsSize = sizeof(quadColors) / sizeof(quadColors[0]);
    quad->colors = (GLfloat*)malloc(sizeof(GLfloat) * quad->colorsSize);

    for(GLint i = 0; i < quad->colorsSize; i++)
    {
        quad->colors[i] = quadColors[i];
    }

    quad->modeltype = RECTANGLE;

    quad->translate.x = 1.5f;
    quad->translate.y = 0.0f;
    quad->translate.z = -6.0f;

    quad->scale.x = 1.0f;
    quad->scale.y = 1.0f;
    quad->scale.z = 1.0f;

    quad->rotationAngle.x = 0.0f;
    quad->rotationAngle.y = 0.0f;
    quad->rotationAngle.z = 0.0f;

    quad->customModelAttributes = NULL;

    //texcoords
    quad->texcoords = NULL;
    quad->texcoordsSize = 0;

    //normals
    quad->normals = NULL;
    quad->normalsSize = 0;
}

void drawQuad(Model *quad)
{
    glLoadIdentity();
    glTranslatef(quad->translate.x, quad->translate.y, quad->translate.z);
    glRotatef(quad->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(quad->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(quad->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(quad->scale.x, quad->scale.y, quad->scale.z);

    glBegin(GL_QUADS);

    for(GLint i = 0; i < quad->verticesSize; i+=3)
    {
        glColor3f(quad->colors[i], quad->colors[i+1], quad->colors[i+2]);
        glVertex3f(quad->vertices[i], quad->vertices[i+1], quad->vertices[i+2]);
    }

    glEnd();
}

void drawModel(Model *model)
{
    switch(model->modeltype)
    {
        case TRIANGLE:
        drawTriangle(&triangle);
        break;

        case RECTANGLE:
        drawQuad(&quad);
        break;
    }
}




