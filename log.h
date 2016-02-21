#ifndef __LOG_H
#define __LOG_H

FILE *open(FILE *log);
int clearfile(char *fname);
void logstr(char *str);

#endif
