#include "GameScreen.hpp"

//CTOR
GameScreen::GameScreen(string gameName,int startWidth,int startHeight,
		int windowPosX,int windowPosY,char gridColor[],int gridFactor,int size) : 
	        		Window(gameName,startWidth,startHeight,windowPosX,windowPosY)
{
	gameBoard = new Grid(Window::windowRender,gridColor,gridFactor,size);
}

//CTOR + Constructing Board Using Cached Data
GameScreen::GameScreen(string gameName,int startWidth,int startHeight,
			int windowPosX,int windowPosY,char gridColor[],int gridFactor,fstream& fout):
				Window(gameName,startWidth,startHeight,windowPosX,windowPosY)
{
	newGame = false;
	gameBoard = new Grid(Window::windowRender,gridColor,gridFactor,fout);

}

//DTOR
GameScreen::~GameScreen()
{
	delete gameBoard;
}

//Event Game Loop Implementation
int GameScreen::eventGameLoop(int fps)
{
	Music* music;
	bool eventLoop = true;int token = 1;
	char control;int score;
	SDL_Color color = {0,255,255};

	Window::loadImagesToDisplay();

	//Loading New Game or Paused Game
	if(newGame)
	{
		gameBoard->buildGridFrame();
		gameBoard->startGrid();
	}

	else
	{
		gameBoard->buildGridFrame();
	}

	//Collecting Score
	score = gameBoard->getScore();
	Window::addTextToDisplay(to_string(score),color,defaultWidth/2 +200,defaultHeight/2+5,20,20);
	gameBoard->displayGirdValues();
	Window::loadTextToDisplay();
	SDL_RenderPresent(Window::windowRender);

	while(eventLoop)
	{
		SDL_Event event;bool change = false;

		while(SDL_PollEvent(&event))
		{
			//Game Quit Event
			if(event.type == SDL_QUIT)
			{
				eventLoop = false;
				token = 0;
				gameBoard->saveGrid();
				break;		
			}

			//Responding To Key Presses
			else if (event.type == SDL_KEYDOWN)
			{
				music->playchannel(1, "./GUI/key.wav", 0);
				switch(event.key.keysym.sym)
				{
					
					case SDLK_UP:
						change = true;
						control  ='s';			
						break;
					
					case SDLK_DOWN:
						change = true;
						control = 'w';
						break;
					
					case SDLK_RIGHT:
						change = true;
						control = 'd';
						break;
					
					case SDLK_LEFT:
						change = true;
						control = 'a';
						break;
					
					case SDLK_q:
						change = true;
						eventLoop = false;
						token = 1;
						break;
					
					case SDLK_u:
						change = true;
						control = 'u';
						break;
					
					case SDLK_s:
						eventLoop = false;
						token = 1;
						gameBoard->saveGrid();
						break;
				}
			}

		}

		if(gameBoard->gameOver())
		{
			eventLoop = false;
			token = 1;

			//Swapping BackGround With End Game Screen
			std::swap(Window::windowImageList[0],Window::windowImageList[1]);

			//Deleting The Score Board
			delete Window::windowImageList[2];
			Window::windowImageList.pop_back();
			
			//Displaying End Game Screen
			SDL_RenderClear(Window::windowRender);
			Window::loadImagesToDisplay();
			SDL_RenderPresent(Window::windowRender);
			music->playchannel(0, "./GUI/end.wav", 0);
			SDL_Delay(2000);
		}

		//Loop Breaking Condition
		if(!eventLoop)	break;

		if(change)
		{
			gameBoard->updateBoard(control);
			score = gameBoard->getScore();
			Window::windowTextList[0]->changeTextToBeDisplayed(to_string(score));
		}

		SDL_RenderClear(Window::windowRender);

		Window::loadImagesToDisplay();
		Window::loadTextToDisplay();
		gameBoard->buildGridFrame();
		gameBoard->displayGirdValues();
		SDL_RenderPresent(Window::windowRender);


		SDL_Delay(1000/fps);
	}

	//Opening File and Finding Previous Maximum
	fstream fout;fout.open("./GUI/gameScore.txt",ios::in);
	int scorePrevious;fout >> scorePrevious;fout.close();

	//Finding The Current Maximum
	int scoreMax = std::max(score,scorePrevious);
	
	//Re writing The Maximum
	fout.open("./GUI/gameScore.txt",ios::out | ios::trunc);
	fout << scoreMax << endl;
	fout.close();

	return token;
}

