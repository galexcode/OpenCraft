#ifndef __PLAYER_H
#define __PLAYER_H
#include "stdsct.h"

enum player_states
{
	PLAYER_ALIVE = 1,
	PLAYER_CROUCHING,
	PLAYER_SWIMMING
};

struct player
{
	char *name;
	enum player_states states;
	struct vec3 pos;
	struct vec3 rot;
};

struct player *Player_NewPlayer(void);
void Player_SetPos(struct player *plr, struct vec3 *pos);
void Player_SetPos3f(struct player * plr, float x, float y, float z);
void Player_SetRot(struct player *plr, struct vec3 *rot);
void Player_SetRot3f(struct player *plr, float x, float y, float z);
void Player_Draw(struct player *plr);
void Player_Free(struct player *plr);





#endif//__PLAYER_H