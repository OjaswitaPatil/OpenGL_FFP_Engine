#include "Models.h"
#include "TextRendering.h"
#include "SaveAndLoadModels.h"

void initializeModelStructureToDefaultValues(Model *model)
{
    if (model == NULL)
    {
        LOG_ERROR("initializeModelStructureToDefaultValues() -> Model pointer is NULL");
        return;
    }

    model->modeltype = INVALIDSHAPE;

    model->numberOfFaces = 0;

    model->numberOfVerticesPerFace = 0;

    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = 0.0f;

    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;

    model->rotationAngle.x = 0.0f;
    model->rotationAngle.y = 0.0f;
    model->rotationAngle.z = 0.0f;

    model->vertices = NULL;
    model->verticesSize = 0;

    model->colors = NULL;
    model->colorsSize = 0;

    model->texcoords = NULL;
    model->texcoordsSize = 0;
    model->textureVariables = NULL;

    model->normals = NULL;
    model->normalsSize = 0;

    model->customModelAttributes = NULL;
    model->customModelAttributesCount = 0;

    model->text = NULL;

    model->readyModelFileName = NULL;
    model->readyModelLLPtr = NULL;
}

void createTriangle(Model *model)
{
    if (model == NULL)
    {
        LOG_ERROR("createTriangle() -> Model pointer is NULL");
        return;
    }

    GLfloat modelVertices[] = {
        //FACE 1
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
        };

    GLfloat modelColors[] = {
        //FACE 1
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
        };

    GLfloat modelTexCoord[] = {
        //FACE 1
        0.5f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
        };

    LOG_DEBUG("*************createTriangle() started ***********");

    model->modeltype = TRIANGLE;

    model->numberOfFaces = 1;
    model->numberOfVerticesPerFace = 3;

    //allocate memory for vertices in a model struct and fill the vertices
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
    //memcpy(model->vertices, modelVertices, sizeof(GLfloat) * model->verticesSize);

    //allocate memory for colors in a model struct and fill the colrs
    model->colors = NULL;
    model->colorsSize = sizeof(modelColors) / sizeof(modelColors[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);
    if(model->colors == NULL)
    {
        LOG_ERROR("createTriangle() -> Memory allocation failed for colors of triangle model");
        if(model->vertices)
        {
            free(model->vertices);
            model->vertices = NULL;
        }
        return;
    }
    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColors[i];
    }
    //memcpy(model->colors, modelColors, sizeof(GLfloat) * model->colorsSize);

    //allocate memory for texcoords in a model struct and fill the texcords
    model->texcoords = NULL;
    model->texcoordsSize = sizeof(modelTexCoord) / sizeof(modelTexCoord[0]);
    model->texcoords = (GLfloat*)malloc(sizeof(GLfloat) * model->texcoordsSize);
    if(model->texcoords == NULL)
    {
        LOG_ERROR("createTriangle() -> Memory allocation failed for texcoords of triangle model");
        if(model->colors)
        {
            free(model->colors);
            model->colors = NULL;
        }
        if(model->vertices)
        {
            free(model->vertices);
            model->vertices = NULL;
        }
        return;
    }
    for(GLint i = 0; i < model->texcoordsSize; i++)
    {
        model->texcoords[i] = modelTexCoord[i];
    }
    //memcpy(model->texcoords, modelTexCoord, sizeof(GLfloat) * model->texcoordsSize);
    
    //allocate memory for textureVariables in a model struct and fill default values in it
    model->textureVariables = NULL;
    model->textureVariables = (GLuint*)malloc(sizeof(GLuint) * model->numberOfFaces);
    if(model->textureVariables == NULL)
    {
        LOG_ERROR("createTriangle() -> Memory allocation failed for textureVariables of triangle model");
        if(model->texcoords)
        {
            free(model->texcoords);
            model->texcoords = NULL;
        }
        if(model->colors)
        {
            free(model->colors);
            model->colors = NULL;
        }
        if(model->vertices)
        {
            free(model->vertices);
            model->vertices = NULL;
        }
        return;
    }
    for(GLint i = 0; i < model->numberOfFaces; i++)
    {
        model->textureVariables[i] = 0;
    }

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
    model->customModelAttributesCount = 0;

    model->text = NULL;
    
    model->readyModelFileName = NULL;
    model->readyModelLLPtr = NULL;

    LOG_DEBUG("*************createTriangle() completed ***********");
}

