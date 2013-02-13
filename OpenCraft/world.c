#include "world.h"
#include <stdlib.h>

struct world *World_NewWorld(void)
{
	struct world *wrld;

	wrld = malloc(sizeof(struct world));
	wrld->blocks = NULL;
	return wrld;
}

void World_AddBlock(struct world *wrld, struct block *blck)
{
	blck->next = wrld->blocks;
	wrld->blocks = blck;
}

void World_DelBlock(struct world *wrld, struct block *blck)
{
	struct block *i;

	for(i=wrld->blocks; i; i=i->next)
	{
		if(i->next == blck)
		{
			i->next = blck->next;
			Block_Free(blck);
			return;
		}
	}
}

void World_Free(struct world *wrld)
{
	struct block *i;

	for(i=wrld->blocks; i; i=i->next)
		Block_Free(i);
	free(wrld);
}

void World_UpdateWorld(struct world *wrld)
{
	struct block *i;

	for(i=wrld->blocks; i; i=i->next)
		Block_UpdateBlock(i);
}

void World_DrawWorld(struct world *wrld)
{
	struct block *i;

	for(i=wrld->blocks; i; i=i->next)
		Block_DrawBlock(i);
}