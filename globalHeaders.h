#ifndef GLOBALHEADERS_H
#define GLOBALHEADERS_H

// win32 headers
#include<windows.h>

#include<math.h>

#include "Logging.h"

// openGl related header files
#include<gl/GL.h>
#include<gl/GLU.h>

#define MAX_FILE_PATH_LENGTH 1024
#define MAX_NUMBER_OF_LOADED_TEXTURES 1024

typedef struct
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}vec3;

struct ScreenRotate
{
    vec3 rotate;
};
extern struct ScreenRotate screenRotate;

// opengl related global variables
extern HDC ghdc;

extern HWND ghwnd;

#endif
