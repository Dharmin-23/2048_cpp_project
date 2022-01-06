#include "GameAI.hpp"

//Initalizing All Parameters
Game_AI::Game_AI()
{
	score = 0;
	plus =0;
	win = 2048;
	max = 0;
	response = 0;
	apocalypse = 1;
}

//Generates A Random Number
int Game_AI::random_index(int x)
{
   	int  index=rand()%x+0;
	return index;
}

//Finds The Greatest Tile 
void Game_AI::find_greatest_tile(vector<vector<int>>& grid)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(grid[i][j]>max)
				max=grid[i][j];
		}
	}	
}

//Copies The Given Grid To The BackUp Grid
void Game_AI::backup_grid(vector<vector<int>>& bgrid ,vector<vector<int>>& grid)
{
	for(int i=0;i<4;i++)
	{
			for(int j=0;j<4;j++)
			{
				bgrid[i][j]=grid[i][j];
			}
	}
}

//Genrates Two Fresh Blocks With Value 2
void Game_AI::start_grid(vector<vector<int>>& grid)
{
	int i = random_index(4);
	int j = random_index(4);

		grid[i][j]=2;

	int a = random_index(4);
	int b = random_index(4);

		grid[i][j]=2;
}

//Checks Whether The Merge Permissible
int Game_AI::block_moves(vector<vector<int>>& bgrid,vector<vector<int>>& grid)
{
	int k=0;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(bgrid[i][j]!=grid[i][j])
			{	
				k=1;
				break;
			}
		}
	}

	return k;
}

//Checks Whether There Are Anymore Moves Possible
int Game_AI::full(vector<vector<int>>& grid)
{
	int k=1;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(!grid[i][j])
				k=0;
				
		}
	}
	
	return k;
}

//Undos The previous Move
void Game_AI::undo(vector<vector<int>>& bgrid,vector<vector<int>>& grid)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			grid[i][j]=bgrid[i][j];
		}
	}
}

//Spawns Random Block
void Game_AI::spawn(vector<vector<int>>& grid)
{		

	int i,j,k;

	do
	{
		i=random_index(4);
		j=random_index(4);
		k=random_index(10);

	}while(grid[i][j]);
						
	if(k<2)
		grid[i][j]=4;

	else
		grid[i][j]=2;
	

}

//Strafes The Grid According to key pressed
void Game_AI::fill_space(vector<vector<int>>& grid,char control)
{
	
	switch(control)
	{
		case 'w':
			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++)
				{
					if(!grid[j][i])
					{
						for(int k=j+1;k<4;k++)
							if(grid[k][i])
								{
									grid[j][i]=grid[k][i];
									grid[k][i]=0;
									break;
								}
					}
				}
				
			break;

		case 's':
			for(int i=0;i<4;i++)
				for(int j=3;j>=0;j--)
				{
					if(!grid[j][i])
					{
						for(int k=j-1;k>=0;k--)
							if(grid[k][i])
								{
									grid[j][i]=grid[k][i];
									grid[k][i]=0;
									break;
								}
					}
				}
			break;

		case 'a':
			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++)
				{
					if(!grid[i][j])
					{
						for(int k=j+1;k<4;k++)
							if(grid[i][k])
							{
								grid[i][j]=grid[i][k];
								grid[i][k]=0;
								break;
							}
					}
				}
			break;


		case 'd':
			for(int i=0;i<4;i++)
				for(int j=3;j>=0;j--)
				{
					if(!grid[i][j])
					{
						for(int k=j-1;k>=0;k--)
							if(grid[i][k])
							{
								grid[i][j]=grid[i][k];
								grid[i][k]=0;
								break;
							}
					}
				}
			break; 
	}
}

//Merges The Required Block
void Game_AI::update_grid(vector<vector<int>>& grid,char control)
{
	plus=0;
	apocalypse=1;

	switch(control)
	{
		case 'w':
			for(int i=0;i<4;i++)
				for(int j=0;j<3;j++)
				{
					if(grid[j][i]&&grid[j][i]==grid[j+1][i])
					{
						apocalypse=0;
						grid[j][i]+=grid[j+1][i];
						grid[j+1][i]=0;
						plus+=(((log2(grid[j][i]))-1)*grid[j][i]);
						score+=(((log2(grid[j][i]))-1)*grid[j][i]);
								
					}
				}
			
			break;

		case 's':
			for(int i=0;i<4;i++)
				for(int j=3;j>0;j--)
				{
					if(grid[j][i]&&grid[j][i]==grid[j-1][i])
					{
						apocalypse=0;
						grid[j][i]+=grid[j-1][i];
						grid[j-1][i]=0;
						plus+=(((log2(grid[j][i]))-1)*grid[j][i]);
                            		}
				}
			
			break;

		case 'a':	
			for(int i=0;i<4;i++)
				for(int j=0;j<3;j++)
				{
					if(grid[i][j]&&grid[i][j]==grid[i][j+1])
					{
						apocalypse=0;
						grid[i][j]+=grid[i][j+1];
						grid[i][j+1]=0;
						plus+=((log2(grid[i][j]))-1)*grid[i][j];
						score+=((log2(grid[i][j]))-1)*grid[i][j];
					}
				}

			break;
						

		case 'd':
			for(int i=0;i<4;i++)
				for(int j=3;j>0;j--)
				{
					if(grid[i][j]&&grid[i][j]==grid[i][j-1])
					{
						apocalypse=0;
						grid[i][j]+=grid[i][j-1];
						grid[i][j-1]=0;
						plus+=((log2(grid[i][j]))-1)*grid[i][j];
						score+=(((log2(grid[i][j]))-1)*grid[i][j]);
					}
				}
			
			break;
	}
}

void Game_AI::logic_flow(vector<vector<int>>& bgrid,vector<vector<int>>& grid,char control)
{
	switch(control)
  	{
      		case 'w':
      		case 'a':
      		case 's':
      		case 'd':
		  	backup_grid(bgrid,grid);
		  	fill_space(grid,control);
		  	update_grid(grid,control);
		  	fill_space(grid,control);
		  	find_greatest_tile(grid);

		  	//execute->display_grid();
		  	usleep(1000*160);

		  	if(full(grid)&&apocalypse)
		  	{
		      		response=-1;
		      		break;
		  	}

		  	else if(block_moves(bgrid,grid))
		  	{
		      		spawn(grid);
		      		break;
		  	}

		  	else
		  	{
		      		response=0;	
		      		break;
		  	}

		case 'u':	
			if(block_moves(bgrid,grid))
				score-=plus;
			undo(bgrid,grid);
			break;
		
		case 'r': 	
			start_grid(grid);
			score=0;
			plus=0;
			break;
  	}
}

//Saves The content of Game AI
void Game_AI::saveGameAI(fstream& fout)
{
	fout << response << endl;
	fout << apocalypse << endl;
	fout << max << endl;
	fout << win << endl;
	fout << plus << endl;
	fout << score << endl;
}

//Overloaded CTOR

Game_AI::Game_AI(fstream& fout)
{
	fout >> response;
	fout >> apocalypse;
	fout >> max;
	fout >> win;
	fout >> plus;
	fout >> score;
}

//Gives The Score To be Displayed
int Game_AI::getScore()
{
	return score;
}