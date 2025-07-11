#include "UtilityFunctions.h"

wchar_t* CharToWideChar(const char* ansiStr)
{
    static wchar_t wideStr[MAX_FILE_PATH_LENGTH];  // Static buffer (MAX_FILE_PATH_LENGTH size)
    MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, wideStr, MAX_FILE_PATH_LENGTH);
    return wideStr;
}


