/* this file handles logging.
 * logging should only be done if DEBUG is not 0 */
#ifndef __LOG_H
#define __LOG_H

#include <stdio.h>

#define LOG_LINE_SIZE	1000

/* clears contents of file with name fname */
int clearfile(char *fname);

/* logs the given string to log file and stderr with timestamp */
void logstr(char *str);

#endif
