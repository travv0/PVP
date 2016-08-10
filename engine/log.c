#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "str.h"
#include "error.h"
#include "log.h"
#include "basic.h"

#define TIME_BUF_SIZE	26

int clearfile(char *fname)
{
	FILE *f;
	if((f = fopen(fname, "w")) == NULL)
		return 1;

	fclose(f);

	return 0;
}

/* logs a string to log file and stderr */
void __appendlog(void *l, char *fmt)
{
	if (DEBUG == TRUE) {
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[TIME_BUF_SIZE];
		char fullfmt[LOG_LINE_SIZE] = "%s - ";

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, TIME_BUF_SIZE, "%Y-%m-%d %H:%M:%S", timeinfo);

		strcat(fullfmt, fmt);
		strcat(fullfmt, "\n");

		fprintf(stderr, fullfmt, buffer, l);

		FILE *log;
		log = fopen(LOG_FILE, "a");

		if (log != NULL){
			fprintf(log, fullfmt, buffer, l);
			fclose(log);
		} else
			fprintf(stderr, "WARNING: Unable to write to log file\n");
	}
}
