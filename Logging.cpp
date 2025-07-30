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

//Use below log statements fo rlogging
/*
eg.
LOG_ERROR("User %s (id=%d) failed to authenticate. Error code: %d", username, userId, errorCode);
LOG_WARN("User %s (id=%d) has limited access.", username, userId);
LOG_INFO("User %s successfully logged in.", username);
LOG_DEBUG("Debug info: userId=%d, username=%s, errorCode=%d", userId, username, errorCode);
*/





