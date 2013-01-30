#include "game.h"
#include <SDL/SDL.h>

int main(int argc, char **argv)
{
	unsigned int time_start, time_end;

	Game_Init();
	
	while(game_running)
	{
		time_start = SDL_GetTicks();
		Game_Update();
		Game_Draw();
		SDL_GL_SwapBuffers();
		time_end = SDL_GetTicks();

		if(1000/FPS > time_end - time_start)
			SDL_Delay(1000/FPS - (time_end - time_start));
	}

	Game_Quit();
	return 0;
}