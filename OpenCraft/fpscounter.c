#include "fpscounter.h"
#include <SDL/SDL.h>
#include <string.h>

static unsigned int time_start, time_now;

void FPSCount_Init(void)
{
	time_start = time_now = SDL_GetTicks();
}

void FPSCount_Tick(void)
{
	static int frames = 0;

	time_now = SDL_GetTicks();

	if(time_now > time_start + 1000)
	{
		char title[9 + 3 + 7 + 1]; //OpenCraft - FPS: 60\n

		sprintf(title, "OpenCraft - FPS: %d\n", frames);
		SDL_WM_SetCaption(title, NULL);

		frames = 0;
		time_start = SDL_GetTicks();
	}

	frames++;
}