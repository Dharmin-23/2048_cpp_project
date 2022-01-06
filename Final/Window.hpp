//Includes
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>

#include "Image.hpp"
#include "Text.hpp"
using namespace std;

class Window
{
	protected:
	/*Data Memebers*/
		string windowName;
		SDL_Window* window;
		SDL_Renderer* windowRender;
		vector<Image*> windowImageList;
		vector<Text*> windowTextList;
		float defaultWidth;
		float defaultHeight;

	public :
	/*CTOR & DTOR*/
		Window(string nameOfWindow,int widthOfWindow,int heightOfWindow,
							int windowPosX,int windowPosY);
		~Window();
	
	/*GUI Related*/
		void addPictureToDisplay(string fileName,int posX,int posY,int sizeX,int sizeY);
		void loadImagesToDisplay();
		void setIconofWindow(string fileName);
		void addTextToDisplay(string text,SDL_Color textColor,int posX,int posY,int sizeX,int sizeY);
		void loadTextToDisplay();

	/*Window Getter Methods*/
		void getWindowDimensions(int* width,int* height);
		void getWindowPosition(int* positionX,int* positionY);
		
	/*Implemented By SubClasses*/
		virtual int eventGameLoop(int fps) = 0;
};