void drawTriangle(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawTriangle() started ***********");
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawTriangle()-> TRIANGLE model struct pointer %p", model);
    
    if(model->vertices == NULL || model->colors == NULL || model->texcoords == NULL || model->textureVariables == NULL)
    {
        LOG_ERROR("drawTriangle() -> Model vertices or colors or texcoords or texturevariables are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    GLint vertexIndex = 0, colorIndex = 0, texCoordIndex = 0;
    for(GLint faceIndex = 0; faceIndex < model->numberOfFaces; faceIndex++)
    {
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawTriangle()-> face %d ITERATION STARTED", faceIndex);

        BOOL EnableTexture = FALSE;

        if(model->textureVariables[faceIndex] > 0)
        {
            EnableTexture = TRUE;
            //bind texture
            glBindTexture(GL_TEXTURE_2D, model->textureVariables[faceIndex]);
            //reset color
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        }

        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TRIANGLE: texture enabled? : %d and is texture?  %d",EnableTexture, glIsTexture(model->textureVariables[faceIndex]));
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TRIANGLE: texture enabled is having GLUINT index is : %d",model->textureVariables[faceIndex]);


        glBegin(GL_TRIANGLES);
        {
            //Vertex1
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("------------");
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Printing primitive details for face %d:", faceIndex);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex], model->texcoords[texCoordIndex+1]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Color: {%lf, %lf, %lf, %lf}",model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex], model->vertices[vertexIndex+1], model->vertices[vertexIndex+2]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex], model->texcoords[texCoordIndex+1]);
            else
                glColor4f(model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            glVertex3f(model->vertices[vertexIndex], model->vertices[vertexIndex+1], model->vertices[vertexIndex+2]);

            //Vertex2
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+2], model->texcoords[texCoordIndex+3]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Color: {%lf, %lf, %lf, %lf}",model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+3], model->vertices[vertexIndex+4], model->vertices[vertexIndex+5]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+2], model->texcoords[texCoordIndex+3]);
            else
                glColor4f(model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            glVertex3f(model->vertices[vertexIndex+3], model->vertices[vertexIndex+4], model->vertices[vertexIndex+5]);


            //Vertex3
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+4], model->texcoords[texCoordIndex+5]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Color: {%lf, %lf, %lf, %lf}",model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+6], model->vertices[vertexIndex+7], model->vertices[vertexIndex+8]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("------------");

            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+4], model->texcoords[texCoordIndex+5]);
            else
                glColor4f(model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            glVertex3f(model->vertices[vertexIndex+6], model->vertices[vertexIndex+7], model->vertices[vertexIndex+8]);
        }
        glEnd();

        if(EnableTexture)
            glBindTexture(GL_TEXTURE_2D, 0);

        //offset jumps for array
        vertexIndex += 9;
        colorIndex += 12,
        texCoordIndex += 6;
    }

    glPopMatrix();
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawTriangle() completed ***********");
}

