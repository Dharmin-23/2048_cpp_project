#include "Image.hpp"

//Making An SDL Image
Image::Image(SDL_Renderer* renderer,string fileName,SDL_Rect displayRect)
{
	windowRender = renderer;
	imageTexture = IMG_LoadTexture(windowRender,fileName.c_str());
	imageRect = displayRect;

	int width,height;
	SDL_GetRendererOutputSize(windowRender,&width,&height);
	windowWidth = width;
	windowHeight = height;
}

//Removes the Image
Image::~Image()
{
	SDL_DestroyTexture(imageTexture);
	imageTexture = NULL;
	windowRender = NULL;
}

//Renders The Given Image
void Image::renderImage()
{
	//Finding window Dimensions
	int width,height;
	SDL_GetRendererOutputSize(windowRender,&width,&height);
	
	//Scaling Down - In Case of Re size
	float xFrac = (width/(windowWidth));
	float yFrac = (height/(windowHeight));

	SDL_Rect newRect = {static_cast<int>((imageRect.x)*xFrac),
			    static_cast<int>((imageRect.y)*yFrac), 
			    static_cast<int>((imageRect.w)*xFrac),
			    static_cast<int>((imageRect.h)*yFrac)};

	SDL_RenderCopy(windowRender,imageTexture,NULL,&newRect);
}

//Changes The Image Rect
void Image::changeImageRect(SDL_Rect displayRect)
{
	imageRect = displayRect;
}
