#ifndef SAVEANDLOADMODELS_H
#define SAVEANDLOADMODELS_H

#include "globalHeaders.h"
#include "linkedList.h"

extern FILE *modelFile;

int createFile(const char* filename, const char *fileMode);
void closeFile(FILE *modelFile);
BOOL saveModel();


#endif

