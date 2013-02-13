#ifndef __GAME_H
#define __GAME_H
#define FPS 60
#define SCREEN_W 1024
#define SCREEN_H 768
#include "stdsct.h"

extern bool_t game_running;

void Game_Init(void);
void Game_Update(void);
void Game_Draw(void);
void Game_Quit(void);



#endif//__GAME_H