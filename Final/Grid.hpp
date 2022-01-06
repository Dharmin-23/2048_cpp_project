//Includes
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

#include "GameAI.hpp"
#include "Image.hpp"
#include "Text.hpp"
using namespace std;

class Grid
{
	private :
	/*Data Members*/
		int gridFactor;
		int gridSize;
		char gridColor[4];
		SDL_Renderer* screenRender;
		vector<SDL_Rect> gridRect;
		vector<vector<int>> gridValue;
		vector<vector<int>> backValue;
		vector<SDL_Texture*> blockTexture;
		Game_AI* logic;


	/*GUI Related*/
		void makeTile(SDL_Rect tile);
		
	public :
	/*CTOR & DTOR*/
		Grid(SDL_Renderer* renderer,char colorScheme[],int factor,int size);
		Grid(SDL_Renderer* renderer,char colorScheme[],int factor,fstream& fout);
		~Grid();
	
	/*GUI Related*/
		void buildGridFrame();
		void displayGirdValues();
		int getScore();

	/*Grid Upates*/
		void startGrid();
		void updateBoard(char control);
		void saveGrid();
		bool gameOver();
		

};
