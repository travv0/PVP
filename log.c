#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sdl.h"

#include "log.h"
#include "basic.h"
#include "strings.h"
#include "error.h"

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

void logstr(char *str, char type)
{
	if (DEBUG == TRUE) {
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[TIME_BUF_SIZE];
		char *fmtstr = malloc(sizeof(char) * LOG_LINE_SIZE);

		switch (type) {
		case 's':
			fmtstr = "%s - %s\n";
			break;
		case 'd':
			fmtstr = "%s - %d\n";
			break;
		default:
			snprintf(fmtstr, LOG_LINE_SIZE, "'%c'", type);
			SDL_SetError(fmtstr);
			throw_err(LOG_FMT_NOT_SUPPORTED_WARN);
			return;
		}

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, TIME_BUF_SIZE, "%Y-%m-%d %H:%M:%S", timeinfo);

		fprintf(stderr, fmtstr, buffer, str);

		FILE *log = malloc(sizeof(*log));
		log = open(log);
		fprintf(log, fmtstr, buffer, str);
		fclose(log);
		free(log);
		free(fmtstr);
	}
}
