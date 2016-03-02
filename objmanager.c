#include "objmanager.h"
#include "error.h"

void objminit(struct objm **mgr)
{
	*mgr = malloc(sizeof(struct objm));
	if (*mgr == NULL)
		throw_err(MALLOC_FAILED);

	(*mgr)->cap = 0;
	(*mgr)->objcnt = 0;
	(*mgr)->objs = NULL;
}

void objmcapup(struct objm *mgr)
{
	mgr->cap = mgr->cap * OBJMANAGER_CAPUP_RATE;
	mgr->objs = realloc(mgr->objs, sizeof(struct object) * mgr->cap);
}

void objmadd(struct objm *mgr, struct object obj)
{
	if (mgr == NULL) {
		throw_err(OBJM_NOT_INIT);
	}

	if (mgr->objcnt == 0) {
		mgr->cap = OBJMANAGER_INITIAL_CAPACITY;
		mgr->objs = malloc(sizeof(struct object) * mgr->cap);

		if (mgr->objs == NULL)
			throw_err(MALLOC_FAILED);
	}

	if (mgr->objcnt >= mgr->cap)
		objmcapup(mgr);

	mgr->objs[mgr->objcnt] = obj;
}

struct object *objmget(struct objm *mgr, int idx)
{
	if (idx >= mgr->objcnt || idx < 0)
		throw_err(OBJM_IDX_OOR);

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
