#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "globalHeaders.h"
#include "Models.h"

struct Node
{
    Model model;
    struct Node *pre;
    struct Node *next;
};

extern struct Node *head;
extern struct Node *last;
extern struct Node *selectedmodel;

void createModel(ModelType modelType);

void drawAllModels(void);

void deleteModel(struct Node *ptr);

#endif
