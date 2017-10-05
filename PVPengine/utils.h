/* some utility functions */
#ifndef __UTILS_H
#define __UTILS_H

/* get seconds since SDL has been initialized */
double getseconds(void);

/* get custom ticks since SDL has been initialized */
double getticks(void);

/* convert seconds to milliseconds */
double sectomsec(double sec);

#endif
