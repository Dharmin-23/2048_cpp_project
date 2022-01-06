#include "LoadScreen.hpp"

//CTOR
LoadScreen::LoadScreen(string gameName,int startWidth,int startHeight,int windowPosX,int windowPosY) : 
	        Window(gameName,startWidth,startHeight,windowPosX,windowPosY)
{
	/*No Explicit CTOR NEEDED*/
}

//Sets Postions To Be Tracked on Screen
void LoadScreen::setPositionRects(SDL_Rect startRect,SDL_Rect helpRect,SDL_Rect resumeRect,SDL_Color color)
{
	//Adding Buttons
	resumeButton = new Button(Window::windowRender,"Resume Game",color,resumeRect);
	startButton  = new Button(Window::windowRender,"Start Game",color,startRect);
	helpButton   = new Button(Window::windowRender,"Help",color,helpRect);
}

//Manges The Event Loop of Game Screen
int LoadScreen::eventGameLoop(int fps)
{
	bool eventLoop = true;int token = 1;

	while(eventLoop)
	{
		//Tracking Events
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{

			if(event.type == SDL_QUIT)
			{
				token = 0;
				eventLoop = false;
			}

			else if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if(startButton->trackMouse())
				{
					token = 2;
					eventLoop = false;
				}

				else if(helpButton->trackMouse())
				{
					token = 3;
					eventLoop = false;
				}

				else if(resumeButton->trackMouse())
				{
					token = 4;
					eventLoop = false;
				}
			}
		}

		if(!eventLoop) break;
		
		SDL_RenderClear(Window::windowRender);
		Window::loadImagesToDisplay();
		Window::loadTextToDisplay();
		resumeButton->renderButton();
		startButton->renderButton();
		helpButton->renderButton();
		SDL_RenderPresent(Window::windowRender);

		//FPS Setting
		SDL_Delay(1000/fps);
	}

	return token;
}