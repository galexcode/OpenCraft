#ifndef __WORLD_H
#define __WORLD_H
#include "block.h"

struct world
{
	struct block *blocks;
	//char *name;
	//...
};

struct world *World_NewWorld(void);
void World_Free(struct world *wrld);
void World_AddBlock(struct world *wrld, struct block *blck);
void World_DelBlock(struct world *wrld, struct block *block);
void World_UpdateWorld(struct world *wrld);
void World_DrawWorld(struct world *wrld);



#endif//__WORLD_H