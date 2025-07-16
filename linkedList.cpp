#include "linkedList.h"


int NumOfActiveLLNodesInMemory = 0;

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
        LOG_ERROR("createLinkedList() -> Memory allocation failed for new LL");
        return cDLL;
    }
    else
    {
        LOG_DEBUG("createLinkedList() -> Memory allocation success for new LL");
    }

    cDLL->head = NULL;
    cDLL->last = NULL;

    return cDLL;
}

struct Node* createModel(struct CircularDoublyLinkedList *pCDLL, ModelType modelType, const char* readyModelFileName)
{
    LOG_DEBUG("*************createModel() started ***********");

    struct Node *ptr =(struct Node*)malloc(sizeof(struct Node));
    if(ptr == NULL)
    {
        LOG_ERROR("createModel() -> Memory allocation failed for Node");
        return NULL;
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
        createReadyModel(&ptr->model, readyModelFileName);
        break;

        default:
        LOG_DEBUG("createModel() -> invalid modeltype %s. linkedlist node not created",modelType);
        return NULL;
        break;
    }

    LOG_DEBUG("createModel() -> Model structure filled successfully for model type %s",getModelNameFromModelType(modelType));

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

    NumOfActiveLLNodesInMemory++;

    LOG_DEBUG("*************createModel() completed ***********");

    return ptr;
}

void drawAllModels(struct CircularDoublyLinkedList *pCDLL)
{
    void drawModel(Model *model);

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************drawAllModels() started ***********");

    if (pCDLL == NULL || pCDLL->head == NULL)
    {
        LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("drawAllModels() -> Linkedlist sent to draw is NULL or its head is NULL");
        return;
    }

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

void deleteAllChildLLModels(struct CircularDoublyLinkedList *pCDLL)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************deleteAllChildLLModels() started ***********");

    int flag = 0;
    struct Node *ptr = pCDLL->head;
    struct Node *temp = NULL;

    while(ptr != NULL && flag == 0)
    {
        temp = ptr->next;

        if(ptr->next == pCDLL->head)
           flag = 1;

        deleteModel(pCDLL, ptr);

        if(temp)
            ptr= temp;
    }
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("deleteAllChildLLModels() -> All models deleted");

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************deleteAllChildLLModels() completed ***********");
}

void deleteModel(struct CircularDoublyLinkedList *pCDLL, struct Node *ptr)
{
    LOG_DEBUG("*************deleteModel() started ***********");
    if(ptr == NULL)
    {
        LOG_DEBUG("deleteModel() -> Pointer to Node is NULL");
        return;
    }

    LOG_DEBUG("deleteModel() -> heap memory for model struct deletion started");
    //free heap memory assigned for struct memberss
    if(ptr->model.vertices)
    {
        free(ptr->model.vertices);
        ptr->model.vertices = NULL;
    }

    if(ptr->model.colors)
    {
        free(ptr->model.colors);
        ptr->model.colors = NULL;
    }
    
    if(ptr->model.texcoords)
    {
        free(ptr->model.texcoords);
       ptr->model.texcoords = NULL;
    }

    //  IMPORATANT Delete model crash BUGis there due to this lines
    // LOG_DEBUG("deleteModel() -> heap memory for model struct deletion started. after texcoords");
    // LOG_DEBUG("Pointer value before free: %p", (void*)ptr->model.textureVariables);
    // if(ptr->model.textureVariables != NULL)
    // {
    //     LOG_DEBUG("deleteModel() -> inside if : before free textureVariables");
    //     free(ptr->model.textureVariables);
    //     LOG_DEBUG("deleteModel() -> inside if : after free textureVariables");
    //     ptr->model.textureVariables = NULL;
    // }
    // LOG_DEBUG("deleteModel() -> heap memory for model struct deletion started. after textureVariables");


    if(ptr->model.normals)
    {
        free(ptr->model.normals);
        ptr->model.normals = NULL;
    }

    if(ptr->model.customModelAttributes)
    {
        free(ptr->model.customModelAttributes);
        ptr->model.customModelAttributes = NULL;
    }

    //  IMPORATANT Delete model crash BUG is there due to this lines - deleting readymodel 
    // LOG_DEBUG("deleteModel() -> heap memory ; just before text");
    // if(ptr->model.text)
    // {
    //     free(ptr->model.text);
    //     ptr->model.text = NULL;
    // }
    // LOG_DEBUG("deleteModel() -> heap memory ; just before readyModelLLPtr");

    
    if(ptr->model.readyModelLLPtr)
    {
        //need to add code here to free child LL
        deleteAllChildLLModels(ptr->model.readyModelLLPtr);
        {
            free(ptr->model.readyModelLLPtr);
            ptr->model.readyModelLLPtr = NULL;
        }
    }
    if(ptr->model.readyModelFileName)
    {
        free(ptr->model.readyModelFileName);
        ptr->model.readyModelFileName = NULL;
    }
    LOG_DEBUG("deleteModel() -> heap memory for model struct deleted suceessfully");

    //Link list code
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
        {
            if(selectedmodel->pre)
                selectedmodel = selectedmodel->pre;
            else
                LOG_DEBUG("deleteModel() -> INVALID selectedModel pointr");
        }
        else
            selectedmodel = NULL;
    }

    //free structre shape heap memory
    free(ptr);
    ptr = NULL;


    NumOfActiveLLNodesInMemory--;

    LOG_DEBUG("*************deleteModel() completed ***********");
}




