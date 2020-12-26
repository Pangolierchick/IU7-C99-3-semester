#ifndef __DEFINES_H__
#define __DEFINES_H__

#define GENERICK_POINTER(p)             (void *) p    

#define NO_ERROR                        0

#define INPUT_FILENAME                  argv[1]
#define OUTPUT_FILENAME                 "out.txt"

typedef enum bool_s
{
    FALSE,
    TRUE
} bool_t;

#endif // __DEFINES_H__
