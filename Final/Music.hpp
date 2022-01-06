#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <time.h>
#include <iostream>

#include <SDL2/SDL_mixer.h>
using namespace std;

class Music
{
public:

	Music();
	~Music();
	void playmusic(const char*);
	void playchannel(int, const char*, int);
};
