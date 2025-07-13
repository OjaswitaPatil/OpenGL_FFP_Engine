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

struct CircularDoublyLinkedList
{
    struct Node *head;
    struct Node *last;
};

// extern struct Node *head;
// extern struct Node *last;
extern struct Node *selectedmodel;
// extern struct Node *saveAndLoadModelPtr;
extern struct CircularDoublyLinkedList *masterLinkedList;

struct CircularDoublyLinkedList* createLinkedList();

void createModel(struct CircularDoublyLinkedList *pCDLL, ModelType modelType);

void drawAllModels(struct CircularDoublyLinkedList *pCDLL);

void deleteModel(struct CircularDoublyLinkedList *pCDLL, struct Node *ptr);

#endif
