#include "Game.hpp"


loadType Game::loadWindow[5] = {NULL,
				     &Game::loadMenuScreen , &Game::loadGameScreen,
				     &Game::loadHelpSreen  , &Game::loadResumeScreen
			       };

//Creates The Game
Game::Game(string nameOfGame,int startWidth,int startHeight,int defaultPosX,int defaultPosY)
{
	gameName = nameOfGame;
	defaultWidth = startWidth;
	defaultHeight = startHeight;
	windowPosX = defaultPosX;
	windowPosY = defaultPosY;
}

//Loads Menu Screen
void Game::loadMenuScreen()
{
	//Making The Window
	display = new LoadScreen(gameName,defaultWidth,defaultHeight,windowPosX,windowPosY);
	
	//Loading Background Image
	display->addPictureToDisplay("./GUI/startMenu.bmp",0,0,defaultWidth,defaultHeight);
	display->addPictureToDisplay("./GUI/highScore.bmp",defaultWidth-120,0,120,100);

	//Setting The Icon
	display->setIconofWindow("./GUI/gameIcon.bmp");

	//Deciding The Position of Start & Help
	SDL_Rect resumeOption = {75,defaultHeight-80,150,40};
	SDL_Rect startOption  = {275,defaultHeight-80,150,40};
	SDL_Rect helpOption   = {500,defaultHeight-80,70,35};

	//Deciding On Color
	SDL_Color color = {255,215,0};

	//Checking if there is any Cache Left
	fstream fout;fout.open("./GUI/gameCache.txt",ios::in);

	if(fout.peek() == std::ifstream::traits_type::eof())
	{
		startOption = resumeOption;
		resumeOption.w = 0;
		resumeOption.h = 0;
	}

	fout.close();

	//Loading The Text For Display
	(static_cast<LoadScreen*>(display))->setPositionRects(startOption,helpOption,resumeOption,color);

	//Finding The HighScore
	fout.open("./GUI/gameScore.txt",ios::in);
	int score;fout >> score;fout.close();
	
	//Loading Hiigh Score for Display`
	SDL_Color color1 = {0,255,255};
	display->addTextToDisplay(to_string(score),color1,defaultWidth-70,50,20,20);
}

//Loads New Game Screen
void Game::loadGameScreen()
{
	//Deciding on Color of Grid
	char gridColor[] = {(char)0,(char)255,(char)255,(char)255};

	//Making The Window
	display = new GameScreen(gameName,defaultWidth,defaultHeight,windowPosX,windowPosY,gridColor,8,4);

	//Laoding BackGround Images
	display->addPictureToDisplay("./GUI/gameOver.bmp",0,0,defaultWidth,defaultHeight);
	display->addPictureToDisplay("./GUI/gameMenu.jpg",0,0,defaultWidth,defaultHeight);
	display->addPictureToDisplay("./GUI/scoreBoard.bmp",defaultWidth/2 +150,defaultHeight/2-50,120,100);
	

	//Setting The Icon
	display->setIconofWindow("./GUI/gameIcon.bmp");

	//Adding Score Option
	// SDL_Color color = {0,0,0};
	// display->addTextToDisplay("SCORE",color,defaultWidth/2+150,defaultHeight/2-60,60,60);

	//Erasing Contents of File
	fstream fout;fout.open("./GUI/gameCache.txt",ios::out | ios::trunc);
	fout.close();
}


//Resumes The Previous Game
void Game::loadResumeScreen()
{
	//Deciding on Color of Grid
	char gridColor[] = {(char)0,(char)255,(char)255,(char)255};


	//Extracting File Object of Cached Data
	fstream fout; fout.open("./GUI/gameCache.txt",ios::in);

	//Making The Window
	display = new GameScreen(gameName,defaultWidth,defaultHeight,windowPosX,windowPosY,gridColor,8,fout);

	//Closing The File
	fout.close();

	//Laoding BackGround Image
	display->addPictureToDisplay("./GUI/gameOver.bmp",0,0,defaultWidth,defaultHeight);
	display->addPictureToDisplay("./GUI/gameMenu.jpg",0,0,defaultWidth,defaultHeight);
	display->addPictureToDisplay("./GUI/scoreBoard.bmp",defaultWidth/2 +150,defaultHeight/2-50,120,100);

	//Setting The Icon
	display->setIconofWindow("./GUI/gameIcon.bmp");

	//Erasing Contents of File
	fout.open("./GUI/gameCache.txt",ios::out | ios::trunc);
	fout.close();
}

//Loads The Help Menu
void Game::loadHelpSreen()
{
	//Making The Window
	display = new HelpScreen(gameName,defaultWidth,defaultHeight,windowPosX,windowPosY);
	
	//Loading Background Image
	display->addPictureToDisplay("./GUI/helpMenu.bmp",0,0,defaultWidth,defaultHeight);

	//Setting The Icon
	display->setIconofWindow("./GUI/gameIcon.bmp");
}

//Main Game Loop
void Game::gameLoop(int fps)
{	
	int token = 1;

	//Window Switching Loop
	while(true)
	{
		//Closing Window
		if(token == 0) break;

		//Loading Window
		(this->*loadWindow[token])();

		//Event Loop of the Window
		token = display->eventGameLoop(fps);

		//To Open the next window where it should it was last time
		display->getWindowDimensions(&defaultWidth,&defaultHeight);
		display->getWindowPosition(&windowPosX,&windowPosY);

		//Closing the Current Screen
		delete display;
		display = NULL;
	}
}
