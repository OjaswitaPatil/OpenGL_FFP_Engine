#ifndef LOGGING_H
#define LOGGING_H

#include<stdio.h>
#include<stdlib.h>
#include<string> // for memset
#include <time.h>
#include <stdarg.h>



// === Log Level Defines ===
#define LOG_LEVEL_ERROR   1
#define LOG_LEVEL_WARN    2
#define LOG_LEVEL_INFO    3
#define LOG_LEVEL_DEBUG   4
#define LOG_LEVEL_DEBUG_DISPLAY_LOOP_ITERATIONS   5

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO // default fallback
#endif

int init_logging(const char* filename);
void close_logging();
void log_print(const char* level, const char* fmt, ...);

// === Log Macros ===
#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(fmt, ...)  log_print("ERROR", fmt, __VA_ARGS__)
#else
#define LOG_ERROR(fmt, ...)  ((void)0)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
#define LOG_WARN(fmt, ...)   log_print("WARN", fmt, __VA_ARGS__)
#else
#define LOG_WARN(fmt, ...)   ((void)0)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(fmt, ...)   log_print("INFO", fmt, __VA_ARGS__)
#else
#define LOG_INFO(fmt, ...)   ((void)0)
#endif


#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOG_DEBUG(fmt, ...)  log_print("DEBUG", fmt, __VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)  ((void)0)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG_DISPLAY_LOOP_ITERATIONS
#define LOG_DEBUG_DISPLAY_LOOP_ITERATIONS(fmt, ...)  log_print("DEBUG DISPLAY", fmt, __VA_ARGS__)
#else
#define LOG_DEBUG_DISPLAY_LOOP_ITERATIONS(fmt, ...)  ((void)0)
#endif

// variables realated with file I/O
extern char gszLogFileName[];
extern FILE *gpFile;

#endif // LOGGING_H

