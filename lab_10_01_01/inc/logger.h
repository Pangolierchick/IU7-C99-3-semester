#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>

#define DEBUG               0
#define INFO                0

#define GENERICK_POINTER(p)             (void *) p

#if DEBUG == 1
#pragma message "Debug mode is on"
#define DBG_PUTS(msg)           fprintf(stderr, "[DBG] [%19s] [%17s:%4d] %s\n" , __FILE__, __func__, __LINE__, msg)
#define DBG_PUT(msg)            fprintf(stderr, "[DBG] [%19s] [%17s:%4d] %s" , __FILE__, __func__, __LINE__, msg)
#define DBG_PRINT(format, ...)  fprintf(stderr, "[DBG] [%19s] [%17s:%4d] " format, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define DBG_PRINTF(format, ...) fprintf(stderr, format, __VA_ARGS__);
#else
#define DBG_PUTS(msg)
#define DBG_PRINT(format, ...)
#define DBG_PUT(msg)
#define DBG_PRINTF(format, ...)
#endif

#if INFO == 1
#define INFO_PUTS(msg)           fprintf(stderr, "[INFO] [%19s] [%17s:%4d] %s\n" , __FILE__, __func__, __LINE__, msg)
#define INFO_PUT(msg)            fprintf(stderr, "[INFO] [%19s] [%17s:%4d] %s" , __FILE__, __func__, __LINE__, msg)
#define INFO_PRINT(format, ...)  fprintf(stderr, "[INFO] [%19s] [%17s:%4d] " format, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define INFO_PRINTF(format, ...) fprintf(stderr, format, __VA_ARGS__);
#else
#define INFO_PUTS(msg)
#define INFO_PRINT(format, ...)
#define INFO_PUT(msg)
#define INFO_PRINTF(format, ...)
#endif

#endif // __LOGGER_H__
