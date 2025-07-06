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


    LOG_DEBUG("*************createTriangle() started ***********");

    model->modeltype = TRIANGLE;

    model->vertices = NULL;
    model->verticesSize = sizeof(modelVertices) / sizeof(modelVertices[0]);
    model->vertices = (GLfloat*)malloc(sizeof(GLfloat) * model->verticesSize);
    if(model->vertices == NULL)
    {
        LOG_ERROR("createTriangle() -> Memory allocation failed for vertices of triangle model");
        return;
    }
    for(GLint i = 0; i < model->verticesSize; i++)
    {
        model->vertices[i] = modelVertices[i];
    }

    model->colors = NULL;
    model->colorsSize = sizeof(modelColors) / sizeof(modelColors[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);
    if(model->colors == NULL)
    {
        LOG_ERROR("createTriangle() -> Memory allocation failed for colors of triangle model");
        free(model->vertices);
        model->vertices = NULL;
        return;
    }
    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColors[i];
    }

    //texcoords
    model->texcoords = NULL;
    model->texcoordsSize = 0;

    //normals
    model->normals = NULL;
    model->normalsSize = 0;

    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = 0.0f;

    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;

    model->rotationAngle.x = 0.0f;
    model->rotationAngle.y = 0.0f;
    model->rotationAngle.z = 0.0f;

    model->customModelAttributes = NULL;

    LOG_DEBUG("*************createTriangle() completed ***********");
}

