#include "Text.hpp"

#include <string>
using namespace std;

//Makes The Ready for Display
Text::Text(SDL_Renderer* renderer,string text,SDL_Color textColor,SDL_Rect displayRect)
{
	textRender = renderer;
	textRect = displayRect;
	textFont = TTF_OpenFont("./GUI/font.ttf", 100);

	textSurface = TTF_RenderText_Solid( textFont, text.c_str(), textColor);
	textTexture = SDL_CreateTextureFromSurface(textRender, textSurface);
	intialColor = textColor;

	int width,height;
	SDL_GetRendererOutputSize(textRender,&width,&height);
	windowWidth = width;
	windowHeight = height;
}

//Removes the Text from Display
Text::~Text()
{
	textRender = NULL;
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

//Renders The Given Text
void Text::renderText()
{	
	//Finding Window Dimensions
	int width,height;
	SDL_GetRendererOutputSize(textRender,&width,&height);
	
	//Scaling Down - In Case of Re size
	float xFrac = (width/(windowWidth));
	float yFrac = (height/(windowHeight));

	SDL_Rect newRect = {static_cast<int>((textRect.x)*xFrac),
			    static_cast<int>((textRect.y)*yFrac), 
			    static_cast<int>((textRect.w)*xFrac),
			    static_cast<int>((textRect.h)*yFrac)};

	SDL_RenderCopy(textRender,textTexture,NULL,&newRect);
}

//Changes The Text Rect
void Text::changeTextRect(SDL_Rect displayRect)
{
	textRect = displayRect;
}


//Changes The Color of The Text
void Text::changeColorOfText(SDL_Color newColor)
{
	SDL_SetTextureColorMod(textTexture,newColor.r,newColor.g,newColor.b);
}


//Resets The Color of The Text
void Text::resetColorOfText()
{
	SDL_SetTextureColorMod(textTexture,intialColor.r,intialColor.g,intialColor.b);
}

void Text::changeTextToBeDisplayed(string newText)
{
	//Chaning Text
	textToBeDisplayed = newText;

	//Destroying Old Contents
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);

	textSurface = TTF_RenderText_Solid(textFont,newText.c_str(),intialColor);
	textTexture = SDL_CreateTextureFromSurface(textRender, textSurface);
}