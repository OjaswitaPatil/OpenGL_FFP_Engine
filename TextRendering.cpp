#include "TextRendering.h"

GLuint  base;                           // Base Display List For The Font Set

BOOL keys[256];                      // Array Used For The Keyboard Routine
const char* fontName = "Aerial";                                              // Define the font name
                            
char textString[128] = ""; // Buffer to store user input

GLvoid BuildFont(GLvoid)                    // Build Our Bitmap Font
{
    HFONT font;                       // Windows Font ID
    HFONT oldfont;                    // Used For Good House Keeping
 
    base = glGenLists(96);                  // Storage For 96 Characters ( NEW )
    
    font = CreateFontA(
            0,                                                                  // Height Of Font ( NEW )
            0,                                                                  // Width Of Font
            0,                                                                  // Angle Of Escapement
            0,                                                                  // Orientation Angle
            FW_BOLD,                                                            // Font Weight
            TRUE,                                                              // Italic
            TRUE,                                                              // Underline
            TRUE,                                                              // Strikeout
            ANSI_CHARSET,                                                       // Character Set Identifier
            OUT_TT_PRECIS,                                                      // Output Precision
            CLIP_DEFAULT_PRECIS,                                                // Clipping Precision
            ANTIALIASED_QUALITY,                                                // Output Quality
            FF_DONTCARE|DEFAULT_PITCH,                                          // Family And Pitch
            fontName                                                            // Font Name
        ); 

    oldfont = (HFONT)SelectObject(ghdc, font);       // Selects The Font We Want
    wglUseFontOutlines(ghdc, 32, 96, base, 0.0f, 0.2f, WGL_FONT_POLYGONS, NULL); // Builds 96 Characters Starting At Character 32
    SelectObject(ghdc, oldfont);             // Selects The Font We Want
    DeleteObject(font);                 // Delete The Font
}    

GLvoid KillFont(GLvoid)                     // Delete The Font List
{
    glDeleteLists(base, 96);                // Delete All 96 Characters ( NEW )
}

GLvoid glPrint(const char *fmt, ...)                // Custom GL "Print" Routine
{
    char text[256];              // Holds Our String
    va_list ap;                 // Pointer To List Of Arguments
   
    if(fmt == NULL)                    // If There's No Text
        return;                     // Do Nothing

    va_start(ap, fmt);                  // Parses The String For Variables
    vsprintf(text, fmt, ap);                // And Converts Symbols To Actual Numbers
    va_end(ap);                     // Results Are Stored In Text

    glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
    glListBase(base - 32);                  // Sets The Base Character to 32    ( NEW )

    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
    glPopAttrib();                      // Pops The Display List Bits   ( NEW )
}

GLvoid showText(char* text)
{
    glPrint(text);  // Print GL Text To The Screen
}



