#ifndef __LOG_H
#define __LOG_H

#include <stdio.h>

#define LOG_LINE_SIZE	1000

/* logs l using format string fmt */
#define log(l,fmt) (__log((void *)l, fmt))
void __log(void *l, char *fmt);

int clearfile(char *fname);
void logint(int i);

#endif
