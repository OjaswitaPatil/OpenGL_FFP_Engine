#include "Texture.h"

//to avoid multiple linking keep this in  .cpp file
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


GLuint loadGLTexture(char* textureFileName)
{
    // VARIABLE DECLARATIONS
    GLuint texture[1] ={0};
    BOOL bResult = FALSE;

    size_t imageFilePathLength = strlen("resources/") + strlen(textureFileName) + 1;
    char *imageFilePath = (char*)malloc(imageFilePathLength * sizeof(char));
    strcpy(imageFilePath,"resources/");
    strcat(imageFilePath, textureFileName);

    if (strstr(imageFilePath, ".bmp") != NULL)
    {
        bResult = loadGLBMPTexture(texture, imageFilePath);
    }
    else if(strstr(imageFilePath, ".png") != NULL)
    {
        bResult = loadGLPNGTexture(texture, imageFilePath);
    }

    return texture[0];
}

BOOL loadGLBMPTexture(GLuint *texture, char* imageFilePath)
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

BOOL loadGLPNGTexture(GLuint *texture, char* imageFilePath)
{
	// variable declaraions
	int w = 0;
	int h = 0;
	int comp = 0;

	unsigned char *image = stbi_load(imageFilePath, &w, &h, &comp, STBI_rgb_alpha);
	BOOL bResult = FALSE;

	if(image)
	{
		bResult = TRUE;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		if (comp == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}
		else if(comp == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}


		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(image);
	}

	return(bResult);

}