void createQuad(Model *model)
{
    GLfloat modelVertices[] = {
        //face 1
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,

        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f
        };

    GLfloat modelColors[] = {
        //face 1
        1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f
        };

    GLfloat modelTexCoord[] ={
        //face 1
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    LOG_DEBUG("*************createQuad() started ***********");

    model->modeltype = RECTANGLE;

    model->numberOfFaces = 1;
    model->numberOfVerticesPerFace = 6;

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

    //allocate memory for texcoords in a model struct and fill the texcords
    model->texcoords = NULL;
    model->texcoordsSize = sizeof(modelTexCoord) / sizeof(modelTexCoord[0]);
    model->texcoords = (GLfloat*)malloc(sizeof(GLfloat) * model->texcoordsSize);
    if(model->texcoords == NULL)
    {
        LOG_ERROR("createQuad() -> Memory allocation failed for texcoords of Quad model");
        free(model->colors);
        model->colors = NULL;
        free(model->vertices);
        model->vertices = NULL;       
        return;
    }
    for(GLint i = 0; i < model->texcoordsSize; i++)
    {
        model->texcoords[i] = modelTexCoord[i];
    }

    //allocate memory for textureVariables in a model struct and fill default values in it
    model->textureVariables = NULL;
    model->textureVariables = (GLuint*)malloc(sizeof(GLuint) * model->numberOfFaces);
    if(model->textureVariables == NULL)
    {
        LOG_ERROR("createQuad() -> Memory allocation failed for textureVariables of quad model");
        free(model->textureVariables);
        model->textureVariables = NULL;
        free(model->colors);
        model->colors = NULL;
        free(model->vertices);
        model->vertices = NULL;
        return;
    }
    for(GLint i = 0; i < model->numberOfFaces; i++)
    {
        model->textureVariables[i] = 0;
    }

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
    model->customModelAttributesCount = 0;
    model->text = NULL;
    model->readyModelFileName = NULL;
    model->readyModelLLPtr = NULL;

    LOG_DEBUG("*************createQuad() completed ***********");
}

void drawQuad(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawQuad() started ***********");

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawQuad()-> Quad model struct pointer %p", model);

    if(model->vertices == NULL || model->colors == NULL || model->texcoords == NULL || model->textureVariables == NULL)
    {
        LOG_ERROR("drawQuad() -> Model vertices or colors or texcoords or texturevariables are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    GLint vertexIndex = 0, colorIndex = 0, texCoordIndex = 0;
    for(GLint faceIndex = 0; faceIndex < model->numberOfFaces; faceIndex++)
    {
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawQuad()-> face %d ITERATION STARTED", faceIndex);

        BOOL EnableTexture = FALSE;

        if(model->textureVariables[faceIndex] > 0)
        {
            EnableTexture = TRUE;
            //bind texture
            glBindTexture(GL_TEXTURE_2D, model->textureVariables[faceIndex]);
            //reset color
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        }

        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("QUAD: texture enabled  : %d",EnableTexture);
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("QUAD: texture enabled is having GLUINT index is : %d",model->textureVariables[faceIndex]);

        glBegin(GL_TRIANGLES);
        {
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("------------");
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Printing primitive details for face %d:", faceIndex);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex], model->texcoords[texCoordIndex+1]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex], model->vertices[vertexIndex+1], model->vertices[vertexIndex+2]);

            //Vertex1
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex], model->texcoords[texCoordIndex+1]);
            else
                glColor4f(model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            glVertex3f(model->vertices[vertexIndex], model->vertices[vertexIndex+1], model->vertices[vertexIndex+2]);

            //Vertex2
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+2], model->texcoords[texCoordIndex+3]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+3], model->vertices[vertexIndex+4], model->vertices[vertexIndex+5]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+2], model->texcoords[texCoordIndex+3]);
            else
                glColor4f(model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            glVertex3f(model->vertices[vertexIndex+3], model->vertices[vertexIndex+4], model->vertices[vertexIndex+5]);


            //Vertex3
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+4], model->texcoords[texCoordIndex+5]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+6], model->vertices[vertexIndex+7], model->vertices[vertexIndex+8]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+4], model->texcoords[texCoordIndex+5]);
            else
                glColor4f(model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            glVertex3f(model->vertices[vertexIndex+6], model->vertices[vertexIndex+7], model->vertices[vertexIndex+8]);

            //Vertex4
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+6], model->texcoords[texCoordIndex+7]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex+12], model->colors[colorIndex+13], model->colors[colorIndex+14], model->colors[colorIndex+15]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+9], model->vertices[vertexIndex+10], model->vertices[vertexIndex+11]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+6], model->texcoords[texCoordIndex+7]);
            else
                glColor4f(model->colors[colorIndex+12], model->colors[colorIndex+13], model->colors[colorIndex+14], model->colors[colorIndex+15]);
            glVertex3f(model->vertices[vertexIndex+9], model->vertices[vertexIndex+10], model->vertices[vertexIndex+11]);

            //Vertex5
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+8], model->texcoords[texCoordIndex+9]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex+17], model->colors[colorIndex+18], model->colors[colorIndex+19]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+13], model->vertices[vertexIndex+14]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+8], model->texcoords[texCoordIndex+9]);
            else
                glColor4f(model->colors[colorIndex+16], model->colors[colorIndex+17], model->colors[colorIndex+18], model->colors[colorIndex+19]);
            glVertex3f(model->vertices[vertexIndex+12], model->vertices[vertexIndex+13], model->vertices[vertexIndex+14]);

            //Vertex6
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+10], model->texcoords[texCoordIndex+11]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex+20], model->colors[colorIndex+21], model->colors[colorIndex+22], model->colors[colorIndex+23]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+16], model->vertices[vertexIndex+17]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("------------");
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+10], model->texcoords[texCoordIndex+11]);
            else
                glColor4f(model->colors[colorIndex+20], model->colors[colorIndex+21], model->colors[colorIndex+22], model->colors[colorIndex+23]);
            glVertex3f(model->vertices[vertexIndex+15], model->vertices[vertexIndex+16], model->vertices[vertexIndex+17]);


        }
        glEnd();

        if(EnableTexture)
            glBindTexture(GL_TEXTURE_2D, 0);


        //offset jumps for array
        vertexIndex += 18;
        colorIndex += 24,
        texCoordIndex += 12;
    }

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

    model->numberOfFaces = 0;
    model->numberOfVerticesPerFace = 0;

    model->vertices = NULL;
    model->verticesSize = 0;

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

    model->texcoords = 0;
    model->texcoordsSize = 0;
    model->textureVariables = 0;

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
    model->customModelAttributesCount = NULL;

    //get Text
    model->text = (char*)malloc(strlen(textString) + 1);
    if(model->text == NULL)
    {
        LOG_ERROR("createText() -> Memory allocation failed for text of TEXT model");
        free(model->colors);
        model->colors = NULL;
        return;
    }
    strncpy(model->text, textString, strlen(textString));
    model->text[strlen(textString)] = '\0';  // manually null-terminate

    BuildFont();

    model->readyModelFileName = NULL;
    model->readyModelLLPtr = NULL;

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

    // static GLint textColorIndex = 0;
    // static GLint textAnimationTimerCounter = 0;
    // GLint textAnimationTimer = 500;

    // switch (textColorIndex)
    // {
    // case 0:
    //     glColor4f(model->colors[0], model->colors[1], model->colors[2], model->colors[3]);
    //     if(textAnimationTimerCounter > textAnimationTimer)
    //     {
    //         textColorIndex = (textColorIndex+1) % 4;
    //         textAnimationTimerCounter = 0;
    //     }
    //     break;
    // case 1:
    //     glColor4f(model->colors[4], model->colors[5], model->colors[6], model->colors[7]);
    //     if(textAnimationTimerCounter > textAnimationTimer)
    //     {
    //         textColorIndex = (textColorIndex+1) % 4;
    //         textAnimationTimerCounter = 0;
    //     }
    //     break;
    // case 2:
    //     glColor4f(model->colors[8], model->colors[9], model->colors[10], model->colors[11]);
    //     if(textAnimationTimerCounter > textAnimationTimer)
    //     {
    //         textColorIndex = (textColorIndex+1) % 4;
    //         textAnimationTimerCounter = 0;
    //     }
    //     break;
    // case 3:
    //     glColor4f(model->colors[12], model->colors[13], model->colors[14], model->colors[15]);
    //     if(textAnimationTimerCounter > textAnimationTimer)
    //     {
    //         textColorIndex = (textColorIndex+1) % 4;
    //         textAnimationTimerCounter = 0;
    //     }
    //     break;
    // default:
    //     break;
    // }
    // textAnimationTimerCounter++;
    // //LOG_INFO("text is -> %s", model->text);


    glColor4f(model->colors[0], model->colors[1], model->colors[2], model->colors[3]);

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
        1.0f, 1.0f, 0.0f, 1.0f
        };

     GLfloat modelTexCoord[] = {
        //FACE 1
        0.5f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        //FACE 2
        0.5f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        //FACE 3
        0.5f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        //FACE 4
        0.5f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
        };

    LOG_DEBUG("*************createPyramid() started ***********");

    model->modeltype = PYRAMID;

    model->numberOfFaces = 4;
    model->numberOfVerticesPerFace = 3;


    //allocate memory for vertices in a model struct and fill the vertices
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

    //allocate memory for colors in a model struct and fill the colrs
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

    //allocate memory for texcoords in a model struct and fill the texcords
    model->texcoords = NULL;
    model->texcoordsSize = sizeof(modelTexCoord) / sizeof(modelTexCoord[0]);
    model->texcoords = (GLfloat*)malloc(sizeof(GLfloat) * model->texcoordsSize);
    for(GLint i = 0; i < model->texcoordsSize; i++)
    {
        model->texcoords[i] = modelTexCoord[i];
    }
    //allocate memory for textureVariables in a model struct and fill default values in it
    model->textureVariables = NULL;
    model->textureVariables = (GLuint*)malloc(sizeof(GLuint) * model->numberOfFaces);
    for(GLint i = 0; i < model->numberOfFaces; i++)
    {
        model->textureVariables[i] = 0;
    }


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
    model->customModelAttributesCount = 0;

    model->text = NULL;

    model->readyModelFileName = NULL;
    model->readyModelLLPtr = NULL;

    LOG_DEBUG("*************createPyramid() completed ***********");
}

