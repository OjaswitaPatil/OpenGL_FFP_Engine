#include "Models.h"
#include "TextRendering.h"


void createTriangle(Model *model)
{
    GLfloat modelVertices[] = {
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
        };
    
    GLfloat modelColors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
        };

    model->vertices = NULL;
    model->verticesSize = sizeof(modelVertices) / sizeof(modelVertices[0]);
    model->vertices = (GLfloat*)malloc(sizeof(GLfloat) * model->verticesSize);
    
    for(GLint i = 0; i < model->verticesSize; i++)
    {
        model->vertices[i] = modelVertices[i];
    }

    model->colors = NULL;
    model->colorsSize = sizeof(modelColors) / sizeof(modelColors[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);

    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColors[i];
    }

    model->modeltype = TRIANGLE;

    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = -6.0f;

    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;

    model->rotationAngle.x = 0.0f;
    model->rotationAngle.y = 0.0f;
    model->rotationAngle.z = 0.0f;

    model->customModelAttributes = NULL;

    //texcoords
    model->texcoords = NULL;
    model->texcoordsSize = 0;

    //normals
    model->normals = NULL;
    model->normalsSize = 0;
}

void drawTriangle(Model *model)
{
    glLoadIdentity();
    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    glBegin(GL_TRIANGLES);

    for(GLint v = 0, c = 0; v < model->verticesSize; v+=3, c+=4)
    {
        glColor4f(model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
        glVertex3f(model->vertices[v], model->vertices[v+1], model->vertices[v+2]);
    }

    glEnd();
}

void createQuad(Model *model)
{
    GLfloat modelVertices[] = {
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
        };
    
    GLfloat modelColors[] = {
        1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f
        };

    model->vertices = NULL;
    model->verticesSize = sizeof(modelVertices) / sizeof(modelVertices[0]);
    model->vertices = (GLfloat*)malloc(sizeof(GLfloat) * model->verticesSize);
    
    for(GLint i = 0; i < model->verticesSize; i++)
    {
        model->vertices[i] = modelVertices[i];
    }

    model->colors = NULL;
    model->colorsSize = sizeof(modelColors) / sizeof(modelColors[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);

    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColors[i];
    }

    model->modeltype = RECTANGLE;

    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = -6.0f;

    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;

    model->rotationAngle.x = 0.0f;
    model->rotationAngle.y = 0.0f;
    model->rotationAngle.z = 0.0f;

    model->customModelAttributes = NULL;

    //texcoords
    model->texcoords = NULL;
    model->texcoordsSize = 0;

    //normals
    model->normals = NULL;
    model->normalsSize = 0;
}

void drawQuad(Model *model)
{
    glLoadIdentity();
    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    glBegin(GL_TRIANGLES);

    for(GLint v = 0, c = 0; v < model->verticesSize; v+=3, c+=4)
    {
        glColor4f(model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
        glVertex3f(model->vertices[v], model->vertices[v+1], model->vertices[v+2]);
    }

    glEnd();
}

void createText(Model *model)
{
    GLfloat modelColors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        };

    model->vertices = NULL;

    model->colors = NULL;
    model->colorsSize = sizeof(modelColors) / sizeof(modelColors[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);

    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColors[i];
    }

    model->modeltype = TEXT;

    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = -6.0f;

    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;

    model->rotationAngle.x = 0.0f;
    model->rotationAngle.y = 0.0f;
    model->rotationAngle.z = 0.0f;

    model->customModelAttributes = NULL;

    //texcoords
    model->texcoords = NULL;
    model->texcoordsSize = 0;

    //normals
    model->normals = NULL;
    model->normalsSize = 0;

    //get Text
    model->text = (char*)malloc(sizeof(textString));
    strcpy(model->text, textString);

    BuildFont();
}

void drawText(Model *model)
{
    glLoadIdentity();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    static GLint textColorIndex = 0;
    static GLint textAnimationTimerCounter = 0;
    GLint textAnimationTimer = 500;

    switch (textColorIndex)
    {
    case 0:
        glColor4f(model->colors[0], model->colors[1], model->colors[2], model->colors[3]);
        if(textAnimationTimerCounter > textAnimationTimer)
        {
            textColorIndex = (textColorIndex+1) % 4;
            textAnimationTimerCounter = 0;
        }
        break;
    case 1:
        glColor4f(model->colors[4], model->colors[5], model->colors[6], model->colors[7]);
        if(textAnimationTimerCounter > textAnimationTimer)
        {
            textColorIndex = (textColorIndex+1) % 4;
            textAnimationTimerCounter = 0;
        }
        break;
    case 2:
        glColor4f(model->colors[8], model->colors[9], model->colors[10], model->colors[11]);
        if(textAnimationTimerCounter > textAnimationTimer)
        {
            textColorIndex = (textColorIndex+1) % 4;
            textAnimationTimerCounter = 0;
        }
        break;
    case 3:
        glColor4f(model->colors[12], model->colors[13], model->colors[14], model->colors[15]);
        if(textAnimationTimerCounter > textAnimationTimer)
        {
            textColorIndex = (textColorIndex+1) % 4;
            textAnimationTimerCounter = 0;
        }
        break;    
    default:
        break;
    }
    textAnimationTimerCounter++;

    showText(model->text);
}

void drawModel(Model *model)
{
    switch(model->modeltype)
    {
        case TRIANGLE:
        drawTriangle(model);
        break;

        case RECTANGLE:
        drawQuad(model);
        break;

        case TEXT:
        drawText(model);
        break;
    }
}




