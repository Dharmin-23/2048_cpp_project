#include "Window.hpp"

//Creates A WIndow Postioned At The Centre of Screen
Window::Window(string nameOfWindow,int widthOfWindow,int heightOfWindow,int windowPosX,int windowPosY)
{
	window = SDL_CreateWindow( nameOfWindow.c_str(),
				   windowPosX,windowPosY,
				   widthOfWindow,heightOfWindow,
				   SDL_SWSURFACE|
				   SDL_WINDOW_RESIZABLE|SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);

	windowRender = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	defaultWidth = widthOfWindow;
	defaultHeight = heightOfWindow;
}

//Closes The Given Window
Window::~Window()
{
	for(Image* image : windowImageList)
	{
		delete image;
		image = NULL;
	}

	for(Text* text : windowTextList)
	{
		delete text;
		text = NULL;
	}
	
	SDL_DestroyRenderer(windowRender);
	SDL_DestroyWindow(window);

	windowRender = NULL;
	window = NULL;
}

//Adds Image To List of Images to Be dispalyed
void Window::addPictureToDisplay(string fileName,int posX,int posY,int sizeX,int sizeY)
{
	SDL_Rect imageRect = {posX,posY,sizeX,sizeY};
	Image* newImage = new Image(windowRender,fileName,imageRect);
	windowImageList.push_back(newImage);
}

//Loads All Images for displaying
void Window::loadImagesToDisplay()
{
	for(Image* image:windowImageList)
		image->renderImage();
}

//Sets The Give Image As The Icon of The Window
void Window::setIconofWindow(string fileName)
{
	SDL_Surface* iconSurface = IMG_Load(fileName.c_str());
	SDL_SetWindowIcon(window,iconSurface);
}

//Adds Text To List of Text to Be dispalyed
void Window::addTextToDisplay(string text,SDL_Color textColor,int posX,int posY,int sizeX,int sizeY)
{
	SDL_Rect textRect = {posX,posY,sizeX,sizeY};
	Text* newText = new Text(windowRender,text,textColor,textRect);
	windowTextList.push_back(newText);
}

//Loads All Text for displaying
void Window::loadTextToDisplay()
{
	for(Text* text:windowTextList)
		text->renderText();
}

//Gives the Dimensions of Window
void Window::getWindowDimensions(int* width,int* height)
{
	SDL_GetRendererOutputSize(windowRender,width,height);
}

//Gives the Position of Window on Screen
void Window::getWindowPosition(int* positionX,int* positionY)
{
	SDL_GetWindowPosition(window,positionX,positionY);
}
