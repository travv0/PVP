#include "objmanager.h"
#include "error.h"
#include "log.h"

void objminit(struct objm **mgr)
{
	*mgr = malloc(sizeof(struct objm));
	if (*mgr == NULL)
		throw_err(MALLOC_FAILED_ERR);

	(*mgr)->cap = 0;
	(*mgr)->objcnt = 0;
	(*mgr)->objs = NULL;
	log((sizeof(struct objm)),
			"Object manager: allocated new object manager "
			"of size %llu");
}

void objmcapup(struct objm *mgr)
{
	mgr->cap = mgr->cap * OBJMANAGER_CAPUP_RATE;
	mgr->objs = realloc(mgr->objs, sizeof(struct object) * mgr->cap);
	log((sizeof(struct object) * mgr->cap),
			"Object manager: reallocated array to size %llu");
}

void objmadd(struct objm *mgr, struct object obj, int x, int y)
{
	if (mgr == NULL) {
		throw_err(OBJM_NOT_INIT_ERR);
	}

	if (mgr->objcnt == 0) {
		mgr->cap = OBJMANAGER_INITIAL_CAPACITY;
		mgr->objs = malloc(sizeof(struct object) * mgr->cap);

		if (mgr->objs == NULL)
			throw_err(MALLOC_FAILED_ERR);

		log((sizeof(struct object) * mgr->cap),
				"Object manager: allocated new array of size %llu");
	}

	if (mgr->objcnt >= mgr->cap)
		objmcapup(mgr);

	obj.x = x;
	obj.y = y;

	mgr->objs[mgr->objcnt] = obj;
	mgr->objcnt++;
}

struct object *objmget(struct objm *mgr, int idx)
{
	if (idx >= mgr->objcnt || idx < 0)
		throw_err(OBJM_IDX_OOR_WARN);

	return &mgr->objs[idx];
}

void objmfree(struct objm *mgr)
{
	free(mgr->objs);
	free(mgr);
}

unsigned long long objmcnt(struct objm *mgr)
{
	return mgr->objcnt;
}
