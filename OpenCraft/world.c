#include "world.h"
#include <stdlib.h>
#define RECT_2D_COLL(x1, y1, w1, h1, x2, y2, w2, h2) (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2)

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

struct block *World_FindBlock(struct world *wrld, struct vec3 *pos)
{
	struct block *i;

	for(i=wrld->blocks; i; i=i->next)
	{
		if(i->pos.x == pos->x && i->pos.y == pos->y && i->pos.z == pos->z)
			return i;
	}

	return NULL;
}

struct block *World_FindBlockXY(struct world *wrld, float x, float y)
{
	struct block *i;

	for(i=wrld->blocks; i; i=i->next)
	{
		if(RECT_2D_COLL(i->pos.x - BLOCK_HW, y, BLOCK_W, BLOCK_W, x, y, 0, 0))
			return i;
	}

	return NULL;
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