//Includes
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
using namespace std;

class Image
{
	protected:
	/*Data Members*/
		float windowWidth;
		float windowHeight;
		SDL_Renderer* windowRender;
		SDL_Texture* imageTexture;
		SDL_Rect imageRect;

	public :
	/*CTOR & DTOR*/
		Image(SDL_Renderer* renderer,string fileName,SDL_Rect displayRect);
		~Image();
	
	/*GUI Related*/
		virtual void renderImage();
		void changeImageRect(SDL_Rect displayRect);
};
