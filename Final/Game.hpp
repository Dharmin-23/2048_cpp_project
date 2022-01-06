//Inlcludes
#pragma once
#include "Window.hpp"
#include "LoadScreen.hpp"
#include "GameScreen.hpp"
#include "HelpScreen.hpp"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


//Type Def for Better Readability
class Game;
typedef void(Game::*loadType)();

class Game
{
	private:
	/*Data Members*/
		Window* display;
		string gameName;
		int defaultWidth;
		int defaultHeight;
		int windowPosX;
		int windowPosY;

	/*Static Data Members*/
		static loadType loadWindow[5];

	public :
	/*CTOR & DTOR*/
		Game(string nameOfGame,int startWidth,int startHeight,int defaultPosX,int defaultPosY);

	/*Loading Window*/
		void loadMenuScreen();
		void loadHelpSreen();
		void loadResumeScreen();
		void loadGameScreen();
	
	/*Game Loop*/
		void gameLoop(int fps);	
};