#include "HelpScreen.hpp"

//CTOR
HelpScreen::HelpScreen(string gameName,int startWidth,int startHeight,int windowPosX,int windowPosY) : 
	        Window(gameName,startWidth,startHeight,windowPosX,windowPosY)
{

}

//GUI Related
int HelpScreen::eventGameLoop(int fps)
{
	bool eventLoop = true;int token = 1;
	
	while(eventLoop)
	{
		SDL_Event event;

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				eventLoop = false;
				token = 0;
				break;
			}

			else if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_q:
						eventLoop = false;
						token = 1;
						break;
				}

				break;
			}
			
		}

		if(!eventLoop)	break;

		SDL_RenderClear(Window::windowRender);
		Window::loadImagesToDisplay();
		SDL_RenderPresent(Window::windowRender);

		SDL_Delay(1000/fps);
	}

	return token;
}