void drawTriangle(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************createTriangle() started ***********");
    if(model->vertices == NULL || model->colors == NULL)
    {
        LOG_ERROR("drawTriangle() -> Model vertices or colors are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    glBegin(GL_TRIANGLES);

    for(GLint v = 0, c = 0; v < model->verticesSize; v+=3, c+=4)
    {
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawTriangle() -> color: { %f, %f, %f }", model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawTriangle() -> Vertex: { %f, %f, %f }", model->vertices[v], model->vertices[v+1], model->vertices[v+2]);

        glColor4f(model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
        glVertex3f(model->vertices[v], model->vertices[v+1], model->vertices[v+2]);
    }

    glEnd();

    glPopMatrix();
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************createTriangle() completed ***********");
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

    LOG_DEBUG("*************createQuad() started ***********");

    model->modeltype = RECTANGLE;

    model->vertices = NULL;
    model->verticesSize = sizeof(modelVertices) / sizeof(modelVertices[0]);
    model->vertices = (GLfloat*)malloc(sizeof(GLfloat) * model->verticesSize);
    if(model->vertices == NULL)
    {
        LOG_ERROR("createQuad() -> Memory allocation failed for vertices of Quad model");
        return;
    }
    for(GLint i = 0; i < model->verticesSize; i++)
    {
        model->vertices[i] = modelVertices[i];
    }

    model->colors = NULL;
    model->colorsSize = sizeof(modelColors) / sizeof(modelColors[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);
    if(model->colors == NULL)
    {
        LOG_ERROR("createQuad() -> Memory allocation failed for colors of Quad model");
        free(model->vertices);
        model->vertices = NULL;
        return;
    }
    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColors[i];
    }

    //texcoords
    model->texcoords = NULL;
    model->texcoordsSize = 0;

    //normals
    model->normals = NULL;
    model->normalsSize = 0;

    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = 0.0f;

    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;

    model->rotationAngle.x = 0.0f;
    model->rotationAngle.y = 0.0f;
    model->rotationAngle.z = 0.0f;

    model->customModelAttributes = NULL;

    LOG_DEBUG("*************createQuad() completed ***********");
}

void drawQuad(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawQuad() started ***********");
    if(model->vertices == NULL || model->colors == NULL)
    {
        LOG_ERROR("drawQuad() -> Model vertices or colors are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    glBegin(GL_TRIANGLES);

    for(GLint v = 0, c = 0; v < model->verticesSize; v+=3, c+=4)
    {
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawQuad() -> color: { %f, %f, %f }", model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawQuad() -> Vertex: { %f, %f, %f }", model->vertices[v], model->vertices[v+1], model->vertices[v+2]);

        glColor4f(model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
        glVertex3f(model->vertices[v], model->vertices[v+1], model->vertices[v+2]);
    }

    glEnd();

    glPopMatrix();

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawQuad() completed ***********");
}

void createText(Model *model)
{

    GLfloat modelColors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
        };

    LOG_DEBUG("*************createText() started ***********");

    model->modeltype = TEXT;

    model->vertices = NULL;

    model->colors = NULL;
    model->colorsSize = sizeof(modelColors) / sizeof(modelColors[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);
    if(model->colors == NULL)
    {
        LOG_ERROR("createText() -> Memory allocation failed for colors of TEXT model");
        return;
    }
    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColors[i];
    }

    //texcoords
    model->texcoords = NULL;
    model->texcoordsSize = 0;

    //normals
    model->normals = NULL;
    model->normalsSize = 0;

    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = 0.0f;

    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;

    model->rotationAngle.x = 0.0f;
    model->rotationAngle.y = 0.0f;
    model->rotationAngle.z = 0.0f;

    model->customModelAttributes = NULL;

    //get Text
    model->text = (char*)malloc(sizeof(textString));
    if(model->text == NULL)
    {
        LOG_ERROR("createText() -> Memory allocation failed for text of TEXT model");
        free(model->colors);
        model->colors = NULL;
        return;
    }
    strncpy(model->text, textString, strlen(model->text));

    BuildFont();

    LOG_DEBUG("*************createText() completed ***********");
}

void drawText(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawText() started ***********");
    if(model->text == NULL || model->colors == NULL)
    {
        LOG_ERROR("drawText() -> Text Model text or colors are NULL");
        return;
    }

    glPushMatrix();

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

    glPopMatrix();

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawText() completed ***********");
}

void createPyramid(Model *model)
{
    GLfloat modelVertices[] = {
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,

        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f
        };

    GLfloat modelColors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
       0.0f, 0.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        };

    LOG_DEBUG("*************createPyramid() started ***********");

    model->modeltype = PYRAMID;

    model->vertices = NULL;
    model->verticesSize = sizeof(modelVertices) / sizeof(modelVertices[0]);
    model->vertices = (GLfloat*)malloc(sizeof(GLfloat) * model->verticesSize);
    if(model->vertices == NULL)
    {
        LOG_ERROR("createPyramid() -> Memory allocation failed for vertices of PYRAMID model");
        return;
    }
    for(GLint i = 0; i < model->verticesSize; i++)
    {
        model->vertices[i] = modelVertices[i];
    }

    model->colors = NULL;
    model->colorsSize = sizeof(modelColors) / sizeof(modelColors[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);
    if(model->colors == NULL)
    {
        LOG_ERROR("createPyramid() -> Memory allocation failed for colors of PYRAMID model");
        free(model->vertices);
        model->vertices = NULL;
        return;
    }
    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColors[i];
    }

    //texcoords
    model->texcoords = NULL;
    model->texcoordsSize = 0;

    //normals
    model->normals = NULL;
    model->normalsSize = 0;

    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = 0.0f;

    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;

    model->rotationAngle.x = 0.0f;
    model->rotationAngle.y = 0.0f;
    model->rotationAngle.z = 0.0f;

    model->customModelAttributes = NULL;

    LOG_DEBUG("*************createPyramid() completed ***********");
}

void drawPyramid(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawPyramid() started ***********");

    if(model->vertices == NULL || model->colors == NULL)
    {
        LOG_ERROR("drawPyramid() -> Model vertices or colors are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    glBegin(GL_TRIANGLES);

    for(GLint v = 0, c = 0; v < model->verticesSize; v+=3, c+=4)
    {
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawPyramid() -> color: { %f, %f, %f }", model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawPyramid() -> Vertex: { %f, %f, %f }", model->vertices[v], model->vertices[v+1], model->vertices[v+2]);

        glColor4f(model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
        glVertex3f(model->vertices[v], model->vertices[v+1], model->vertices[v+2]);
    }

    glEnd();

    glPopMatrix();

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawPyramid() completed ***********");
}

void createCube(Model *model)
{
    GLfloat modelVertices[] = {
        // front
        1.0f,  1.0f,  1.0f, // top-right of front
        -1.0f,  1.0f,  1.0f, // top-left of front
        -1.0f, -1.0f,  1.0f, // bottom-left of front

        -1.0f, -1.0f,  1.0f, // bottom-left of front
        1.0f, -1.0f,  1.0f, // bottom-right of front
        1.0f,  1.0f,  1.0f, // top-right of front

        // right
        1.0f,  1.0f, -1.0f, // top-right of right
        1.0f,  1.0f,  1.0f, // top-left of right
        1.0f, -1.0f,  1.0f, // bottom-left of right

        1.0f, -1.0f,  1.0f, // bottom-left of right
        1.0f, -1.0f, -1.0f, // bottom-right of right
        1.0f,  1.0f, -1.0f, // top-right of right

        // back
        1.0f,  1.0f, -1.0f, // top-right of back
        -1.0f,  1.0f, -1.0f, // top-left of back
        -1.0f, -1.0f, -1.0f, // bottom-left of back

        -1.0f, -1.0f, -1.0f, // bottom-left of back
        1.0f, -1.0f, -1.0f, // bottom-right of back
        1.0f,  1.0f, -1.0f, // top-right of back

        // left
        -1.0f,  1.0f,  1.0f, // top-right of left
        -1.0f,  1.0f, -1.0f, // top-left of left
        -1.0f, -1.0f, -1.0f, // bottom-left of left

        -1.0f, -1.0f, -1.0f, // bottom-left of left
        -1.0f, -1.0f,  1.0f, // bottom-right of left
        -1.0f,  1.0f,  1.0f, // top-right of left

        //top
        1.0f,  1.0f, -1.0f, // top-right of top
        -1.0f,  1.0f, -1.0f, // top-left of top
        -1.0f,  1.0f,  1.0f, // bottom-left of top

        -1.0f,  1.0f,  1.0f, // bottom-left of top
        1.0f,  1.0f,  1.0f, // bottom-right of top
        1.0f,  1.0f, -1.0f, // top-right of top

        // bottom
        1.0f, -1.0f,  1.0f, // top-right of bottom
        -1.0f, -1.0f,  1.0f, // top-left of bottom
        -1.0f, -1.0f, -1.0f, // bottom-left of bottom

        -1.0f, -1.0f, -1.0f, // bottom-left of bottom
        1.0f, -1.0f, -1.0f, // bottom-right of bottom
        1.0f, -1.0f,  1.0f, // top-right of bottom
        };

    GLfloat modelColors[] = {
        // front
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        // right
        1.0f, 0.5f, 0.0f, 1.0f,
        1.0f, 0.5f, 0.0f, 1.0f,
        1.0f, 0.5f, 0.0f, 1.0f,

        1.0f, 0.5f, 0.0f, 1.0f,
        1.0f, 0.5f, 0.0f, 1.0f,
        1.0f, 0.5f, 0.0f, 1.0f,

        // back
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        // left
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,


        //Top
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        //bottom
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,

         1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f

        };


    LOG_DEBUG("*************createCube() started ***********");

    model->modeltype = CUBE;

    model->vertices = NULL;
    model->verticesSize = sizeof(modelVertices) / sizeof(modelVertices[0]);
    model->vertices = (GLfloat*)malloc(sizeof(GLfloat) * model->verticesSize);
    if(model->vertices == NULL)
    {
        LOG_ERROR("createCube() -> Memory allocation failed for vertices of CUBE model");
        return;
    }
    for(GLint i = 0; i < model->verticesSize; i++)
    {
        model->vertices[i] = modelVertices[i];
    }

    model->colors = NULL;
    model->colorsSize = sizeof(modelColors) / sizeof(modelColors[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);
    if(model->colors == NULL)
    {
        LOG_ERROR("createCube() -> Memory allocation failed for colors of CUBE model");
        free(model->vertices);
        model->vertices = NULL;
        return;
    }
    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColors[i];
    }

    //texcoords
    model->texcoords = NULL;
    model->texcoordsSize = 0;

    //normals
    model->normals = NULL;
    model->normalsSize = 0;

    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = 0.0f;

    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;

    model->rotationAngle.x = 0.0f;
    model->rotationAngle.y = 0.0f;
    model->rotationAngle.z = 0.0f;

    model->customModelAttributes = NULL;

    LOG_DEBUG("*************createCube() completed ***********");
}

void drawCube(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawCube() started ***********");

    if(model->vertices == NULL || model->colors == NULL)
    {
        LOG_ERROR("drawCube() -> Model vertices or colors are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    glBegin(GL_TRIANGLES);

    for(GLint v = 0, c = 0; v < model->verticesSize; v+=3, c+=4)
    {
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawCube() -> color: { %f, %f, %f }", model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawCube() -> Vertex: { %f, %f, %f }", model->vertices[v], model->vertices[v+1], model->vertices[v+2]);

        glColor4f(model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
        glVertex3f(model->vertices[v], model->vertices[v+1], model->vertices[v+2]);
    }

    glEnd();

    glPopMatrix();

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawCube() completed ***********");
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

        case PYRAMID:
        drawPyramid(model);
        break;

        case CUBE:
        drawCube(model);
        break;
    }
}

void drawGridAroundSelectedModel(Model *model)
{
	glPushMatrix();

	glTranslatef(model->translate.x, model->translate.y, model->translate.z);
	glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
	glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
	glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
	glScalef(model->scale.x, model->scale.y, model->scale.z);

	//X-Axis
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-3.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	//Y Axis
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glVertex3f(0.0f, -3.0f, 0.0f);
	glEnd();

	//z axis
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glVertex3f(0.0f, 0.0f, -3.0f);
	glEnd();

	glPopMatrix();
}

void drawGridForEntireScene(void)
{
    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef(screenRotate.rotate.x, 1.0f, 0.0f, 0.0f);
    glRotatef(screenRotate.rotate.y, 0.0f, 1.0f, 0.0f);
    glRotatef(screenRotate.rotate.z, 0.0f, 0.0f, 1.0f);

	//X-Axis
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glEnd();

	for(int i = 0; i <= 20; i++)
	{
		glLineWidth(1.0f);
		glBegin(GL_LINES);
		glColor3f(0.5f, 0.5f, 0.5f);

		//lines on z axis
		glVertex3f(-10.0f, 0.0f, (float)i/2);
		glVertex3f(10.0f, 0.0f, (float)i/2);

		glVertex3f(-10.0f, 0.0f, -(float)i/2);
		glVertex3f(10.0f, 0.0f, -(float)i/2);

		//lines on X axis
		glVertex3f((float)i/2, 0.0f, -10.0f);
		glVertex3f((float)i/2, 0.0f, 10.0f);

		glVertex3f(-(float)i/2, 0.0f, -10.0f);
		glVertex3f(-(float)i/2, 0.0f, 10.0f);


		glEnd();
	}


	//Y Axis
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(0.0f, -10.0f, 0.0f);
	glEnd();

	//z axis
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);
	glVertex3f(0.0f, 0.0f, -20.0f);
	glEnd();
}