void drawPyramid(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawPyramid() started ***********");

    if(model->vertices == NULL || model->colors == NULL || model->texcoords == NULL || model->textureVariables == NULL)
    {
        LOG_ERROR("drawPyramid() -> Model vertices or colors or texcoords or texturevariables are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    GLint vertexIndex = 0, colorIndex = 0, texCoordIndex = 0;
    for(GLint faceIndex = 0; faceIndex < model->numberOfFaces; faceIndex++)
    {
        BOOL EnableTexture = FALSE;
        if( (model->textureVariables[faceIndex]) > 0)
        {
            EnableTexture = TRUE;

            //bind texture
            glBindTexture(GL_TEXTURE_2D, model->textureVariables[faceIndex]);

            //reset color
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        }

        glBegin(GL_TRIANGLES);
        {
            //Vertex1
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("------------");
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Printing primitive details :");
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex], model->texcoords[texCoordIndex+1]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Color: {%lf, %lf, %lf, %lf}",model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex], model->vertices[vertexIndex+1], model->vertices[vertexIndex+2]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex], model->texcoords[texCoordIndex+1]);
            else
                glColor4f(model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            glVertex3f(model->vertices[vertexIndex], model->vertices[vertexIndex+1], model->vertices[vertexIndex+2]);

            //Vertex2
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+2], model->texcoords[texCoordIndex+3]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Color: {%lf, %lf, %lf, %lf}",model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+3], model->vertices[vertexIndex+4], model->vertices[vertexIndex+5]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+2], model->texcoords[texCoordIndex+3]);
            else
                glColor4f(model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            glVertex3f(model->vertices[vertexIndex+3], model->vertices[vertexIndex+4], model->vertices[vertexIndex+5]);


            //Vertex3
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+4], model->texcoords[texCoordIndex+5]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Color: {%lf, %lf, %lf, %lf}",model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+6], model->vertices[vertexIndex+7], model->vertices[vertexIndex+8]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("------------");

            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+4], model->texcoords[texCoordIndex+5]);
            else
                glColor4f(model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            glVertex3f(model->vertices[vertexIndex+6], model->vertices[vertexIndex+7], model->vertices[vertexIndex+8]);
        }
        glEnd();

        if(EnableTexture)
            glBindTexture(GL_TEXTURE_2D, 0);


        //offset jumps for array
        vertexIndex += 9;
        colorIndex += 12,
        texCoordIndex += 6;
    }

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

    GLfloat modelTexCoord[] ={
        //face 1
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        //face 2
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        //face 3
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        //face 4
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        //face 5
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        //face 6
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };


    LOG_DEBUG("*************createCube() started ***********");

    model->modeltype = CUBE;

    model->numberOfFaces = 6;
    model->numberOfVerticesPerFace = 6;

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

    //allocate memory for texcoords in a model struct and fill the texcords
    model->texcoords = NULL;
    model->texcoordsSize = sizeof(modelTexCoord) / sizeof(modelTexCoord[0]);
    model->texcoords = (GLfloat*)malloc(sizeof(GLfloat) * model->texcoordsSize);
    for(GLint i = 0; i < model->texcoordsSize; i++)
    {
        model->texcoords[i] = modelTexCoord[i];
    }
    if(model->texcoords == NULL)
    {
        LOG_ERROR("createQuad() -> Memory allocation failed for texcoords of Quad model");
        free(model->colors);
        model->colors = NULL;
        free(model->vertices);
        model->vertices = NULL;
        return;
    }
    //allocate memory for textureVariables in a model struct and fill default values in it
    model->textureVariables = NULL;
    model->textureVariables = (GLuint*)malloc(sizeof(GLuint) * model->numberOfFaces);
    if(model->textureVariables == NULL)
    {
        LOG_ERROR("createQuad() -> Memory allocation failed for textureVariables of quad model");
        free(model->textureVariables);
        model->textureVariables = NULL;
        free(model->colors);
        model->colors = NULL;
        free(model->vertices);
        model->vertices = NULL;
        return;
    }
    for(GLint i = 0; i < model->numberOfFaces; i++)
    {
        model->textureVariables[i] = 0;
    }

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
    model->customModelAttributesCount = 0;

    model->text = NULL;

    model->readyModelFileName = NULL;
    model->readyModelLLPtr = NULL;

    LOG_DEBUG("*************createCube() completed ***********");
}

