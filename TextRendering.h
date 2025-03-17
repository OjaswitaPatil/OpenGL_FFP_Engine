#ifndef TEXTRENDERINGUSINGBITMAP_H
#define TEXTRENDERINGUSINGBITMAP_H

#include "globalHeaders.h"

extern GLuint  base;                           // Base Display List For The Font Set
extern GLfloat cnt1;                           // 1st Counter Used To Move Text & For Coloring
extern GLfloat cnt2;                           // 2nd Counter Used To Move Text & For Coloring
 
extern BOOL keys[256];                      // Array Used For The Keyboard Routine
extern const char* fontName;
extern const char* textString;

GLvoid BuildFont(GLvoid);
GLvoid KillFont(GLvoid);
GLvoid glPrint(const char *fmt, ...);
GLvoid showText(GLvoid);

#endif
