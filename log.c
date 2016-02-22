#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "log.h"
#include "basic.h"
#include "strings.h"

#define TIME_BUF_SIZE	26

FILE *open(FILE *log)
{
	if((log = fopen(LOG_FILE, "a")) == NULL)
		return NULL;

	return log;
}

int clearfile(char *fname)
{
	FILE *f;
	if((f = fopen(fname, "w")) == NULL)
		return 1;

	fclose(f);

	return 0;
}

void logstr(char *str)
{
	if (DEBUG == TRUE) {
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[TIME_BUF_SIZE];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, TIME_BUF_SIZE, "%Y-%m-%d %H:%M:%S", timeinfo);

		fprintf(stderr, "%s - %s\n", buffer, str);

		FILE *log = malloc(sizeof(*log));
		log = open(log);
		fprintf(log, "%s - %s\n", buffer, str);
		fclose(log);
		free(log);
	}
}
