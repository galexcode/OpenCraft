#include "player.h"
#include <stdlib.h>
#include <SDL/SDL_opengl.h>
#include "camera.h"

struct player *Player_NewPlayer(void)
{
	struct player *tmp;

	tmp = malloc(sizeof(struct player));
	tmp->name = "";
	tmp->pos.x = tmp->pos.y = tmp->pos.z = 0.0f;
	tmp->rot = tmp->pos;
	tmp->states = PLAYER_ALIVE;

	return tmp;
}

void Player_SetPos(struct player *plr, struct vec3 *pos)
{
	plr->pos = *pos;
}

void Player_SetPos3f(struct player *plr, float x, float y, float z)
{
	plr->pos.x = x;
	plr->pos.y = y;
	plr->pos.z = z;
}

void Player_SetRot(struct player *plr, struct vec3 *rot)
{
	plr->rot = *rot;
}

void Player_SetRot3f(struct player *plr, float x, float y, float z)
{
	plr->rot.x = x;
	plr->rot.y = y;
	plr->rot.z = z;
}

void Player_Draw(struct player *plr)
{
	glDisable(GL_CULL_FACE);
	glPushMatrix();

	glColor3f(1.0f, 1.0f, 0.0f);

	glTranslatef(plr->pos.x, plr->pos.y, plr->pos.z);
	glRotatef(plr->rot.z, 0.0f, 0.0f, 1.0f);
	glRotatef(plr->rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(plr->rot.x, 1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();

	glPopMatrix();
	glEnable(GL_CULL_FACE);
}

void Player_Free(struct player *plr)
{
	free(plr);
	plr = NULL;
}