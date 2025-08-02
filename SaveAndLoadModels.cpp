#include "SaveAndLoadModels.h"
#include "UtilityFunctions.h"

// variables realated with file I/O
FILE *modelFile = NULL;

// Initialize and Cleanup Logging
int createFile(const char* filename, const char *fileMode)
{
    modelFile = fopen(filename, fileMode);
    if (modelFile == NULL)
    {
        LOG_ERROR("failed to open file %s", filename);
        return -1;
    }
    else
    {
        LOG_INFO("Model file open successfully %s", filename);
    }
    return 0;
}

void closeFile(FILE *modelFile)
{
    if (modelFile)
    {
        fclose(modelFile);
        modelFile = NULL;
        LOG_INFO("Model file save successfully !!");
    }
}

BOOL saveModel(const char *fileName)
{
    int result = createFile(fileName, "w");
    if(result != 0)
    {
        return FALSE;
    }

    // Writing header row
    fprintf(modelFile,
        "modeltype,numberOfFaces,numberOfVerticesPerFace,"                      \
        "translate,scale,rotationAngle,"                                        \
        "verticesSize,vertices,"                                                \
        "colorsSize,colors,"                                                    \
        "texcoordsSize,texcoords,textureVariables,"                             \
        "normalsSize,normals,"                                                  \
        "customModelAttributesCount,customModelAttributes,"                     \
        "text\n"                                                                \
    );

    int flag = 0;
    struct Node *saveAndLoadModelPtr = head;

    while(saveAndLoadModelPtr != NULL && flag == 0)
    {
        //Model indentfiers
        fprintf(
            modelFile,
            "%s,%d,%d,",
            getModelNameFromModelType(saveAndLoadModelPtr->model.modeltype),
            saveAndLoadModelPtr->model.numberOfFaces,
            saveAndLoadModelPtr->model.numberOfVerticesPerFace
        );

        // tranformations
        fprintf(
            modelFile,
            "%lf;%lf;%lf," \
            "%lf;%lf;%lf," \
            "%lf;%lf;%lf,",
            saveAndLoadModelPtr->model.translate.x,saveAndLoadModelPtr->model.translate.y,saveAndLoadModelPtr->model.translate.z,
            saveAndLoadModelPtr->model.scale.x,saveAndLoadModelPtr->model.scale.y,saveAndLoadModelPtr->model.scale.z,
            saveAndLoadModelPtr->model.rotationAngle.x,saveAndLoadModelPtr->model.rotationAngle.y,saveAndLoadModelPtr->model.rotationAngle.z
        );

        // vertices
        fprintf(modelFile, "%d,", saveAndLoadModelPtr->model.verticesSize);

        if(saveAndLoadModelPtr->model.vertices == NULL)
        {
            fprintf(modelFile,"NODATA,");
        }
        else
        {
            for(int i= 0; i < saveAndLoadModelPtr->model.verticesSize; i++)
            {
                fprintf(modelFile, "%lf", saveAndLoadModelPtr->model.vertices[i]);
                if(i == saveAndLoadModelPtr->model.verticesSize-1)
                {
                    fprintf(modelFile,",");
                }
                else
                {
                    fprintf(modelFile,";");
                }

            }
        }

        // colors
        fprintf(modelFile, "%d,", saveAndLoadModelPtr->model.colorsSize);

        if(saveAndLoadModelPtr->model.colors == NULL)
        {
            fprintf(modelFile,"NODATA,");
        }
        else
        {
            for(int i= 0; i < saveAndLoadModelPtr->model.colorsSize; i++)
            {
                fprintf(modelFile, "%lf", saveAndLoadModelPtr->model.colors[i]);
                if(i == saveAndLoadModelPtr->model.colorsSize-1)
                {
                    fprintf(modelFile,",");
                }
                else
                {
                    fprintf(modelFile,";");
                }

            }
        }

        // texcoords
        fprintf(modelFile, "%d,", saveAndLoadModelPtr->model.texcoordsSize);

        if(saveAndLoadModelPtr->model.texcoords == NULL)
        {
            fprintf(modelFile,"NODATA,");
        }
        else
        {
            for(int i= 0; i < saveAndLoadModelPtr->model.texcoordsSize; i++)
            {
                fprintf(modelFile, "%lf", saveAndLoadModelPtr->model.texcoords[i]);
                if(i == saveAndLoadModelPtr->model.texcoordsSize-1)
                {
                    fprintf(modelFile,",");
                }
                else
                {
                    fprintf(modelFile,";");
                }

            }
        }

        //textureVaribles
        if(saveAndLoadModelPtr->model.textureVariables == NULL)
        {
            fprintf(modelFile,"NODATA,");
        }
        else
        {
            for(int i= 0; i < saveAndLoadModelPtr->model.numberOfFaces; i++)
            {
                // BOOL textureFound = FALSE;
                int indexInallLoadedTextureIdentifiers_Array = 0;
                for(int j = 0; j < numberOfTextureAvailablesinallTexturesArray; j++)
                {
                    if(allLoadedTextureIdentifiers_Array[j] == saveAndLoadModelPtr->model.textureVariables[i])
                    {
                        indexInallLoadedTextureIdentifiers_Array = j;
                        // fprintf(modelFile, "%s", allTextureNames_Array[j]);
                        // textureFound = TRUE;
                        break;
                    }
                }
                if(saveAndLoadModelPtr->model.textureVariables[i] > 0)
                    fprintf(modelFile, "%s", allTextureNames_Array[indexInallLoadedTextureIdentifiers_Array]);
                else
                    fprintf(modelFile, "NOFILE");

                if(i == saveAndLoadModelPtr->model.numberOfFaces-1)
                {
                    fprintf(modelFile,",");
                }
                else
                {
                    fprintf(modelFile,";");
                }

            }
        }

        //normals
        fprintf(modelFile, "%d,", saveAndLoadModelPtr->model.normalsSize);

        if(saveAndLoadModelPtr->model.normals == NULL)
        {
            fprintf(modelFile,"NODATA,");
        }
        else
        {
            for(int i= 0; i < saveAndLoadModelPtr->model.normalsSize; i++)
            {
                fprintf(modelFile, "%lf", saveAndLoadModelPtr->model.normals[i]);
                if(i == saveAndLoadModelPtr->model.normalsSize-1)
                {
                    fprintf(modelFile,",");
                }
                else
                {
                    fprintf(modelFile,";");
                }

            }
        }

        //customattrubutes
        fprintf(modelFile, "%d,", saveAndLoadModelPtr->model.customModelAttributesCount);

        if(saveAndLoadModelPtr->model.customModelAttributes == NULL)
        {
            fprintf(modelFile,"NODATA,");
        }
        else
        {
            for(int i= 0; i < saveAndLoadModelPtr->model.customModelAttributesCount; i++)
            {
                fprintf(modelFile, "%lf", saveAndLoadModelPtr->model.customModelAttributes[i]);
                if(i == saveAndLoadModelPtr->model.customModelAttributesCount-1)
                {
                    fprintf(modelFile,",");
                }
                else
                {
                    fprintf(modelFile,";");
                }

            }
        }

        //text
        if(saveAndLoadModelPtr->model.text == NULL)
        {
            fprintf(modelFile,"NODATA,");
        }
        else
        {
            fprintf(modelFile, "%s,", saveAndLoadModelPtr->model.text);
        }

        fprintf(modelFile, "\n");


        if(saveAndLoadModelPtr->next == head)
           flag = 1;

        saveAndLoadModelPtr = saveAndLoadModelPtr->next;
    }

    closeFile(modelFile);

    return TRUE;
}

