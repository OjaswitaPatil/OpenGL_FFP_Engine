#include "linkedList.h"

struct Node *head = NULL;
struct Node *last = NULL;
struct Node *selectedmodel = head;

void createModel(ModelType modelType)
{
    struct Node *ptr =(struct Node*)malloc(sizeof(struct Node));
    ptr->model.modeltype = modelType;

    switch(modelType)
    {
        case TRIANGLE:
        createTriangle(&(ptr->model));
        break;

        case RECTANGLE:
        createQuad(&(ptr->model));
        break;

        case TEXT:
        createText(&(ptr->model));
        break;

        case PYRAMID:
        createPyramid(&ptr->model);
        break;
    }

    ptr->next = NULL;
    ptr->pre = NULL;

    if(head == NULL)
    {
        ptr->next = ptr;
        ptr->pre = ptr;
        head = ptr;
        last = ptr;
    }
    else
    {
        last->next = ptr;
        ptr->pre = last;
        ptr->next = head;
        head->pre = ptr;
        last = ptr;
    }

    selectedmodel = ptr;
}

void deleteModel(struct Node *ptr)
{
    if(ptr == NULL)
        return;

    if(head == last)
    {
        head = NULL;
        last = NULL;
    }
    else if(ptr == head)
    {
        ptr->next->pre = last;
        last->next = ptr->next;
        head = ptr->next;
    }
    else if(ptr == last)
    {
        head->pre = last->pre;
        last->pre->next = head;
        last = last->pre;
    }
    else
    {
        ptr->pre->next = ptr->next;
        ptr->next->pre = ptr->pre;
    }

    if(head != NULL)
        selectedmodel = selectedmodel->pre;
    else   
        selectedmodel = NULL;

  
    //free structre shape heap memory
    free(ptr);
}

void drawAllModels(void)
{
    void drawModel(Model *model);

    int flag = 0;
    struct Node *ptr = head;
    
    while(ptr != NULL && flag == 0)
    {
        drawModel(&(ptr->model));

        if(ptr->next == head)
           flag = 1;

        ptr= ptr->next;   
    }

    if(selectedmodel!= NULL)
        drawGridAroundSelectedModel(&(selectedmodel->model));
}