void drawCube(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawCube() started ***********");

    if(model->vertices == NULL || model->colors == NULL || model->texcoords == NULL || model->textureVariables == NULL)
    {
        LOG_ERROR("drawCube() -> Model vertices or colors or texcoords or texturevariables are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    GLint vertexIndex = 0, colorIndex = 0, texCoordIndex = 0;
    for(GLint faceIndex = 0; faceIndex < model->numberOfFaces; faceIndex++)
    {
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawCube()-> face %d ITERATION STARTED", faceIndex);

        BOOL EnableTexture = FALSE;

        if(model->textureVariables[faceIndex] > 0)
        {
            EnableTexture = TRUE;
            //bind texture
            glBindTexture(GL_TEXTURE_2D, model->textureVariables[faceIndex]);
            //reset color
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        }

        glBegin(GL_TRIANGLES);
        {
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("------------");
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Printing primitive details :");
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex], model->texcoords[texCoordIndex+1]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex], model->vertices[vertexIndex+1], model->vertices[vertexIndex+2]);

            //Vertex1
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex], model->texcoords[texCoordIndex+1]);
            else
                glColor4f(model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            glVertex3f(model->vertices[vertexIndex], model->vertices[vertexIndex+1], model->vertices[vertexIndex+2]);

            //Vertex2
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+2], model->texcoords[texCoordIndex+3]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+3], model->vertices[vertexIndex+4], model->vertices[vertexIndex+5]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+2], model->texcoords[texCoordIndex+3]);
            else
                glColor4f(model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            glVertex3f(model->vertices[vertexIndex+3], model->vertices[vertexIndex+4], model->vertices[vertexIndex+5]);


            //Vertex3
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+4], model->texcoords[texCoordIndex+5]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+6], model->vertices[vertexIndex+7], model->vertices[vertexIndex+8]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+4], model->texcoords[texCoordIndex+5]);
            else
                glColor4f(model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            glVertex3f(model->vertices[vertexIndex+6], model->vertices[vertexIndex+7], model->vertices[vertexIndex+8]);

            //Vertex4
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+6], model->texcoords[texCoordIndex+7]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex+12], model->colors[colorIndex+13], model->colors[colorIndex+14], model->colors[colorIndex+15]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+9], model->vertices[vertexIndex+10], model->vertices[vertexIndex+11]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+6], model->texcoords[texCoordIndex+7]);
            else
                glColor4f(model->colors[colorIndex+12], model->colors[colorIndex+13], model->colors[colorIndex+14], model->colors[colorIndex+15]);
            glVertex3f(model->vertices[vertexIndex+9], model->vertices[vertexIndex+10], model->vertices[vertexIndex+11]);

            //Vertex5
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+8], model->texcoords[texCoordIndex+9]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex+17], model->colors[colorIndex+18], model->colors[colorIndex+19]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+13], model->vertices[vertexIndex+14]);
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+8], model->texcoords[texCoordIndex+9]);
            else
                glColor4f(model->colors[colorIndex+16], model->colors[colorIndex+17], model->colors[colorIndex+18], model->colors[colorIndex+19]);
            glVertex3f(model->vertices[vertexIndex+12], model->vertices[vertexIndex+13], model->vertices[vertexIndex+14]);

            //Vertex6
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("TexCoord: {%lf, %lf}",model->texcoords[texCoordIndex+10], model->texcoords[texCoordIndex+11]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("colors: {%lf, %lf}",model->colors[colorIndex+20], model->colors[colorIndex+21], model->colors[colorIndex+22], model->colors[colorIndex+23]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("Vertices: {%lf, %lf, %lf}",model->vertices[vertexIndex+16], model->vertices[vertexIndex+17]);
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("------------");
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+10], model->texcoords[texCoordIndex+11]);
            else
                glColor4f(model->colors[colorIndex+20], model->colors[colorIndex+21], model->colors[colorIndex+22], model->colors[colorIndex+23]);
            glVertex3f(model->vertices[vertexIndex+15], model->vertices[vertexIndex+16], model->vertices[vertexIndex+17]);


        }
        glEnd();

        if(EnableTexture)
            glBindTexture(GL_TEXTURE_2D, 0);


        //offset jumps for array
        vertexIndex += 18;
        colorIndex += 24,
        texCoordIndex += 12;
    }
    glPopMatrix();

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawCube() completed ***********");
}

