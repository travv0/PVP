#include "objmanager.h"

void objminit(struct objm *mgr)
{
	mgr->cap = OBJMANAGER_INITIAL_CAPACITY;
	mgr->objcnt = 0;
	mgr->objs = malloc(sizeof(mgr->objs) * mgr->cap);
}

void objmcapup(struct objm *mgr)
{
	mgr->cap = mgr->cap * OBJMANAGER_CAPUP_RATE;
	mgr->objs = realloc(mgr->objs, sizeof(mgr->objs) * mgr->cap);
}

void objmadd(struct objm *mgr, struct object obj)
{
	if (mgr->objcnt >= mgr->cap / OBJMANAGER_CAPUP_RATE)
		objmcapup(mgr);

	mgr->objs[mgr->objcnt] = obj;
}

void objmget(struct objm *mgr, int idx)
{
	if (idx >= mgr->objcnt || idx < 0)
		throw_err(OBJM_IDX_OOR);

	return mgr->objs[idx];
}

void objmfree(struct objm *mgr)
{
	free(mgr->objs);
	free(mgr);
}
