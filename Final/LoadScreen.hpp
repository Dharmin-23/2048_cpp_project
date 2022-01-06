#pragma once
#include "Window.hpp"
#include "Image.hpp"
#include "Text.hpp"
#include "Button.hpp"

#include <string>
using namespace std;

class LoadScreen : public Window
{
	private:
	/*Data Members*/
		Button* helpButton;
		Button* startButton;
		Button* resumeButton;

	public :
	/*CTOR & DTOR*/
		LoadScreen(string gameName,int startWidth,int startHeight,int windowPosX,int windowPosY);
	
	/*GUI RELATED*/
		int eventGameLoop(int fps);
	
	/*SETTERS*/
		void setPositionRects(SDL_Rect startRect,SDL_Rect helpRect,
						SDL_Rect resumeRect,SDL_Color color);

};