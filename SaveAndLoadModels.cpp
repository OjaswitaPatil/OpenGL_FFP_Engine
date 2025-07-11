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

BOOL saveModel()
{
    int result = createFile("model.csv", "w");
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
    struct Node *ptr = head;

    while(ptr != NULL && flag == 0)
    {
        saveAndLoadModelPtr = ptr;

        //Model indentfiers
        fprintf(
            modelFile, 
            "%s,%d,%d,", 
            getModelNameFromModelType(saveAndLoadModelPtr->model.modeltype),
            saveAndLoadModelPtr->model.numberOfFaces,
            saveAndLoadModelPtr->model.numberOfVerticesPerFace
        );
        
        // fprintf(
        //     modelFile, 
        //     "%d,%d,%d,", 
        //     (int)saveAndLoadModelPtr->model.modeltype,
        //     saveAndLoadModelPtr->model.numberOfFaces,
        //     saveAndLoadModelPtr->model.numberOfVerticesPerFace
        // );

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
            fprintf(modelFile,",");
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
            fprintf(modelFile,",");
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
            fprintf(modelFile,",");
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
            fprintf(modelFile,",");
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
                // if (!textureFound)
                // {
                //     fprintf(modelFile, "NONE");  // or leave blank ""
                // }
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
            fprintf(modelFile,",");
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
            fprintf(modelFile,",");
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
            fprintf(modelFile,",");
        }
        else
        {
            fprintf(modelFile, "%s", saveAndLoadModelPtr->model.text);
        }

        fprintf(modelFile, "\n");


        if(ptr->next == head)
           flag = 1;

        ptr= ptr->next;
    }


    closeFile(modelFile);

    return TRUE;
}



