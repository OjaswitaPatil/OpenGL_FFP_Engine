#include "DrawPrimitiveModelFunctions.h"

GLUquadric *quadric = NULL;




void drawTRIANGLEModel(Model *model)
{
    GLfloat vertices[] = {
        //FACE 1
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
        };

    GLfloat texcoords[] = {
        //FACE 1
        0.5f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
        };

    GLint vertexIndex = 0, colorIndex = 0, texCoordIndex = 0;
    for(GLint faceIndex = 0; faceIndex < model->numberOfFaces; faceIndex++)
    {
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
            //Vertex1
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex], texcoords[texCoordIndex+1]);
            else
                glColor4f(model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            glVertex3f(vertices[vertexIndex], vertices[vertexIndex+1], vertices[vertexIndex+2]);

            //Vertex2
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+2], texcoords[texCoordIndex+3]);
            else
                glColor4f(model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            glVertex3f(vertices[vertexIndex+3], vertices[vertexIndex+4], vertices[vertexIndex+5]);


            //Vertex3
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+4], texcoords[texCoordIndex+5]);
            else
                glColor4f(model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            glVertex3f(vertices[vertexIndex+6], vertices[vertexIndex+7], vertices[vertexIndex+8]);
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

void drawRECTANGLEModel(Model *model)
{
    GLfloat vertices[] = {
        //face 1
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,

        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f
        };

    GLfloat texcoords[] ={
        //face 1
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    GLint vertexIndex = 0, colorIndex = 0, texCoordIndex = 0;
    for(GLint faceIndex = 0; faceIndex < model->numberOfFaces; faceIndex++)
    {
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
            //Vertex1
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex], texcoords[texCoordIndex+1]);
            else
                glColor4f(model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            glVertex3f(vertices[vertexIndex], vertices[vertexIndex+1], vertices[vertexIndex+2]);

            //Vertex2
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+2], texcoords[texCoordIndex+3]);
            else
                glColor4f(model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            glVertex3f(vertices[vertexIndex+3], vertices[vertexIndex+4], vertices[vertexIndex+5]);


            //Vertex3
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+4], texcoords[texCoordIndex+5]);
            else
                glColor4f(model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            glVertex3f(vertices[vertexIndex+6], vertices[vertexIndex+7], vertices[vertexIndex+8]);

            //Vertex4
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+6], texcoords[texCoordIndex+7]);
            else
                glColor4f(model->colors[colorIndex+12], model->colors[colorIndex+13], model->colors[colorIndex+14], model->colors[colorIndex+15]);
            glVertex3f(vertices[vertexIndex+9], vertices[vertexIndex+10], vertices[vertexIndex+11]);

            //Vertex5
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+8], texcoords[texCoordIndex+9]);
            else
                glColor4f(model->colors[colorIndex+16], model->colors[colorIndex+17], model->colors[colorIndex+18], model->colors[colorIndex+19]);
            glVertex3f(vertices[vertexIndex+12], vertices[vertexIndex+13], vertices[vertexIndex+14]);

            //Vertex6
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+10], texcoords[texCoordIndex+11]);
            else
                glColor4f(model->colors[colorIndex+20], model->colors[colorIndex+21], model->colors[colorIndex+22], model->colors[colorIndex+23]);
            glVertex3f(vertices[vertexIndex+15], vertices[vertexIndex+16], vertices[vertexIndex+17]);


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
}

void drawPYRAMIDModel(Model *model)
{
    GLfloat vertices[] = {
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

     GLfloat texcoords[] = {
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
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex], texcoords[texCoordIndex+1]);
            else
                glColor4f(model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            glVertex3f(vertices[vertexIndex], vertices[vertexIndex+1], vertices[vertexIndex+2]);

            //Vertex2
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+2], texcoords[texCoordIndex+3]);
            else
                glColor4f(model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            glVertex3f(vertices[vertexIndex+3], vertices[vertexIndex+4], vertices[vertexIndex+5]);


            //Vertex3
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+4], texcoords[texCoordIndex+5]);
            else
                glColor4f(model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            glVertex3f(vertices[vertexIndex+6], vertices[vertexIndex+7], vertices[vertexIndex+8]);
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

void drawCUBEModel(Model *model)
{
    GLfloat vertices[] = {
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

    GLfloat texcoords[] ={
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


    GLint vertexIndex = 0, colorIndex = 0, texCoordIndex = 0;
    for(GLint faceIndex = 0; faceIndex < model->numberOfFaces; faceIndex++)
    {
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
            //Vertex1
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex], texcoords[texCoordIndex+1]);
            else
                glColor4f(model->colors[colorIndex], model->colors[colorIndex+1], model->colors[colorIndex+2], model->colors[colorIndex+3]);
            glVertex3f(vertices[vertexIndex], vertices[vertexIndex+1], vertices[vertexIndex+2]);

            //Vertex2
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+2], texcoords[texCoordIndex+3]);
            else
                glColor4f(model->colors[colorIndex+4], model->colors[colorIndex+5], model->colors[colorIndex+6], model->colors[colorIndex+7]);
            glVertex3f(vertices[vertexIndex+3], vertices[vertexIndex+4], vertices[vertexIndex+5]);


            //Vertex3
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+4], texcoords[texCoordIndex+5]);
            else
                glColor4f(model->colors[colorIndex+8], model->colors[colorIndex+9], model->colors[colorIndex+10], model->colors[colorIndex+11]);
            glVertex3f(vertices[vertexIndex+6], vertices[vertexIndex+7], vertices[vertexIndex+8]);

            //Vertex4
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+6], texcoords[texCoordIndex+7]);
            else
                glColor4f(model->colors[colorIndex+12], model->colors[colorIndex+13], model->colors[colorIndex+14], model->colors[colorIndex+15]);
            glVertex3f(vertices[vertexIndex+9], vertices[vertexIndex+10], vertices[vertexIndex+11]);

            //Vertex5
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+8], texcoords[texCoordIndex+9]);
            else
                glColor4f(model->colors[colorIndex+16], model->colors[colorIndex+17], model->colors[colorIndex+18], model->colors[colorIndex+19]);
            glVertex3f(vertices[vertexIndex+12], vertices[vertexIndex+13], vertices[vertexIndex+14]);

            //Vertex6
            if(EnableTexture)
                glTexCoord2f(texcoords[texCoordIndex+10], texcoords[texCoordIndex+11]);
            else
                glColor4f(model->colors[colorIndex+20], model->colors[colorIndex+21], model->colors[colorIndex+22], model->colors[colorIndex+23]);
            glVertex3f(vertices[vertexIndex+15], vertices[vertexIndex+16], vertices[vertexIndex+17]);


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

}

void drawSPHEREModel(Model *model)
{
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
}

void drawCYLINDERModel(Model *model)
{
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

    gluCylinder(quadric, model->customModelAttributes[1], model->customModelAttributes[2],model->customModelAttributes[3], model->customModelAttributes[4], model->customModelAttributes[5]);

    if(EnableTexture)
        glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawDISKModel(Model *model)
{
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
}
