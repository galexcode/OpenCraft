#include "block.h"
#include <SDL/SDL_opengl.h>
#include <IL/il.h>
#include <stdlib.h>

static void RegisterTexture(uint32_t id, const char *file)
{
	ilBindImage(id);
	ilLoad(IL_BMP, file);
	
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	ilDeleteImage(1);
}

struct block *Block_NewBlock(struct vec3 *pos, enum block_type type)
{
	struct block *blck;

	blck = malloc(sizeof(struct block));
	blck->col.r = blck->col.g = blck->col.b = 1.0f;
	blck->pos = *pos;
	blck->type = type;
	blck->visible = 1;
	return blck;
}

void Block_MakeDisplayList(void)
{
	glNewList(BLOCK_DISPLAY_LIST, GL_COMPILE);

	glBegin(GL_TRIANGLE_STRIP);
	//Front
	glTexCoord2i(0, 1); glVertex3f(-BLOCK_HW, BLOCK_HW, BLOCK_HW);
	glTexCoord2i(0, 0); glVertex3f(-BLOCK_HW, -BLOCK_HW, BLOCK_HW);
	glTexCoord2i(1, 1); glVertex3f(BLOCK_HW, BLOCK_HW, BLOCK_HW);
	glTexCoord2i(1, 0); glVertex3f(BLOCK_HW, -BLOCK_HW, BLOCK_HW);
	//Left
	glTexCoord2i(0, 1); glVertex3f(-BLOCK_HW, BLOCK_HW, -BLOCK_HW);
	glTexCoord2i(0, 0); glVertex3f(-BLOCK_HW, -BLOCK_HW, -BLOCK_HW);
	glTexCoord2i(1, 1); glVertex3f(-BLOCK_HW, BLOCK_HW, BLOCK_HW);
	glTexCoord2i(1, 0); glVertex3f(-BLOCK_HW, -BLOCK_HW, BLOCK_HW);
	//Back
	glTexCoord2i(0, 1); glVertex3f(BLOCK_HW, BLOCK_HW, -BLOCK_HW);
	glTexCoord2i(0, 0); glVertex3f(BLOCK_HW, -BLOCK_HW, -BLOCK_HW);
	glTexCoord2i(1, 1); glVertex3f(-BLOCK_HW, BLOCK_HW, -BLOCK_HW);
	glTexCoord2i(1, 0); glVertex3f(-BLOCK_HW, -BLOCK_HW, -BLOCK_HW);
	//Right
	glTexCoord2i(0, 1); glVertex3f(BLOCK_HW, BLOCK_HW, BLOCK_HW);
	glTexCoord2i(0, 0); glVertex3f(BLOCK_HW, -BLOCK_HW, BLOCK_HW);
	glTexCoord2i(1, 1); glVertex3f(BLOCK_HW, BLOCK_HW, -BLOCK_HW);
	glTexCoord2i(1, 0); glVertex3f(BLOCK_HW, -BLOCK_HW, -BLOCK_HW);
	//Top
	glTexCoord2i(0, 1); glVertex3f(-BLOCK_HW, BLOCK_HW, -BLOCK_HW);
	glTexCoord2i(0, 0); glVertex3f(-BLOCK_HW, BLOCK_HW, BLOCK_HW);
	glTexCoord2i(1, 1); glVertex3f(BLOCK_HW, BLOCK_HW, -BLOCK_HW);
	glTexCoord2i(1, 0); glVertex3f(BLOCK_HW, BLOCK_HW, BLOCK_HW);
	//Bottom
	glTexCoord2i(0, 1); glVertex3f(-BLOCK_HW, -BLOCK_HW, BLOCK_HW);
	glTexCoord2i(0, 0); glVertex3f(-BLOCK_HW, -BLOCK_HW, -BLOCK_HW);
	glTexCoord2i(1, 1); glVertex3f(BLOCK_HW, -BLOCK_HW, BLOCK_HW);
	glTexCoord2i(1, 0); glVertex3f(BLOCK_HW, -BLOCK_HW, -BLOCK_HW);
	glEnd();

	glEndList();
}

void Block_LoadTextures(void)
{
	RegisterTexture(BLOCK_DIRT, "dirt.bmp");
	RegisterTexture(BLOCK_STONE, "stone.bmp");
}

void Block_FreeDisplayList(void)
{
	glDeleteLists(BLOCK_DISPLAY_LIST, 1);
}

void Block_FreeTextures(void)
{
	uint32_t tex;

	tex = BLOCK_DIRT;
	glDeleteTextures(1, &tex);
	tex = BLOCK_STONE;
	glDeleteTextures(1, &tex);
}

void Block_UpdateBlock(struct block *blck)
{
	//if(blck is inside viewfrustum)
	//	blck->visible = 1;
	//	else blck->visible = 0;

	//blck->visible = 1;
}

void Block_DrawBlock(struct block *blck)
{
	if(!blck->visible) return;

	glColor3f(blck->col.r, blck->col.g, blck->col.b);
	glBindTexture(GL_TEXTURE_2D, blck->type);
	glTranslatef(blck->pos.x, blck->pos.y, blck->pos.z);
	glCallList(BLOCK_DISPLAY_LIST);
	glTranslatef(-blck->pos.x, -blck->pos.y, -blck->pos.z);
}

void Block_Free(struct block *blck)
{
	free(blck);
	blck = NULL;
}