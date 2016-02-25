#ifndef __BASIC_H
#define __BASIC_H

#define TRUE	1
#define FALSE	0

/* the frame rate we're trying to hit.
 * make sure this is a double so we don't have to worry about accidentally
 * demoting to int when using it. */
#define TARGET_FRAME_RATE	60.0

extern int DEBUG;
extern float DT;	/* change in time since last go in the main loop */

#endif

