#include "game.h"
#include <math.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <IL/il.h>
#include "world.h"
#include "camera.h"
#include "player.h"
#ifndef M_PI
#define M_PI 3.14159265
#endif
#define MOUSE_SPEED 0.5f


bool_t game_running = TRUE;
struct world *myWorld;
float cam_speed = 0.05f;
struct player *myPlayer;


static void glPerspective(double fovy, double aspect, double zNear, double zFar)
{
	double xmin, xmax, ymin, ymax;

	ymax = zNear * tan(fovy * M_PI / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;

	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

void Game_Init(void)
{
	struct vec3 bpos = {0.0f, 0.0f, 0.0f};
	int y, s;

	//SDL
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_HWSURFACE | SDL_OPENGL);
	SDL_WM_SetCaption("OpenCraft", NULL);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, TRUE);
	SDL_ShowCursor(SDL_FALSE);
	SDL_WarpMouse(SCREEN_W >> 1, SCREEN_H >> 1);
	//OpenGL
	glClearColor(0.2f, 0.6f, 0.8f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPerspective(60.0, (double)SCREEN_W / (double)SCREEN_H, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	//DevIL
	ilInit();
	//Block & World
	Block_MakeDisplayList();
	Block_LoadTextures();

	myWorld = World_NewWorld();
	for(y=0; y<40; y++)
	{
		int x;

		bpos.y = BLOCK_W * y;
		s = y;

		for(x=0; x<50; x++)
		{
			if(s++ % 2)
				World_AddBlock(myWorld, Block_NewBlock(&bpos, BLOCK_DIRT));
			else World_AddBlock(myWorld, Block_NewBlock(&bpos, BLOCK_STONE));
			bpos.x += BLOCK_W;
		}

		bpos.x = 0.0f;
	}

	//Camera
	Cam_SetPos3f(0.0f, 0.0f, 5.0f);
	Cam_SetRot3f(0.0f, 0.0f, 0.0f);

	myPlayer = Player_NewPlayer();
	Player_SetPos3f(myPlayer, 13.0f, 5.0f, 5.0f);
}

void Game_Update(void)
{
	SDL_Event event;
	uint8_t *keys;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT) game_running = FALSE;
		if(event.type == SDL_MOUSEMOTION)
		{
			Cam_Rotate3f(((SCREEN_H >> 1) - event.motion.y) * MOUSE_SPEED, ((SCREEN_W >> 1) - event.motion.x) * MOUSE_SPEED, 0.0f);
			SDL_WarpMouse(SCREEN_W >> 1, SCREEN_H >> 1);
		}
	}

	keys = SDL_GetKeyState(NULL);
	if(keys[SDLK_ESCAPE]) game_running = FALSE;
	if(keys[SDLK_w]) Cam_Move(cam_speed, 0.0f);
	if(keys[SDLK_s]) Cam_Move(cam_speed, 180.0f);
	if(keys[SDLK_a]) Cam_Move(cam_speed, 90.0f);
	if(keys[SDLK_d]) Cam_Move(cam_speed, -90.0f);
	if(keys[SDLK_SPACE]) Cam_Translate3f(0.0f, cam_speed, 0.0f);
	if(keys[SDLK_LALT] || keys[SDLK_LCTRL]) Cam_Translate3f(0.0f, -cam_speed, 0.0f);
	if(keys[SDLK_BACKSPACE])
	{
		Cam_SetPos3f(0.0f, 0.0f, 5.0f);
		Cam_SetRot3f(0.0f, 0.0f, 0.0f);
	}
	if(keys[SDLK_LSHIFT]) cam_speed = 0.2f;
	else cam_speed = 0.05f;
	if(keys[SDLK_RCTRL])
	{
		if(Cam_GetBound())
			Cam_Unbind();
		else
			Cam_Bind(&myPlayer->pos, &myPlayer->rot);
		keys[SDLK_RCTRL] = FALSE;
	}

	World_UpdateWorld(myWorld);
}

void Game_Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Cam_Draw();
	Player_Draw(myPlayer);

	World_DrawWorld(myWorld);
}

void Game_Quit(void)
{
	Player_Free(myPlayer);
	World_Free(myWorld);
	Block_FreeTextures();
	Block_FreeDisplayList();
	SDL_Quit();
}