void createSphere(Model *model)
{
    GLfloat modelColor[] = {
        //FACE 1
        1.0f, 0.0f, 0.0f, 1.0f,
        };

    //allocate memory for colors in a model struct and fill the colrs
    model->colors = NULL;
    model->colorsSize = sizeof(modelColor) / sizeof(modelColor[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);
    if(model->colors == NULL)
    {
        LOG_ERROR("createSphere() -> Memory allocation failed for colors of sphere model");
        return;
    }
    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColor[i];
    }

    model->modeltype = SPHERE;

    model->numberOfFaces = 1;
    model->numberOfVerticesPerFace = 1;

    model->vertices = NULL;
    model->verticesSize = 0;

    model->texcoords = 0;
    model->texcoordsSize = 0;
 
    //allocate memory for textureVariables in a model struct and fill default values in it
    model->textureVariables = NULL;
    model->textureVariables = (GLuint*)malloc(sizeof(GLuint) * model->numberOfFaces);
    if(model->textureVariables == NULL)
    {
        LOG_ERROR("createSphere() -> Memory allocation failed for textureVariables of sphere model");
        free(model->textureVariables);
        model->textureVariables = NULL;
        free(model->colors);
        model->colors = NULL;
        return;
    }
    for(GLint i = 0; i < model->numberOfFaces; i++)
    {
        model->textureVariables[i] = 0;
    }

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

    model->customModelAttributesCount = 3;

    model->customModelAttributes = (float*)malloc(sizeof(float) * model->customModelAttributesCount);
    model->customModelAttributes[0] = 1.0f;   //glu fill
    model->customModelAttributes[1] = 20.0f;  //slices
    model->customModelAttributes[2] = 20.0f;  //stacks

    model->text = NULL;

    model->readyModelFileName = NULL;
    model->readyModelLLPtr = NULL;

    LOG_DEBUG("*************createSphere() completed ***********");
}

