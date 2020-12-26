#ifndef __FILELIB_H__
#define __FILELIB_H__

#ifdef OSX
#define EXPORT __attribute__((visibility("default")))

#elif defined(WIN)

#pragma message "TODO"

#elif defined(LINUX)

#pragma message "TODO"

#else
#warning "Unknown sybsytem";
#define EXPORT
#endif // OSX


EXPORT
int read_file(FILE *f, int **pb, int **pe);
EXPORT
int write_file(FILE *f, int *pb, int *pe);


#endif // __FILELIB_H__
