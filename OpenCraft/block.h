#ifndef __BLOCK_H
#define __BLOCK_H
#include <stdint.h>
#include "stdsct.h"
#define BLOCK_DISPLAY_LIST 1
#define BLOCK_W 1.0f
#define BLOCK_HW 0.5f

enum block_type
{
	BLOCK_UNKNWON = 0,
	BLOCK_DIRT,
	BLOCK_STONE
};

struct block
{
	struct vec3 pos;
	struct col3 col;
	//uint8_t texture;
	uint8_t visible:1;
	enum block_type type;
	struct block *next;
};

struct block *Block_NewBlock(struct vec3 *pos, enum block_type type);
void Block_MakeDisplayList(void);
void Block_LoadTextures(void);
void Block_FreeDisplayList(void);
void Block_FreeTextures(void);
void Block_UpdateBlock(struct block *blck);
void Block_DrawBlock(struct block *blck);
void Block_Free(struct block *blck);



#endif//__BLOCK_H