#ifndef TEXTURE_H
#define TEXTURE_H

#include "globalHeaders.h"
#include "UtilityFunctions.h"

extern char **allTextureNames_Array;
extern GLuint *allLoadedTextureIdentifiers_Array;
extern GLint numberOfTextureAvailablesinallTexturesArray;

int addTextureNameToallTexturesArray(char *);
BOOL loadGLTexture(GLuint *texture, char* imageFilePath);
BOOL loadGLBMPTexture(GLuint *texture, char* imageFilePath);
BOOL loadGLPNGTexture(GLuint *texture, char* imageFilePath);

#endif
