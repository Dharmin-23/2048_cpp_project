#pragma once
#include "Text.hpp"

#include <string>
using namespace std;

class Button
{
	private:
	/*Data Members*/
		Text* buttonText;
		SDL_Rect trackRect;
		SDL_Renderer* buttonRender;
		float defaultWidth;
		float defaultHeight;
	
	public:
	/*CTOR & DTOR*/
		Button(SDL_Renderer* renderer,string text,SDL_Color textColor,SDL_Rect displayRect);
		~Button();
	
	/*GUI Related*/
		bool trackMouse();
		void renderButton();
};