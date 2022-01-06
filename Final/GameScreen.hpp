//Includes
#include "Window.hpp"
#include "Grid.hpp"
#include "Button.hpp"
#include "Music.hpp"

#include <string>
#include <fstream>
using namespace std;

class GameScreen : public Window
{
	private:
	/*Data Members*/
		Grid* gameBoard;
		bool newGame = true;

	public :
	/*CTOR & DTOR*/	
		GameScreen(string gameName,int startWidth,int startHeight,
			int windowPosX,int windowPosY,char gridColor[],int girdFactor,int size);

		GameScreen(string gameName,int startWidth,int startHeight,
			int windowPosX,int windowPosY,char gridColor[],int gridFactor,fstream& fout);

		~GameScreen();
	
	/*GUI Related*/
		int eventGameLoop(int fps);
};