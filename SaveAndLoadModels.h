#ifndef SAVEANDLOADMODELS_H
#define SAVEANDLOADMODELS_H

#include "globalHeaders.h"
#include "linkedList.h"

#define TYPE_INT    0
#define TYPE_FLOAT  1
#define TYPE_STRING 2

#define MAX_CSV_COLUMNS 18  // Adjust as needed

extern FILE *modelFile;

int createFile(const char* filename, const char *fileMode);
void closeFile(FILE *modelFile);
BOOL saveModel(const char *fileName);
int splitStringBaseOnToken(const char* source, void* destination, int type);
BOOL loadCSVModel(const char *filename) ;


#endif

