#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>

#define DEBUG               0

#if DEBUG == 1
#pragma message "Debug mode is on"
#define DBG_PUTS(msg)          fprintf(stderr, "[DBG] [%17s] [%15s:%4d] %s\n" , __FILE__, __func__, __LINE__, msg)
#define DBG_PUT(msg)           fprintf(stderr, "[DBG] [%17s] [%15s:%4d] %s" , __FILE__, __func__, __LINE__, msg)
#define DBG_PRINT(format, ...) fprintf(stderr, "[DBG] [%17s] [%15s:%4d] " format, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define DBG_PUTS(msg)
#define DBG_PRINT(format, ...)
#define DBG_PUT(msg)
#endif

#endif // __LOGGER_H__
