#include "linkedList.h"

// struct Node *head = NULL;
// struct Node *last = NULL;
struct Node *selectedmodel;
// struct Node *saveAndLoadModelPtr = head;

struct CircularDoublyLinkedList *masterLinkedList = NULL;

struct CircularDoublyLinkedList* createLinkedList()
{
    struct CircularDoublyLinkedList *cDLL = (struct CircularDoublyLinkedList*)malloc(sizeof(struct CircularDoublyLinkedList));
    if(cDLL == NULL)
    {
        LOG_ERROR("createModel() -> Memory allocation failed for Node");
        return cDLL;
    }

    cDLL->head = NULL;
    cDLL->last = NULL;

    return cDLL;
}

void createModel(struct CircularDoublyLinkedList *pCDLL, ModelType modelType)
{
    LOG_DEBUG("*************createModel() started ***********");

    struct Node *ptr =(struct Node*)malloc(sizeof(struct Node));
    if(ptr == NULL)
    {
        LOG_ERROR("createModel() -> Memory allocation failed for Node");
        return;
    }

    initializeModelStructureToDefaultValues(&(ptr->model));

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

        case SPHERE:
        createSphere(&ptr->model);
        break;

        case CYLINDER:
        createCylinder(&ptr->model);
        break;

        case DISK:
        createDisk(&ptr->model);
        break;

        case READYMODEL:
        //neet to add recursive call to draw model
        break;

        default:
        LOG_DEBUG("createModel() -> invalid modeltype %s. linkedlist node not created",modelType);
        return;
        break;
    }

    ptr->next = NULL;
    ptr->pre = NULL;

    if(pCDLL->head == NULL)
    {
        LOG_DEBUG("createModel() -> First Node in LL created");
        ptr->next = ptr;
        ptr->pre = ptr;
        pCDLL->head = ptr;
        pCDLL->last = ptr;
    }
    else
    {
        LOG_DEBUG("createModel() -> second and + Node in LL created");
        pCDLL->last->next = ptr;
        ptr->pre = pCDLL->last;
        ptr->next = pCDLL->head;
        pCDLL->head->pre = ptr;
        pCDLL->last = ptr;
    }

    if(pCDLL == masterLinkedList)
    {
        selectedmodel = ptr;
    }

    LOG_DEBUG("*************createModel() completed ***********");
}

void deleteModel(struct CircularDoublyLinkedList *pCDLL, struct Node *ptr)
{
    LOG_DEBUG("*************deleteModel() started ***********");
    if(ptr == NULL)
    {
        LOG_WARN("deleteModel() -> Pointer to Node is NULL");
        return;
    }

    //free heap memory assigned for struct memberss
    if(ptr->model.vertices)
        free(ptr->model.vertices);
    if(ptr->model.colors)
        free(ptr->model.colors);
    if(ptr->model.texcoords)
        free(ptr->model.texcoords);
    if(ptr->model.textureVariables)
        free(ptr->model.textureVariables);
    if(ptr->model.normals)
        free(ptr->model.normals);
    if(ptr->model.customModelAttributes)
        free(ptr->model.customModelAttributes);
    if(ptr->model.text)
        free(ptr->model.text);
    if(ptr->model.readyModelFileName)
        free(ptr->model.readyModelFileName);
    if(ptr->model.readyModelLLHeadPtr)
    {
        //need to add code here to free child LL
        free(ptr->model.readyModelLLHeadPtr);
    }

    if(pCDLL->head == pCDLL->last)
    {
        pCDLL->head = NULL;
        pCDLL->last = NULL;
        LOG_DEBUG("deleteModel() -> No Node avaialble in LL for deletion");
    }
    else if(ptr == pCDLL->head)
    {
        ptr->next->pre = pCDLL->last;
        pCDLL->last->next = ptr->next;
        pCDLL->head = ptr->next;
        LOG_DEBUG("deleteModel() -> head Node deleted");
    }
    else if(ptr == pCDLL->last)
    {
        pCDLL->head->pre = pCDLL->last->pre;
        pCDLL->last->pre->next = pCDLL->head;
        pCDLL->last = pCDLL->last->pre;
        LOG_DEBUG("deleteModel() -> last Node deleted");
    }
    else
    {
        ptr->pre->next = ptr->next;
        ptr->next->pre = ptr->pre;
        LOG_DEBUG("deleteModel() -> Middle Node deleted");
    }

    if(pCDLL == masterLinkedList)
    {
        if(pCDLL->head != NULL)
            selectedmodel = selectedmodel->pre;
        else
            selectedmodel = NULL;
    }

    //free structre shape heap memory
    free(ptr);

    LOG_DEBUG("*************deleteModel() completed ***********");
}

void drawAllModels(struct CircularDoublyLinkedList *pCDLL)
{
    void drawModel(Model *model);

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawAllModels() started ***********");

    int flag = 0;
    struct Node *ptr = pCDLL->head;

    while(ptr != NULL && flag == 0)
    {
        drawModel(&(ptr->model));

        if(ptr->next == pCDLL->head)
           flag = 1;

        ptr= ptr->next;
    }
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawAllModels() -> All model drawn in 1 iteration");

    if(pCDLL == masterLinkedList)
    {
        if(selectedmodel!= NULL)
        {
            drawGridAroundSelectedModel(&(selectedmodel->model));
            LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawAllModels() -> Grid drawn around selected model");
        }
    }

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawAllModels() completed ***********");
}