void drawSphere(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawSphere() started ***********");
    if(model->colors == NULL || model->textureVariables == NULL || model->customModelAttributes == NULL)
    {
        LOG_ERROR("drawSphere() -> Model colors or texturevariables or customattributes are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    BOOL EnableTexture = FALSE;

    if((int)model->customModelAttributes[0] == 1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Fill the sphere
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    gluQuadricNormals(quadric, GLU_SMOOTH);  // Use smooth shading for normals

    if(model->textureVariables[0] > 0)
    {
        EnableTexture = TRUE;
        //bind texture
        glBindTexture(GL_TEXTURE_2D, model->textureVariables[0]);
        //reset color
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else
    {
        glColor4f(model->colors[0], model->colors[1], model->colors[2], model->colors[3]);
    }

    gluSphere(quadric, 0.75f, model->customModelAttributes[1], model->customModelAttributes[2]);

    if(EnableTexture)
        glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawSphere() completed ***********");
}

void createCylinder(Model *model)
{
    GLfloat modelColor[] = {
        //FACE 1
        1.0f, 0.0f, 0.0f, 1.0f,
        };

    //allocate memory for colors in a model struct and fill the colrs
    model->colors = NULL;
    model->colorsSize = sizeof(modelColor) / sizeof(modelColor[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);
    if(model->colors == NULL)
    {
        LOG_ERROR("createCylinder() -> Memory allocation failed for colors of cylinder model");
        return;
    }
    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColor[i];
    }

    model->modeltype = CYLINDER;

    model->numberOfFaces = 1;
    model->numberOfVerticesPerFace = 1;

    model->vertices = NULL;
    model->verticesSize = 0;

    model->texcoords = 0;
    model->texcoordsSize = 0;

    //allocate memory for textureVariables in a model struct and fill default values in it
    model->textureVariables = NULL;
    model->textureVariables = (GLuint*)malloc(sizeof(GLuint) * model->numberOfFaces);
    if(model->textureVariables == NULL)
    {
        LOG_ERROR("createCylinder() -> Memory allocation failed for textureVariables of cylinder model");
        free(model->textureVariables);
        model->textureVariables = NULL;
        free(model->colors);
        model->colors = NULL;
        return;
    }
    for(GLint i = 0; i < model->numberOfFaces; i++)
    {
        model->textureVariables[i] = 0;
    }

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

    model->customModelAttributesCount = 6;

    model->customModelAttributes = (float*)malloc(sizeof(float) * model->customModelAttributesCount);
    model->customModelAttributes[0] = 1.0f;   //glu fill
    model->customModelAttributes[1] = 0.5f;  //1st opening
    model->customModelAttributes[2] = 0.5f;  //2nd opening
    model->customModelAttributes[3] = 4.0f;  //length
    model->customModelAttributes[4] = 20.0f;  //slices
    model->customModelAttributes[5] = 20.0f;  //stacks

    model->text = NULL;

    model->readyModelFileName = NULL;
    model->readyModelLLPtr = NULL;

    LOG_DEBUG("*************createcylinder() completed ***********");
}

void drawCylinder(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawCylinder() started ***********");
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawCylinder()-> CYLINDER model struct pointer %p", model);

    if(model->colors == NULL || model->textureVariables == NULL || model->customModelAttributes == NULL)
    {
        LOG_ERROR("drawCylinder() -> Model colors or texturevariables or customattributes are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    BOOL EnableTexture = FALSE;

    if((int)model->customModelAttributes[0] == 1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Fill the sphere
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    gluQuadricNormals(quadric, GLU_SMOOTH);  // Use smooth shading for normals

    if(model->textureVariables[0] > 0)
    {
        EnableTexture = TRUE;
        //bind texture
        glBindTexture(GL_TEXTURE_2D, model->textureVariables[0]);
        //reset color
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else
    {
        glColor4f(model->colors[0], model->colors[1], model->colors[2], model->colors[3]);
    }

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("CYLINDER: texture enabled  : %d",EnableTexture);
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("CYLINDER: texture enabled is having GLUINT index is : %d",model->textureVariables[0]);

    gluCylinder(quadric, model->customModelAttributes[1], model->customModelAttributes[2],model->customModelAttributes[3], model->customModelAttributes[4], model->customModelAttributes[5]);

    if(EnableTexture)
        glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawcylinder() completed ***********");
}

void createDisk(Model *model)
{
    LOG_DEBUG("*************createDisk() started ***********");
    GLfloat modelColor[] = {
        //FACE 1
        1.0f, 0.0f, 0.0f, 1.0f,
        };

    //allocate memory for colors in a model struct and fill the colrs
    model->colors = NULL;
    model->colorsSize = sizeof(modelColor) / sizeof(modelColor[0]);
    model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);
    if(model->colors == NULL)
    {
        LOG_ERROR("createdisk() -> Memory allocation failed for colors of disk model");
        return;
    }
    for(GLint i = 0; i < model->colorsSize; i++)
    {
        model->colors[i] = modelColor[i];
    }

    model->modeltype = DISK;

    model->numberOfFaces = 1;
    model->numberOfVerticesPerFace = 1;

    model->vertices = NULL;
    model->verticesSize = 0;

    model->texcoords = 0;
    model->texcoordsSize = 0;

    //allocate memory for textureVariables in a model struct and fill default values in it
    model->textureVariables = NULL;
    model->textureVariables = (GLuint*)malloc(sizeof(GLuint) * model->numberOfFaces);
    if(model->textureVariables == NULL)
    {
        LOG_ERROR("createdisk() -> Memory allocation failed for textureVariables of disk model");
        free(model->textureVariables);
        model->textureVariables = NULL;
        free(model->colors);
        model->colors = NULL;
        return;
    }
    for(GLint i = 0; i < model->numberOfFaces; i++)
    {
        model->textureVariables[i] = 0;
    }

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

    model->customModelAttributesCount = 5;

    model->customModelAttributes = (float*)malloc(sizeof(float) * model->customModelAttributesCount);
    model->customModelAttributes[0] = 1.0f;   //glu fill
    model->customModelAttributes[1] = 0.5f;  //inner radius
    model->customModelAttributes[2] = 2.0f;  //outer radius
    model->customModelAttributes[3] = 20.0f;  //slices
    model->customModelAttributes[4] = 20.0f;  //stack

    model->text = NULL;

    model->readyModelFileName = NULL;
    model->readyModelLLPtr = NULL;

    LOG_DEBUG("*************createdisk() completed ***********");
}

void drawDisk(Model *model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawDisk() started ***********");
    if(model->colors == NULL || model->textureVariables == NULL || model->customModelAttributes == NULL)
    {
        LOG_ERROR("drawDisk() -> Model colors or texturevariables or customattributes are NULL");
        return;
    }

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);

    BOOL EnableTexture = FALSE;

    if((int)model->customModelAttributes[0] == 1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Fill the sphere
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    gluQuadricNormals(quadric, GLU_SMOOTH);  // Use smooth shading for normals

    if(model->textureVariables[0] > 0)
    {
        EnableTexture = TRUE;
        //bind texture
        glBindTexture(GL_TEXTURE_2D, model->textureVariables[0]);
        //reset color
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else
    {
        glColor4f(model->colors[0], model->colors[1], model->colors[2], model->colors[3]);
    }

    gluDisk(quadric, model->customModelAttributes[1], model->customModelAttributes[2],model->customModelAttributes[3], model->customModelAttributes[4]);

    if(EnableTexture)
        glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawDisk() completed ***********");
}

void createReadyModel(Model* model, const char* fileName)
{
    LOG_DEBUG("*************createReadyModel() started ***********");

    model->modeltype = READYMODEL;

    model->numberOfFaces = 0;

    model->numberOfVerticesPerFace = 0;

    model->translate.x = 0.0f;
    model->translate.y = 0.0f;
    model->translate.z = 0.0f;

    model->scale.x = 1.0f;
    model->scale.y = 1.0f;
    model->scale.z = 1.0f;

    model->rotationAngle.x = 0.0f;
    model->rotationAngle.y = 0.0f;
    model->rotationAngle.z = 0.0f;

    model->vertices = NULL;
    model->verticesSize = 0;

    model->colors = NULL;
    model->colorsSize = 0;

    model->texcoords = NULL;
    model->texcoordsSize = 0;
    model->textureVariables = NULL;

    model->normals = NULL;
    model->normalsSize = 0;

    model->customModelAttributes = NULL;
    model->customModelAttributesCount = 0;

    model->text = NULL;

    LOG_DEBUG("createReadyModel() -> readymodel file %s name is getting copied model struct",fileName);
    model->readyModelFileName = (char*)malloc( (strlen(fileName)+ 1) * sizeof(char));
    strcpy(model->readyModelFileName, fileName);
    LOG_DEBUG("createReadyModel() -> readymodel file name is %s",model->readyModelFileName);

    struct CircularDoublyLinkedList *childLinkedList = NULL;
    childLinkedList = createLinkedList();

    if(childLinkedList == NULL)
    {
        LOG_ERROR("createReadyModel() -> childLinkedList is null could not create ready model");
    }
    else
    {
        BOOL loadResult = loadCSVModel(childLinkedList, model->readyModelFileName);
        model->readyModelLLPtr = childLinkedList;

        if(loadResult == FALSE)
        {
            LOG_ERROR("createReadyModel() -> readymodel loading failed");
        }
        else
        {
            LOG_INFO("createReadyModel() -> readymodel loading successfull");
        }
    }

    LOG_DEBUG("*************createReadyModel() completed ***********");
}

void drawReadyModel(Model* model)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawReadyModel() started ***********");

    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);


    if(model->readyModelLLPtr == NULL)
    {
        LOG_ERROR("drawReadyModel() -> Model readyModelLLPtr is NULL");
        return;
    }

    drawAllModels(model->readyModelLLPtr);

    glPopMatrix();

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawReadyModel() completed ***********");
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

        case SPHERE:
        drawSphere(model);
        break;

        case CYLINDER:
        drawCylinder(model);
        break;

        case DISK:
        drawDisk(model);
        break;

        case READYMODEL:
        drawReadyModel(model);
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


char* getModelNameFromModelType(ModelType modelType)
{
    char* modelIDname = NULL;
    switch(modelType)
    {
        case TRIANGLE:
            modelIDname = (char*)malloc(sizeof(char) * strlen("TRIANGLE"));
            strcpy(modelIDname, "TRIANGLE");
        break; 

        case RECTANGLE:
            modelIDname = (char*)malloc(sizeof(char) * strlen("RECTANGLE"));
            strcpy(modelIDname, "RECTANGLE");
        break; 

        case TEXT:
            modelIDname = (char*)malloc(sizeof(char) * strlen("TEXT"));
            strcpy(modelIDname, "TEXT");
        break; 

        case PYRAMID:
            modelIDname = (char*)malloc(sizeof(char) * strlen("PYRAMID"));
            strcpy(modelIDname, "PYRAMID");
        break; 

        case CUBE:
            modelIDname = (char*)malloc(sizeof(char) * strlen("CUBE"));
            strcpy(modelIDname, "CUBE");
        break; 

        case SPHERE:
            modelIDname = (char*)malloc(sizeof(char) * strlen("SPHERE"));
            strcpy(modelIDname, "SPHERE");
        break; 

        case CYLINDER:
            modelIDname = (char*)malloc(sizeof(char) * strlen("CYLINDER"));
            strcpy(modelIDname, "CYLINDER");
        break; 

        case DISK:
            modelIDname = (char*)malloc(sizeof(char) * strlen("DISK"));
            strcpy(modelIDname, "DISK");
        break; 

        case READYMODEL:
            modelIDname = (char*)malloc(sizeof(char) * strlen("READYMODEL"));
            strcpy(modelIDname, "READYMODEL");
        break;

        case INVALIDSHAPE:
            modelIDname = (char*)malloc(sizeof(char) * strlen("INVALIDSHAPE"));
            strcpy(modelIDname, "INVALIDSHAPE");
            LOG_ERROR("getModelNameFromModelType() -> INVALID SHAPE Model ID detected");
        break;


        default:
        LOG_ERROR("getModelNameFromModelType() -> cannot get modelType %d", modelType);
        break;
    }
    return modelIDname;
}

ModelType getModelTypeFromModelName(char *modelName)
{
    if(strcmp(modelName, "TRIANGLE") == 0)
        return TRIANGLE;
    else if(strcmp(modelName, "RECTANGLE") == 0)
        return RECTANGLE;
    else if(strcmp(modelName, "PYRAMID") == 0)
        return PYRAMID;
    else if(strcmp(modelName, "CUBE") == 0)
        return CUBE;
    else if(strcmp(modelName, "TEXT") == 0)
        return TEXT;
    else if(strcmp(modelName, "CYLINDER") == 0)
        return CYLINDER;
    else if(strcmp(modelName, "SPHERE") == 0)
        return SPHERE;
    else if(strcmp(modelName, "DISK") == 0)
        return DISK;
    else if(strcmp(modelName, "READYMODEL") == 0)
        return READYMODEL;
    else
        return INVALIDSHAPE;
}



