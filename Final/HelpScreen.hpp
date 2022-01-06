#include "Window.hpp"

class HelpScreen : public Window
{
	public:
	/*CTOR*/
		HelpScreen(string gameName,int startWidth,int startHeight,int windowPosX,int windowPosY);

	/*GUI Related*/
		int eventGameLoop(int fps);
};