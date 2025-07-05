#include "Models.h"
#include "TextRendering.h"

void createTriangle(Model *model)
{
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
    
    // model->numberOfFaces = 1;


    // //allocate memory for vertices in a model struct and fill the vertices 
    // model->vertices = NULL;
    // model->verticesSize = sizeof(modelVertices) / sizeof(modelVertices[0]);
    // model->vertices = (GLfloat*)malloc(sizeof(GLfloat) * model->verticesSize);
    // for(GLint i = 0; i < model->verticesSize; i++)
    // {
    //     model->vertices[i] = modelVertices[i];
    // }

    // //allocate memory for colors in a model struct and fill the colrs
    // model->colors = NULL;
    // model->colorsSize = sizeof(modelColors) / sizeof(modelColors[0]);
    // model->colors = (GLfloat*)malloc(sizeof(GLfloat) * model->colorsSize);
    // for(GLint i = 0; i < model->colorsSize; i++)
    // {
    //     model->colors[i] = modelColors[i];
    // }

    // //allocate memory for texcoords in a model struct and fill the texcords
    // model->texcoords = NULL;
    // model->texcoordsSize = sizeof(modelTexCoord) / sizeof(modelTexCoord[0]);
    // model->texcoords = (GLfloat*)malloc(sizeof(GLfloat) * model->texcoordsSize);
    // for(GLint i = 0; i < model->texcoordsSize; i++)
    // {
    //     model->texcoords[i] = modelTexCoord[i];
    // }
    // //allocate memory for textureVariables in a model struct and fill default values in it 
    // model->textureVariables = NULL;
    // model->textureVariables = (GLuint*)malloc(sizeof(GLuint) * model->numberOfFaces);
    // for(GLint i = 0; i < model->numberOfFaces; i++)
    // {
    //     model->textureVariables[i] = -1;
    // }

    // //normals
    // model->normals = NULL;
    // model->normalsSize = 0;

    // model->modeltype = TRIANGLE;

    // model->translate.x = 0.0f;
    // model->translate.y = 0.0f;
    // model->translate.z = 0.0f;

    // model->scale.x = 1.0f;
    // model->scale.y = 1.0f;
    // model->scale.z = 1.0f;

    // model->rotationAngle.x = 0.0f;
    // model->rotationAngle.y = 0.0f;
    // model->rotationAngle.z = 0.0f;

    // model->customModelAttributes = NULL;
}

void drawTriangle(Model *model)
{
    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
    glRotatef(model->rotationAngle.x, 1.0f, 0.0f, 0.0f);
    glRotatef(model->rotationAngle.y, 0.0f, 1.0f, 0.0f);
    glRotatef(model->rotationAngle.z, 0.0f, 0.0f, 1.0f);
    glScalef(model->scale.x, model->scale.y, model->scale.z);


    // glBindTexture(GL_TEXTURE_2D, allLoadedTextureIdentifiers_Array[2]);
    // glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    // glBegin(GL_TRIANGLES);

    // for(GLint v = 0, c = 0, tc = 0; v < model->verticesSize; v+=3, c+=4, tc+=2)
    // {
    //     glTexCoord2f(model->texcoords[tc], model->texcoords[tc+1]);
    //     //glColor4f(model->colors[c], model->colors[c+1], model->colors[c+2], model->colors[c+3]);
    //     glVertex3f(model->vertices[v], model->vertices[v+1], model->vertices[v+2]);

    //     // fprintf(gpFile, "[DEBUG] &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    //     // fprintf(gpFile, "[DEBUG]Printing primitive details :\n");
    //     // fprintf(gpFile, "[DEBUG]TexCoord: {%lf, %lf}\n",model->texcoords[tc], model->texcoords[tc+1]);
    //     // fprintf(gpFile, "[DEBUG]Vertices: {%lf, %lf, %lf}\n",model->vertices[v], model->vertices[v+1], model->vertices[v+2]);
    //     // fprintf(gpFile, "[DEBUG] &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    // }

    // glEnd();
    // glBindTexture(GL_TEXTURE_2D, 0);



    GLint vertexIndex = 0, colorIndex = 0, texCoordIndex = 0;
    for(GLint faceIndex = 0; faceIndex < model->numberOfFaces; faceIndex++)
    {
        BOOL EnableTexture = FALSE;
        if( (model->textureVariables[faceIndex]) > 0)
        {
            EnableTexture = TRUE;

            //bind texture
            glBindTexture(GL_TEXTURE_2D, allLoadedTextureIdentifiers_Array[model->textureVariables[faceIndex]]);

            //reset color
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        }
        
        glBegin(GL_TRIANGLES);
        {
            //Vertex1
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex], model->texcoords[texCoordIndex+1]);
            else
                glColor4f(model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            glVertex3f(model->vertices[vertexIndex], model->vertices[vertexIndex+1], model->vertices[vertexIndex+2]);

            //Vertex2
            if(EnableTexture)
                glTexCoord2f(model->texcoords[texCoordIndex+2], model->texcoords[texCoordIndex+3]);
            else
                glColor4f(model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            glVertex3f(model->vertices[vertexIndex+3], model->vertices[vertexIndex+4], model->vertices[vertexIndex+5]);

            //Vertex3
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
    model->translate.z = 0.0f;

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
    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
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

    glPopMatrix();
}

void createText(Model *model)
{
    
    GLfloat modelColors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
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
    model->translate.z = 0.0f;

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
    model->translate.z = 0.0f;

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

void drawPyramid(Model *model)
{
    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
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

    glPopMatrix();
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
    model->translate.z = 0.0f;

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

void drawCube(Model *model)
{
    glPushMatrix();

    glTranslatef(model->translate.x, model->translate.y, model->translate.z);
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

    glPopMatrix();
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



