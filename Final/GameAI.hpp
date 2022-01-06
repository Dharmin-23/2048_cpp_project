//Includes
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <cmath>
#include <random>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#include<unistd.h>

using namespace std;


class Game_AI
{
	private:
	/*Data Memebers*/
		int response;
  		int apocalypse;
		int max;
  		int win;
  		int plus;
  		int score;
  
	public:
	/*CTOR*/
  		Game_AI();
		Game_AI(fstream& fout);

	/*Grid Updates*/
		void start_grid(vector<vector<int>>&); //
  		void logic_flow(vector<vector<int>>&,vector<vector<int>>&,char);
  		void update_grid(vector<vector<int>>&,char);//
  		void fill_space(vector<vector<int>>&,char);//
  		void spawn(vector<vector<int>>&); //
  		void undo(vector<vector<int>>&,vector<vector<int>>&);//
		int getScore();

	/*Utility*/
		int random_index(int); //
		void find_greatest_tile(vector<vector<int>>&); //
		void backup_grid(vector<vector<int>>&,vector<vector<int>>&); //
		int block_moves(vector<vector<int>>& ,vector<vector<int>>& ); //
		int full(vector<vector<int>>&); //
		void saveGameAI(fstream& fout);
};