BOOL printModelFunction(char *fileName)
{
    int result = createFile("Exported_DrawFunction.txt", "w");
    if(result != 0)
    {
        return FALSE;
    }

    FILE *variableFile = fopen("Exported_ModelGlobalVariables.txt", "w");
    if(variableFile == NULL)
    {
        return FALSE;
    }

    FILE *initializeAndUninitializeFunctionFile = fopen("Exported_InitializeAndUninitializeFunctions.txt", "w");
    if(initializeAndUninitializeFunctionFile == NULL)
    {
        return FALSE;
    }


    int flag = 0;
    struct Node *saveAndLoadModelPtr = head;

    //Draw function start
    fprintf(
            modelFile,
            "void drawReadyModel()\n" \
            "{\n" \
            "\t glPushMatrix();\n" \
            "\t {\n"  \
        );

    //initialize function start
    fprintf(
            initializeAndUninitializeFunctionFile,
            "void initializeReadyModel()\n" \
            "{\n"
        );

    int primitiveIndexCountInModel = 0;
    while(saveAndLoadModelPtr != NULL && flag == 0)
    {
        //**********Intialize function START***********
        fprintf(
            initializeAndUninitializeFunctionFile,
            "\t //------ReadyModel[%d]------\n" \
            "\t ReadyModel[%d].noOfVerticesPerFace = %d;\n" \
            "\t ReadyModel[%d].numberOfFaces = %d;\n\n",
            primitiveIndexCountInModel,
            primitiveIndexCountInModel,saveAndLoadModelPtr->model.numberOfVerticesPerFace,
            primitiveIndexCountInModel,saveAndLoadModelPtr->model.numberOfFaces
        );
        // malloc functions
        if(saveAndLoadModelPtr->model.customModelAttributesCount > 0)
        {
            fprintf(
                initializeAndUninitializeFunctionFile,
                "\t ReadyModel[%d].colors = (GLfloat*)malloc(%d * sizeof(GLfloat));\n" \
                "\t ReadyModel[%d].textureVariables = (GLuint*)malloc(%d * sizeof(GLuint));\n" \
                "\t ReadyModel[%d].customModelAttributes = (GLfloat*)malloc(%d * sizeof(GLfloat));\n\n",
                primitiveIndexCountInModel,saveAndLoadModelPtr->model.colorsSize,
                primitiveIndexCountInModel,saveAndLoadModelPtr->model.numberOfFaces,
                primitiveIndexCountInModel,saveAndLoadModelPtr->model.customModelAttributesCount
            );
        }
        else
        {
            fprintf(
                initializeAndUninitializeFunctionFile,
                "\t ReadyModel[%d].colors = (GLfloat*)malloc(%d * sizeof(GLfloat));\n" \
                "\t ReadyModel[%d].textureVariables = (GLuint*)malloc(%d * sizeof(GLuint));\n" \
                "\t ReadyModel[%d].customModelAttributes = NULL;\n\n",
                primitiveIndexCountInModel,saveAndLoadModelPtr->model.colorsSize,
                primitiveIndexCountInModel,saveAndLoadModelPtr->model.numberOfFaces,
                primitiveIndexCountInModel
            );
        }

        //Asssigning values to variables
        //Color
        fprintf(
            initializeAndUninitializeFunctionFile,
            "\t {\n" \
            "\t\t GLfloat colors[%d] = { ",
            saveAndLoadModelPtr->model.colorsSize
        );

        for(int i = 0; i < saveAndLoadModelPtr->model.colorsSize; i++)
        {
            fprintf(
                initializeAndUninitializeFunctionFile,
                "%lff",
                saveAndLoadModelPtr->model.colors[i]
                );

            if(i < saveAndLoadModelPtr->model.colorsSize - 1)
            {
                fprintf(
                    initializeAndUninitializeFunctionFile,
                    ", "
                    );
            }
        }
        fprintf(
            initializeAndUninitializeFunctionFile,
            " };      // colors\n"
        );

        //textureVariables
        fprintf(
            initializeAndUninitializeFunctionFile,
            "\t\t GLuint textureVariables[%d] = { ",
            saveAndLoadModelPtr->model.numberOfFaces
        );
        for(int i = 0; i < saveAndLoadModelPtr->model.numberOfFaces; i++)
        {
            fprintf(
                initializeAndUninitializeFunctionFile,
                "%d",
                saveAndLoadModelPtr->model.textureVariables[i]
                );

            if(i < saveAndLoadModelPtr->model.numberOfFaces - 1)
            {
                fprintf(
                    initializeAndUninitializeFunctionFile,
                    ", "
                    );
            }
        }
        if(saveAndLoadModelPtr->model.customModelAttributesCount > 0)
        {
            fprintf(
                initializeAndUninitializeFunctionFile,
                " };      // textureVariables\n"
            );
        }
        else
        {
            fprintf(
                initializeAndUninitializeFunctionFile,
                " };      // textureVariables\n"
            );
        }

        //customModelAttributes
        if(saveAndLoadModelPtr->model.customModelAttributesCount > 0)
        {
           fprintf(
                initializeAndUninitializeFunctionFile,
                "\t\t GLfloat customModelAttributes[%d] = { ",
                saveAndLoadModelPtr->model.customModelAttributesCount
            );
            for(int i = 0; i < saveAndLoadModelPtr->model.customModelAttributesCount; i++)
            {
                fprintf(
                    initializeAndUninitializeFunctionFile,
                    "%lff",
                    saveAndLoadModelPtr->model.customModelAttributes[i]
                    );

                if(i < saveAndLoadModelPtr->model.customModelAttributesCount - 1)
                {
                    fprintf(
                        initializeAndUninitializeFunctionFile,
                        ", "
                        );
                }
            }
            fprintf(
                initializeAndUninitializeFunctionFile,
                " };      // customModelAttributes\n"
            );
        }

        fprintf(
            initializeAndUninitializeFunctionFile,
            "\n"
        );

        //Fill the values in Structure now
        //color
        fprintf(
            initializeAndUninitializeFunctionFile,
            "\t\t for(int i = 0; i < sizeof(colors)/sizeof(colors[0]); i++)\n" \
            "\t\t {\n" \
            "\t\t\t ReadyModel[%d].colors[i] = colors[i];\n" \
            "\t\t }\n" ,
            primitiveIndexCountInModel
        );
        //textureVariables
        fprintf(
            initializeAndUninitializeFunctionFile,
            "\t\t for(int i = 0; i < sizeof(textureVariables)/sizeof(textureVariables[0]); i++)\n" \
            "\t\t {\n" \
            "\t\t\t ReadyModel[%d].textureVariables[i] = textureVariables[i];\n" \
            "\t\t }\n" ,
            primitiveIndexCountInModel
        );
        if(saveAndLoadModelPtr->model.customModelAttributesCount > 0)
        {
            //customModelAttributes
            fprintf(
                initializeAndUninitializeFunctionFile,
                "\t\t for(int i = 0; i < sizeof(customModelAttributes)/sizeof(customModelAttributes[0]); i++)\n" \
                "\t\t {\n" \
                "\t\t\t ReadyModel[%d].customModelAttributes[i] = customModelAttributes[i];\n" \
                "\t\t }\n" ,
                primitiveIndexCountInModel
            );
        }

        fprintf(
                initializeAndUninitializeFunctionFile,
                "\t }\n\n"
            );

        //reassigning correct texture variables as per current state
        for(int i = 0; i < saveAndLoadModelPtr->model.numberOfFaces; i++)
        {
            if(saveAndLoadModelPtr->model.textureVariables[i] > 0)
            {
                fprintf(
                    initializeAndUninitializeFunctionFile,
                    "\tReadyModel[%d].textureVariables[%d] = loadGLTexture(\"%s\"); \n" ,
                    primitiveIndexCountInModel,
                    i,
                    allTextureNames_Array[(saveAndLoadModelPtr->model.textureVariables[i])-1]
                );
            }
        }
        fprintf(
            initializeAndUninitializeFunctionFile,
            "\n\t//========================\n\n"
        );


        //**********Intialize function END***********

        //**********DRAW function START***********

        fprintf(
            modelFile,
            "\t\tglPushMatrix();\n" \
            "\t\t{\n"  \
            "\t\t\tglTranslatef(%lff, %lff, %lff);\n"  \
            "\t\t\tglRotatef(%lff, 1.0f, 0.0f, 0.0f);\n"  \
            "\t\t\tglRotatef(%lff, 0.0f, 1.0f, 0.0f);\n"  \
            "\t\t\tglRotatef(%lff, 0.0f, 0.0f, 1.0f);\n"  \
            "\t\t\tglScalef(%lff, %lff, %lff);\n",
            saveAndLoadModelPtr->model.translate.x, saveAndLoadModelPtr->model.translate.y, saveAndLoadModelPtr->model.translate.z,
            saveAndLoadModelPtr->model.rotationAngle.x,
            saveAndLoadModelPtr->model.rotationAngle.y,
            saveAndLoadModelPtr->model.rotationAngle.z,
            saveAndLoadModelPtr->model.scale.x, saveAndLoadModelPtr->model.scale.y, saveAndLoadModelPtr->model.scale.z
        );

        //Model indentfiers - Draw Primimitive function
        fprintf(
            modelFile,
            "\t\t\tdraw%sModel(&ReadyModel[%d]);\n",
            getModelNameFromModelType(saveAndLoadModelPtr->model.modeltype),
            primitiveIndexCountInModel
        );


        fprintf(
            modelFile,
            "\t\t}\n" \
            "\t\tglPopMatrix();\n",
            getModelNameFromModelType(saveAndLoadModelPtr->model.modeltype)
        );

        //**********DRAW function END***********


        if(saveAndLoadModelPtr->next == head)
           flag = 1;

        saveAndLoadModelPtr = saveAndLoadModelPtr->next;

        primitiveIndexCountInModel++;
    }

    //***********GLOBAL VAR SECTION START *************
    fprintf(
        variableFile,
        "struct Model\n" \
        "{\n" \
        "\t int numberOfFaces;\n" \
        "\t int noOfVerticesPerFace;\n" \
        "\t GLfloat *colors;\n"  \
        "\t GLuint *textureVariables;\n"  \
        "\t GLfloat *customModelAttributes;\n"  \
        "};\n",
        primitiveIndexCountInModel
    );
    fprintf(
        variableFile,
        "struct Model ReadyModel[%d];\n" ,
        primitiveIndexCountInModel
    );
    //***********GLOBAL VAR SECTION END *************


    //function closure
    //initialize function closure
    fprintf(
            initializeAndUninitializeFunctionFile,
            "}\n"
        );
    //draw function closure
    fprintf(
        modelFile,
        "\t}\n" \
        "\tglPopMatrix();\n" \
        "}\n",
        getModelNameFromModelType(saveAndLoadModelPtr->model.modeltype)
    );


    // ************** Uninitialize function START **************
    //UNinitialize function start
    fprintf(
            initializeAndUninitializeFunctionFile,
            "\n-------------------------------\n\n" \
            "void uninitializeReadyModel()\n" \
            "{\n" \
            "\t for(int i = 0; i < %d; i++)\n" \
            "\t {\n" \

            "\t\t if(ReadyModel[i].colors != NULL)\n" \
            "\t\t {\n" \
            "\t\t\t free(ReadyModel[i].colors);\n" \
            "\t\t\t ReadyModel[i].colors = NULL;\n" \
            "\t\t }\n" \

            "\t\t if(ReadyModel[i].textureVariables != NULL)\n" \
            "\t\t {\n" \
            "\t\t\t free(ReadyModel[i].textureVariables);\n" \
            "\t\t\t ReadyModel[i].textureVariables = NULL;\n" \
            "\t\t }\n" \

            "\t\t if(ReadyModel[i].customModelAttributes != NULL)\n" \
            "\t\t {\n" \
            "\t\t\t free(ReadyModel[i].customModelAttributes);\n" \
            "\t\t\t ReadyModel[i].customModelAttributes = NULL;\n" \
            "\t\t }\n" \

            "\t }\n" \
            "}\n",
            primitiveIndexCountInModel
        );

    // ************** Uninitialize function END **************


    fclose(initializeAndUninitializeFunctionFile);
    fclose(variableFile);
    closeFile(modelFile);

    return TRUE;
}


