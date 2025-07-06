#include "TextRendering.h"

GLuint  base;                                                                   // Base Display List For The Font Set

BOOL keys[256];                                                                 // Array Used For The Keyboard Routine
const char* fontName = "Aerial";                                                // Define the font name

char textString[128] = "";                                                      // Buffer to store user input

GLvoid BuildFont(GLvoid)                                                        // Build Our Bitmap Font
{
    LOG_DEBUG("*************BuildFont() started ***********");

    HFONT font;                                                                 // Windows Font ID
    HFONT oldfont;                                                              // Used For Good House Keeping

    base = glGenLists(96);                                                      // Storage For 96 Characters ( NEW )
    if (base == 0) {
        LOG_ERROR("BuildFont() -> Failed to generate display lists.");
        return;
    }
    LOG_DEBUG("BuildFont() -> Generated display lists starting at ID %u", base);

    font = CreateFontA(
            0,                                                                  // Height Of Font ( NEW )
            0,                                                                  // Width Of Font
            0,                                                                  // Angle Of Escapement
            0,                                                                  // Orientation Angle
            FW_BOLD,                                                            // Font Weight
            TRUE,                                                               // Italic
            TRUE,                                                               // Underline
            TRUE,                                                               // Strikeout
            ANSI_CHARSET,                                                       // Character Set Identifier
            OUT_TT_PRECIS,                                                      // Output Precision
            CLIP_DEFAULT_PRECIS,                                                // Clipping Precision
            ANTIALIASED_QUALITY,                                                // Output Quality
            FF_DONTCARE|DEFAULT_PITCH,                                          // Family And Pitch
            fontName                                                            // Font Name
        );

    if (!font) {
        LOG_ERROR("BuildFont() -> Failed to create font.");
        return;
    }
    LOG_DEBUG("BuildFont() -> Windows font created with name '%s'", fontName);

    oldfont = (HFONT)SelectObject(ghdc, font);                                  // Selects The Font We Want
    if (!wglUseFontOutlines(ghdc, 32, 96, base, 0.0f, 0.2f, WGL_FONT_POLYGONS, NULL))// Builds 96 Characters Starting At Character 32
    {
        LOG_ERROR("BuildFont() -> wglUseFontOutlines failed.");
    }
    else
    {
        LOG_INFO("BuildFont() -> Successfully built font outlines.");
    }

    SelectObject(ghdc, oldfont);                                                // Selects The Font We Want
    DeleteObject(font);                                                         // Delete The Font

    LOG_DEBUG("*************BuildFont() completed ***********");
}

GLvoid KillFont(GLvoid)                                                         // Delete The Font List
{
    LOG_DEBUG("*************KillFont() started ***********");

    LOG_INFO("KillFont() -> Deleting font display lists starting at ID %u", base);
    glDeleteLists(base, 96);                                                    // Delete All 96 Characters ( NEW )
    LOG_INFO("KillFont() -> Deleted font display lists.");

    LOG_DEBUG("*************KillFont() completed ***********");
}

GLvoid glPrint(const char *fmt, ...)                                            // Custom GL "Print" Routine
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************glPrint() started ***********");

    char text[256];                                                             // Holds Our String
    va_list ap;                                                                 // Pointer To List Of Arguments

    if (fmt == NULL) {
        LOG_WARN("glPrint()-> Format string is NULL. Skipping print.");
        return;
    }

    va_start(ap, fmt);                                                          // Parses The String For Variables
    vsprintf(text, fmt, ap);                                                    // And Converts Symbols To Actual Numbers
    va_end(ap);                                                                 // Results Are Stored In Text

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("glPrint()->  Printing text \"%s\"", text);

    glPushAttrib(GL_LIST_BIT);                                                  // Pushes The Display List Bits     ( NEW )
    glListBase(base - 32);                                                      // Sets The Base Character to 32    ( NEW )

    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);                          // Draws The Display List Text  ( NEW )
    glPopAttrib();                                                              // Pops The Display List Bits   ( NEW )

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************glPrint() completed ***********");
}

GLvoid showText(char* text)
{
    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************showText() started ***********");

     if (!text)
     {
        LOG_WARN("showText()-> NULL input text.");
        return;
    }

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("showText()-> Showing text on screen: \"%s\"", text);
    glPrint(text);                                                              // Print GL Text To The Screen

    LOG_DEBUG_DISPLAY_LOOP_ITERATIONS("*************showText() completed ***********");
}



