#include "Logging.h"

// variables realated with file I/O
char gszLogFileName[] = "0_Log.txt";
FILE *gpFile = NULL;

// Initialize and Cleanup Logging
int init_logging(const char* filename)
{
    gpFile = fopen(filename, "w");
    if (gpFile == NULL)
    {
        fprintf(stderr, "Failed to open log file: %s\n", filename);
        return 0;
    }
    return 1;
}

void close_logging() {
    if (gpFile)
    {
        fclose(gpFile);
        gpFile = NULL;
    }
}

// Logging Function
void log_print(const char* level, const char* fmt, ...)
{
    if (gpFile == NULL)
        return;

    va_list args;
    va_start(args, fmt);

    // Timestamp
    time_t t = time(NULL);
    struct tm* lt = localtime(&t);
    char timebuf[20];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", lt);

    // Write formatted log
    fprintf(gpFile, "[%s] [%s] ", timebuf, level);
    vfprintf(gpFile, fmt, args);
    fprintf(gpFile, "\n");
    fflush(gpFile);  // Ensures it's written immediately

    va_end(args);
}


void LogOpenGLError(const char* msg)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        LOG_ERROR("[OpenGL ERROR] %s -> OpenGL Error: 0x%X", msg, err);
}

void LogWin32Error(const char* msg)
{
    DWORD err = GetLastError();
    if (err != 0)
        LOG_ERROR("[Win32 ERROR]%s -> Win32 Error: 0x%X", msg, err);
}

//Use below log statements fo rlogging
/*
eg.
LOG_ERROR("User %s (id=%d) failed to authenticate. Error code: %d", username, userId, errorCode);
LOG_WARN("User %s (id=%d) has limited access.", username, userId);
LOG_INFO("User %s successfully logged in.", username);
LOG_DEBUG("Debug info: userId=%d, username=%s, errorCode=%d", userId, username, errorCode);
*/