int splitStringBaseOnToken(const char* source, void* destination, int type)
{
    if(source == NULL)
    {
        LOG_ERROR("splitStringBaseOnToken() -> source string is NULL");
        return 0;
    }

    if(destination == NULL)
    {
        LOG_ERROR("splitStringBaseOnToken() -> destination string is NULL");
        return 0;
    }

    char *buffer = (char*)malloc(sizeof(char) * strlen(source));
    LOG_DEBUG("splitStringBaseOnTokenloadCSVModel() -> buffer size and size of source is %d", strlen(source));
    strcpy(buffer, source);  // Make a local copy because strtok modifies the string

    char* token = strtok(buffer, ";");
    int count = 0;

    while (token != NULL)
    {
        LOG_DEBUG("splitStringBaseOnTokenloadCSVModel() -> loop iteration");

        if (type == TYPE_INT)
        {
            ((int*)destination)[count] = atoi(token);
        }
        else if (type == TYPE_FLOAT)
        {
            ((float*)destination)[count] = atof(token);
        }
        else if (type == TYPE_STRING)
        {
                ((char**)destination)[count] = strdup(token);  // copy token to new string
                LOG_DEBUG("splitStringBaseOnTokenloadCSVModel() -> strlen(token) > 0  -> TRUE");
        }

        count++;
        token = strtok(NULL, ";");
    }

    free(buffer);

    return count;
}

