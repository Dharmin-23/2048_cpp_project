#include "Button.hpp"

//Constructs The Given Button
Button::Button(SDL_Renderer* renderer,string text,SDL_Color textColor,SDL_Rect displayRect)
{
	buttonText = new Text(renderer,text,textColor,displayRect);
	trackRect  = displayRect;
	buttonRender = renderer;

	int width,height;
	SDL_GetRendererOutputSize(buttonRender,&width,&height);
	defaultWidth = width;
	defaultHeight = height;

}

//Deletes The Button
Button::~Button()
{
	delete buttonText;
	buttonRender = NULL;
}

//Checks if The Mouse is in the Range
bool Button::trackMouse()
{
	int mousePosX,mousePosY,width,height;

	//Tracking Mouse Co-ordinates
	SDL_GetMouseState(&mousePosX,&mousePosY);

	//Finding new Co-ordinates In-case of Re size
	SDL_GetRendererOutputSize(buttonRender,&width,&height);

	//Re Size Factors
	float xFrac = width/defaultWidth;
	float yFrac = height/defaultHeight;

	//Old Co-ordinates
	int x1 = trackRect.x,x2 = trackRect.x + trackRect.w;
	int y1 = trackRect.y,y2 = trackRect.y + trackRect.h;

	//Chekcing Conditions For in Range
	bool inXRange = ( mousePosX > static_cast<int>(x1*xFrac) ) && 
			( mousePosX < static_cast<int>(x2*xFrac) ); 

	bool inYRange = ( mousePosY > static_cast<int>(y1*yFrac) ) && 
			( mousePosY < static_cast<int>(y2*yFrac) ); 

	return(inXRange && inYRange);
}

//Renders The Given Button
void Button::renderButton()
{
	buttonText->resetColorOfText();

	SDL_Color newColor = {0,0,255};

	if(trackMouse())
		buttonText->changeColorOfText(newColor);
	
	buttonText->renderText();
}