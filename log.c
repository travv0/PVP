#include <stdio.h>

#include "log.h"

FILE *open(FILE *log)
{
	if ((log = fopen("log.txt", "w")) == NULL)
		return NULL;

	return log;
}