BOOL loadCSVModel(const char *filename)
{
    LOG_DEBUG("*************loadCSVModel() started ***********");

    FILE *modelFile = fopen(filename, "r");
    if (modelFile == NULL)
    {
        LOG_ERROR("loadCSVModel() -> Error opening file for reading!");
        return FALSE;
    }
    else
    {
        LOG_INFO("loadCSVModel() ->file open for loading succesfully %s", filename);
    }

    char line[10000];                   //maximum character allowed per line
    int lineCount = 0;


    while (fgets(line, sizeof(line), modelFile))
    {
        line[strcspn(line, "\n")] = 0;  // remove \n from line

        if (lineCount == 0)
        {
            lineCount++;
            continue;  // skip header
        }

        char *csvRow[MAX_CSV_COLUMNS];
        int tokenIndex = 0;

        char *temp = strtok(line, ",");
        while (temp && tokenIndex < MAX_CSV_COLUMNS)
        {
            csvRow[tokenIndex++] = temp;
            temp = strtok(NULL, ",");
        }


        int columnIndex = 0;
        //ModelType
        createModel(getModelTypeFromModelName(csvRow[columnIndex++]));

        //numberOfFaces
        selectedmodel->model.numberOfFaces = atoi(csvRow[columnIndex++]);
        LOG_DEBUG("loadCSVModel()->  selectedmodel->model.numberOfFaces = %d",  selectedmodel->model.numberOfFaces);

        //numberOfVerticesPerFace
        selectedmodel->model.numberOfVerticesPerFace = atoi(csvRow[columnIndex++]);
        LOG_DEBUG("loadCSVModel()->  selectedmodel->model.numberOfVerticesPerFace = %d",  selectedmodel->model.numberOfVerticesPerFace);

        //translate
        float translateArray[3];
        splitStringBaseOnToken(csvRow[columnIndex++], translateArray, TYPE_FLOAT);
        selectedmodel->model.translate.x = translateArray[0];
        selectedmodel->model.translate.y = translateArray[1];
        selectedmodel->model.translate.z = translateArray[2];

        LOG_DEBUG(
            "loadCSVModel()->  \n"                                              \
            "selectedmodel->model.translate.x = %lf\n"                           \
            "selectedmodel->model.translate.y = %lf\n"                          \
            "selectedmodel->model.translate.z = %lf\n",
            selectedmodel->model.translate.x,
            selectedmodel->model.translate.y,
            selectedmodel->model.translate.z
        );

        //scale
        float scaleArray[3];
        splitStringBaseOnToken(csvRow[columnIndex++], scaleArray, TYPE_FLOAT);
        selectedmodel->model.scale.x = scaleArray[0];
        selectedmodel->model.scale.y = scaleArray[1];
        selectedmodel->model.scale.z = scaleArray[2];

        LOG_DEBUG(
            "loadCSVModel()->  \n"                                              \
            "selectedmodel->model.scale.x = %lf\n"                              \
            "selectedmodel->model.scale.y = %lf\n"                              \
            "selectedmodel->model.scale.z = %lf\n",
            selectedmodel->model.scale.x,
            selectedmodel->model.scale.y,
            selectedmodel->model.scale.z
        );

        //rotation
        float rotationArray[3];
        splitStringBaseOnToken(csvRow[columnIndex++], rotationArray, TYPE_FLOAT);
        selectedmodel->model.rotationAngle.x = rotationArray[0];
        selectedmodel->model.rotationAngle.y = rotationArray[1];
        selectedmodel->model.rotationAngle.z = rotationArray[2];

        LOG_DEBUG(
            "loadCSVModel()->  \n"                                              \
            "selectedmodel->model.rotationAngle.x = %lf\n"                      \
            "selectedmodel->model.rotationAngle.y = %lf\n"                      \
            "selectedmodel->model.rotationAngle.z = %lf\n",
            selectedmodel->model.rotationAngle.x,
            selectedmodel->model.rotationAngle.y,
            selectedmodel->model.rotationAngle.z
        );

        //verticesSize
        selectedmodel->model.verticesSize = atoi(csvRow[columnIndex++]);
        LOG_DEBUG("loadCSVModel()->  selectedmodel->model.verticesSize = %d",  selectedmodel->model.verticesSize);

        //vertices
        if(selectedmodel->model.verticesSize > 0)
        {
            splitStringBaseOnToken(csvRow[columnIndex], selectedmodel->model.vertices, TYPE_FLOAT);

            LOG_DEBUG("loadCSVModel()->");
            for(int i = 0; i<selectedmodel->model.verticesSize; i++)
            {
                LOG_DEBUG("\t\t\t selectedmodel->model.vertices[%d] = %lf", i, selectedmodel->model.vertices[i]);
            }
        }
        else
        {
            LOG_DEBUG("\t\t\t selectedmodel->model.vertices is NULL");
        }
        columnIndex++;

        //colorsSize
        selectedmodel->model.colorsSize = atoi(csvRow[columnIndex++]);
        LOG_DEBUG("loadCSVModel()->  selectedmodel->model.colorsSize = %d",  selectedmodel->model.colorsSize);

        //colors
        if(selectedmodel->model.colorsSize > 0)
        {
            splitStringBaseOnToken(csvRow[columnIndex], selectedmodel->model.colors, TYPE_FLOAT);

            LOG_DEBUG("loadCSVModel()->");
            for(int i = 0; i<selectedmodel->model.colorsSize; i++)
            {
                LOG_DEBUG("\t\t\t selectedmodel->model.colors[%d] = %lf", i, selectedmodel->model.colors[i]);
            }
        }
        else
        {
            LOG_DEBUG("\t\t\t selectedmodel->model.colors is NULL");
        }
        columnIndex++;

        //texCoordsize
        selectedmodel->model.texcoordsSize = atoi(csvRow[columnIndex++]);
        LOG_DEBUG("loadCSVModel()->  selectedmodel->model.texCoordsize = %d",  selectedmodel->model.texcoordsSize);

        //texcord
        if(selectedmodel->model.texcoordsSize > 0)
        {
            splitStringBaseOnToken(csvRow[columnIndex], selectedmodel->model.texcoords, TYPE_FLOAT);

            LOG_DEBUG("loadCSVModel()->");
            for(int i = 0; i<selectedmodel->model.texcoordsSize; i++)
            {
                LOG_DEBUG("\t\t\t selectedmodel->model.texcord[%d] = %lf", i, selectedmodel->model.texcoords[i]);
            }
        }
        else
        {
            LOG_DEBUG("\t\t\t selectedmodel->model.texcord is NULL");
        }
        columnIndex++;

        //textureVariables
        char** textureVariablesStringTemp = (char**)malloc(sizeof(char*) * (selectedmodel->model.numberOfFaces) );
        if(selectedmodel->model.numberOfFaces > 0)
        {
            splitStringBaseOnToken(csvRow[columnIndex], textureVariablesStringTemp, TYPE_STRING);

            for(int i = 0; i<selectedmodel->model.numberOfFaces; i++)
            {
                bool isTexturefound = false;
                if(strcmp(textureVariablesStringTemp[i], "NOFILE") != 0)
                {
                    for(int j = 0; j<numberOfTextureAvailablesinallTexturesArray; j++)
                    {
                        if(strcmp(allTextureNames_Array[j],textureVariablesStringTemp[i]) == 0)
                        {
                            selectedmodel->model.textureVariables[i] = allLoadedTextureIdentifiers_Array[j];
                            isTexturefound = true;
                            LOG_DEBUG("loadCSVModel()-> textureVariables : found texture %s in allTextureNames_Array: %s ",textureVariablesStringTemp[i],  allTextureNames_Array[j]);
                            break;
                        }
                    }
                }
                if(isTexturefound == false)
                {
                    selectedmodel->model.textureVariables[i]= 0;
                    LOG_DEBUG("loadCSVModel()-> textureVariables : not found texture %s in allTextureNames_Array:  ",textureVariablesStringTemp[i]);
                }
            }
            LOG_DEBUG("loadCSVModel()->");
            for(int i = 0; i<selectedmodel->model.numberOfFaces; i++)
            {
                LOG_DEBUG("\t\t\t selectedmodel->model.textureVariables[%d] = %d : %s", i, selectedmodel->model.textureVariables[i], textureVariablesStringTemp[i]);
            }
        }
        else
        {
            LOG_DEBUG("\t\t\t selectedmodel->model.textureVariables is NULL");
        }
        columnIndex++;


        //normalSize
        selectedmodel->model.normalsSize = atoi(csvRow[columnIndex++]);
        LOG_DEBUG("loadCSVModel()->  selectedmodel->model.normalSize = %d",  selectedmodel->model.normalsSize);

        //normals
        if(selectedmodel->model.normalsSize > 0)
        {
            splitStringBaseOnToken(csvRow[columnIndex], selectedmodel->model.normals, TYPE_FLOAT);

            LOG_DEBUG("loadCSVModel()->");
            for(int i = 0; i<selectedmodel->model.normalsSize; i++)
            {
                LOG_DEBUG("\t\t\t selectedmodel->model.normals[%d] = %lf", i, selectedmodel->model.normals[i]);
            }
        }
        else
        {
            LOG_DEBUG("\t\t\t selectedmodel->model.normals is NULL");
        }
        columnIndex++;

        //customAttributesCount
        selectedmodel->model.customModelAttributesCount = atoi(csvRow[columnIndex++]);
        LOG_DEBUG("loadCSVModel()->  selectedmodel->model.customAttributesCount = %d",  selectedmodel->model.customModelAttributesCount);

        LOG_DEBUG("loadCSVModel()->  columnIndex = %d customAttributes",  columnIndex);
        //customAttributes
        if(selectedmodel->model.customModelAttributesCount > 0)
        {
            splitStringBaseOnToken(csvRow[columnIndex], selectedmodel->model.customModelAttributes, TYPE_FLOAT);

            LOG_DEBUG("loadCSVModel()->");
            for(int i = 0; i<selectedmodel->model.customModelAttributesCount; i++)
            {
                LOG_DEBUG("\t\t\t selectedmodel->model.customAttributes[%d] = %lf", i, selectedmodel->model.customModelAttributes[i]);
            }
        }
        else
        {
            LOG_DEBUG("\t\t\t selectedmodel->model.customAttributes is NULL");
        }
        columnIndex++;

        //text
        LOG_DEBUG("loadCSVModel()->  selectedmodel->model.text at index %d= %s",  columnIndex, csvRow[columnIndex]);
        selectedmodel->model.text = (char*)malloc(sizeof(char) * (strlen(csvRow[columnIndex])+1) );
        strcpy(selectedmodel->model.text, csvRow[columnIndex++]);

        if(selectedmodel->model.text)
            LOG_DEBUG("loadCSVModel()->  selectedmodel->model.text = %s",  selectedmodel->model.text);
        else
            LOG_DEBUG("loadCSVModel()->  selectedmodel->model.text is NULL");
        columnIndex++;
    }

    closeFile(modelFile);

    LOG_DEBUG("*************loadCSVModel() Completed ***********");

    return TRUE;
}



