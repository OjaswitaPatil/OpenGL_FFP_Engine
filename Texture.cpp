#include "Texture.h"

char **allTextureNames_Array = NULL;
GLuint *allLoadedTextureIdentifiers_Array = NULL;
GLint numberOfTextureAvailablesinallTexturesArray = 0;

int addTextureNameToallTexturesArray(char *newFileName)
{
    LOG_DEBUG("*************addTextureNameToallTexturesArray() started ***********");

    if(numberOfTextureAvailablesinallTexturesArray > MAX_NUMBER_OF_LOADED_TEXTURES)
    {
        LOG_ERROR("MAX_NUMBER_OF_LOADED_TEXTURES (%d) exceeded. Cannot add more textures unless MAX_NUMBER_OF_LOADED_TEXTURES macro modified",MAX_NUMBER_OF_LOADED_TEXTURES);
        return -1;
    }

    //allocate memory for new fileName
    int fileNameLength = strlen(newFileName);
    char *fileNameTemp = (char*)malloc(sizeof(char) * fileNameLength);
    strcpy(fileNameTemp, newFileName);
    //LOG_DEBUG("texture fileNameTemp =  %s\n", fileNameTemp);

    //Allocate memory for new allTextureNames_Array of existing size+1 and fill existing textureNames in it and then fill new textureName
    numberOfTextureAvailablesinallTexturesArray += 1;
    char **allTextureNames_ArrayTemp = (char**)malloc(sizeof(char*) * numberOfTextureAvailablesinallTexturesArray);
    for(int i= 0; i < numberOfTextureAvailablesinallTexturesArray - 1 ; i++)
    {
        int len = strlen(allTextureNames_Array[i]);
        allTextureNames_ArrayTemp[i] = (char*)malloc(sizeof(char) * (len + 1));
        strcpy(allTextureNames_ArrayTemp[i], allTextureNames_Array[i]);
        free(allTextureNames_Array[i]);
    }

    //copy newFile name to allTextureNames_Array
    allTextureNames_ArrayTemp[numberOfTextureAvailablesinallTexturesArray-1] = fileNameTemp;
    free(allTextureNames_Array);
    allTextureNames_Array = NULL;
    allTextureNames_Array = allTextureNames_ArrayTemp;
    allTextureNames_ArrayTemp = NULL;
    for(int i= 0; i < numberOfTextureAvailablesinallTexturesArray; i++)
    {
        LOG_INFO("allTextureNamesArray[%d] = %s", i,allTextureNames_Array[i]);
    }

    //Allocate memory for new allLoadedTextureIdentifiers_Array of existing size+1 and fill existing textureIdentifiers in it and then fill new textureIdentifiers
    GLuint *allLoadedTextureIdentifiers_ArrayTemp = (GLuint*)malloc(sizeof(GLuint) * numberOfTextureAvailablesinallTexturesArray);
    for(int i= 0; i < numberOfTextureAvailablesinallTexturesArray - 1 ; i++)
    {
        allLoadedTextureIdentifiers_ArrayTemp[i]= allLoadedTextureIdentifiers_Array[i];
    }
    free(allLoadedTextureIdentifiers_Array);
    allLoadedTextureIdentifiers_Array = NULL;
    allLoadedTextureIdentifiers_Array = allLoadedTextureIdentifiers_ArrayTemp;
    allLoadedTextureIdentifiers_ArrayTemp = NULL;


    //Create textureIdentifier for new texture and add that textureIdentifier into allLoadedTextureIdentifiers_Array
    char filePath[MAX_FILE_PATH_LENGTH]="resources/bmp_textures/\0";
    strcat(filePath,allTextureNames_Array[numberOfTextureAvailablesinallTexturesArray-1]);

    if(loadGLTexture(&allLoadedTextureIdentifiers_Array[numberOfTextureAvailablesinallTexturesArray-1], filePath) == FALSE)
    {
        LOG_DEBUG("Loading textureFilePath:%s at index: %d failed",filePath, numberOfTextureAvailablesinallTexturesArray-1);
        return -1;
    }
    else
    {
        LOG_DEBUG("Loading textureFilePath:%s at index: %d Succeeded",filePath, numberOfTextureAvailablesinallTexturesArray-1);
    }

    for(int i= 0; i < numberOfTextureAvailablesinallTexturesArray; i++)
    {
        LOG_INFO("allLoadedTextureIdentifiers_Array[%d] = %d", i,allLoadedTextureIdentifiers_Array[i]);
    }

    LOG_DEBUG("*************addTextureNameToallTexturesArray() Completed ***********");
    return 0;
}

BOOL loadGLTexture(GLuint *texture, char* imageFilePath)
{
    // VARIABLE DECLARATIONS
    HBITMAP hBitmap = NULL;
    BITMAP bmp;
    BOOL bResult = FALSE;

    // code
    wchar_t* wideFilePath = CharToWideChar(imageFilePath);
    // load the bitmap as image
    hBitmap = (HBITMAP)LoadImageW(GetModuleHandle(NULL), wideFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    {
        bResult = TRUE;

        // get bitmap structure from the loaded bitmap image
        GetObject(hBitmap, sizeof(BITMAP), &bmp);

        // genereta opengl texture objcet
        glGenTextures(1, texture);

        //bind to the newly created empty object
        glBindTexture(GL_TEXTURE_2D, *texture);

        //unpack image in memory for faster loading
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
        glBindTexture(GL_TEXTURE_2D, 0);
        DeleteObject(hBitmap);
        hBitmap = NULL;
    }
    return bResult;

}



