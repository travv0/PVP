/* object manager to hold game objects so they can be easily looped through
 * for drawing, updating, etc. */
#ifndef __OBJMANAGER_H
#define __OBJMANAGER_H

#include "object.h"

#define OBJMANAGER_INITIAL_CAPACITY	2
#define OBJMANAGER_CAPUP_RATE		1.5

/* struct for the object manager */
struct objm {
	unsigned long long	objcnt;	/* the number of objects in the manager */
	struct object		*objs;	/* array of objects */
	unsigned long long	cap;	/* capacity of manager */
};

/* initialize the object manager */
void objminit(struct objm *mgr);

/* increase object manager's capacity */
void objmcapup(struct objm *mgr);

/* add an object to the manager */
void objmadd(struct objm *mgr, struct object obj);

/* get an object from the manager */
struct object *objmget(struct objm *mgr, int idx);

/* free memory allocated by object manager */
void objmfree(struct objm *mgr);

/* returns count of objects in the manager */
unsigned long long objmcnt(struct objm *mgr);

#endif
