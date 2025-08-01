#ifndef TEXTUREFUNCTIONS_H
#define TEXTUREFUNCTIONS_H


// win32 headers
#include<windows.h>

// openGl related header files
#include<gl/GL.h>
#include<gl/GLU.h>

GLuint loadGLTexture(char* textureFileName);
BOOL loadGLBMPTexture(GLuint *texture, char* imageFilePath);
BOOL loadGLPNGTexture(GLuint *texture, char* imageFilePath);

#endif

