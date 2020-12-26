#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>

int get_file_len(FILE *f, int *len);
int read_file(FILE *f, int **pb, int **pe);
int write_file(FILE *f, int *pb, int *pe);

#endif // __FILE_H__
