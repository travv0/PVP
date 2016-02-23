#ifndef __LOG_H
#define __LOG_H

#include <stdio.h>

#define LOG_LINE_SIZE	1000

FILE *open(FILE *log);
int clearfile(char *fname);
void logstr(char *str);
void logint(int i);

#endif
