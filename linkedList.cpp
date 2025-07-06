#include "linkedList.h"

struct Node *head = NULL;
struct Node *last = NULL;
struct Node *selectedmodel = head;

void createModel(ModelType modelType)
{
    LOG_DEBUG("*************createModel() started ***********");

    struct Node *ptr =(struct Node*)malloc(sizeof(struct Node));
    if(ptr == NULL)
    {
        LOG_ERROR("createModel() -> Memory allocation failed for Node");
        return;
    }
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

        case CUBE:
        createCube(&ptr->model);
        break;
    }

    ptr->next = NULL;
    ptr->pre = NULL;

    if(head == NULL)
    {
        LOG_DEBUG("createModel() -> First Node in LL created");
        ptr->next = ptr;
        ptr->pre = ptr;
        head = ptr;
        last = ptr;
    }
    else
    {
        LOG_DEBUG("createModel() -> second and + Node in LL created");
        last->next = ptr;
        ptr->pre = last;
        ptr->next = head;
        head->pre = ptr;
        last = ptr;
    }

    selectedmodel = ptr;

    LOG_DEBUG("*************createModel() completed ***********");
}

void deleteModel(struct Node *ptr)
{
    LOG_DEBUG("*************deleteModel() started ***********");

    if(ptr == NULL)
    {
        LOG_WARN("deleteModel() -> Pointer to Node is NULL");
        return;
    }


    if(head == last)
    {
        head = NULL;
        last = NULL;
        LOG_DEBUG("deleteModel() -> No Node avaialble in LL for deletion");
    }
    else if(ptr == head)
    {
        ptr->next->pre = last;
        last->next = ptr->next;
        head = ptr->next;
        LOG_DEBUG("deleteModel() -> Head Node deleted");
    }
    else if(ptr == last)
    {
        head->pre = last->pre;
        last->pre->next = head;
        last = last->pre;
        LOG_DEBUG("deleteModel() -> LAST Node deleted");
    }
    else
    {
        ptr->pre->next = ptr->next;
        ptr->next->pre = ptr->pre;
        LOG_DEBUG("deleteModel() -> Middle Node deleted");
    }

    if(head != NULL)
        selectedmodel = selectedmodel->pre;
    else
        selectedmodel = NULL;


    //free structre shape heap memory
    free(ptr);

    LOG_DEBUG("*************deleteModel() completed ***********");
}

void drawAllModels(void)
{
    void drawModel(Model *model);

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawAllModels() started ***********");

    int flag = 0;
    struct Node *ptr = head;

    while(ptr != NULL && flag == 0)
    {
        drawModel(&(ptr->model));

        if(ptr->next == head)
           flag = 1;

        ptr= ptr->next;
    }
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawAllModels() -> All model drawn in 1 iteration");

    if(selectedmodel!= NULL)
    {
        drawGridAroundSelectedModel(&(selectedmodel->model));
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawAllModels() -> Grid drawn around selected model");
    }

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawAllModels() completed ***********");
}



