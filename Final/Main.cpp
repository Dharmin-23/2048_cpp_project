#include "Game.hpp"
#include "Music.hpp"

#define GAMENAME "Double Trouble"
#define WINDOWWIDTH 680
#define WINDOWHEIGHT 400

int main()
{	
	Game* game = new Game(GAMENAME,WINDOWWIDTH,WINDOWHEIGHT,
				        SDL_WINDOWPOS_CENTERED,
				        SDL_WINDOWPOS_CENTERED);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	Music* music = new Music();
	music->playmusic("GUI/bckgrnd.wav");
	TTF_Init();
	game->gameLoop(60);
	TTF_Quit();
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	delete game;
	return 0;
}
