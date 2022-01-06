//Includes
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

using namespace std;

class Text
{
	private:
	/*Data Members*/
		float windowWidth;
		float windowHeight;
		SDL_Renderer* textRender;
		SDL_Texture* textTexture;
		SDL_Surface* textSurface;
		SDL_Color intialColor;
		string textToBeDisplayed;
		SDL_Rect textRect;
		TTF_Font* textFont;
	
	public :
	/*CTOR & DTOR*/
		Text(SDL_Renderer* renderer,string text,SDL_Color textColor,SDL_Rect displayRect);
		~Text();
	
	/*GUI Related*/
		void renderText();
		void changeTextRect(SDL_Rect displayRect);
		void changeColorOfText(SDL_Color newColor);
		void resetColorOfText();
		void changeTextToBeDisplayed(string newText);
};