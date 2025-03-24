#ifndef GLOBALHEADERS_H
#define GLOBALHEADERS_H

// win32 headers
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <cstring> // for memset

// openGl related header files
#include<gl/GL.h>
#include<gl/GLU.h>

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

// variables realated with file I/O
extern char gszLogFileName[];
extern FILE *gpFile;

extern HWND ghwnd; 

#endif
