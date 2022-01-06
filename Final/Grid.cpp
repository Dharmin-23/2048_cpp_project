#include "Grid.hpp"

//Constructs The 2x2 Grid With Provided Specifications
Grid::Grid(SDL_Renderer* renderer,char colorScheme[],int factor,int size)
{
	for(int i=0;i<4;i++)
		gridColor[i] = colorScheme[i];
	
	gridSize = size;
	gridFactor = factor;
	screenRender = renderer;

	//Loading Textures
	blockTexture.push_back(NULL);

	for(int i=2;i<=4096;i*=2)
	{
		SDL_Rect rect = {0,0,0,0};
		string fileName = "./GUI/"+ to_string(i) + "_.bmp"; 
		blockTexture.push_back(IMG_LoadTexture(screenRender,fileName.c_str()));
	}

	//Initializing Board
	for(int i=0;i<gridSize;i++)
	{
		vector<int> temp(gridSize);
		
		gridValue.push_back(temp);
		backValue.push_back(temp);
	}

	//Initializing Logic
	logic =  new Game_AI();
}


//CTOR The Cached Grid
Grid::Grid(SDL_Renderer* renderer,char colorScheme[],int factor,fstream& fout)
{
	for(int i=0;i<4;i++)
		gridColor[i] = colorScheme[i];
	
	gridFactor = factor;
	screenRender = renderer;

	//Loading Textures
	blockTexture.push_back(NULL);

	for(int i=2;i<=4096;i*=2)
	{
		SDL_Rect rect = {0,0,0,0};
		string fileName = "./GUI/"+ to_string(i) + "_.bmp"; 
		blockTexture.push_back(IMG_LoadTexture(screenRender,fileName.c_str()));
	}

	//Making the board
	fout >> gridSize;

	for(int i=0;i<gridSize;i++)
	{
		vector<int> row(gridSize);

		backValue.push_back(row);
		gridValue.push_back(row);

		for(int j=0;j<gridSize;j++)
		{
			fout >> gridValue[i][j];
		}
	}

	//Loading Game AI
	logic = new Game_AI(fout);
}

//Destroys The Given Grid
Grid::~Grid()
{
	screenRender = NULL;
}

//Builds Grid Frame
void Grid::buildGridFrame()
{
	//Clearing The Old Grid
	gridRect.clear();

	//Starting Off Fresh
	int windowWidth,windowHeight;

	//Finding Window width & height
	SDL_GetRendererOutputSize(screenRender,&windowWidth,&windowHeight);

	//Finding Other Parameters Using it
	int blockSize = windowHeight/gridFactor;
	int maxTiles = gridSize/2,gridPosX,gridPosY;
	int gridOriginX = windowWidth/2;
	int gridOriginY = windowHeight/2;

	//Building The Grid Frame
	for(int row = -maxTiles+1;row < maxTiles+1;row += 1)
	{
		gridPosY = gridOriginY - (row*blockSize);

		for(int col=-maxTiles;col < maxTiles;col += 1)
		{
			gridPosX = gridOriginX + (col*blockSize);
			
			SDL_Rect newTile = {gridPosX,gridPosY,
					    blockSize,blockSize};

			gridRect.push_back(newTile);
			
			makeTile(newTile);
		}
	}
}

//Draws a Single Tile of a Grid
void Grid::makeTile(SDL_Rect tile)
{
        SDL_SetRenderDrawColor(screenRender,
				   gridColor[0],gridColor[1],
					gridColor[2],gridColor[3]);

        SDL_RenderDrawRect( screenRender, &tile );
}

//Displays The Value of The Grid
void Grid::displayGirdValues()
{
	//Iterating Over The Grid Values
	for(int i=0;i<gridSize;i++)
	{
		for(int j=0;j<gridSize;j++)
		{
			int value = gridValue[i][j];
			if(value == 0) continue;	
			
			//Finding The Texture
			int index = log2(value);
			SDL_Texture* block = blockTexture[index];

			//Loading Images For Non-Zero Values
			if(block != NULL)
				SDL_RenderCopy(screenRender,block,NULL,&gridRect[(4*i)+j]);
		}
	}
}

//Updates The Grid
void Grid::updateBoard(char control)
{
	logic->logic_flow(backValue,gridValue,control);
}

//Intializes Board
void Grid::startGrid()
{
	logic->start_grid(gridValue);
}

//Saves The Grid in "./GUI/gameCache.txt"
void Grid::saveGrid()
{
	fstream fout;

	//Opening The File With Erased Contents
	fout.open("./GUI/gameCache.txt",ios::out | ios::trunc);

	//Saving Contents
	fout << gridSize << endl;

	//Grid Contents
	for(int i=0;i<gridSize;i++)
	{
		for(int j=0;j<gridSize;j++)
		{
			fout << gridValue[i][j] << " ";
		}

		fout << endl;
	}

	//Saving Game AI Contents
	logic->saveGameAI(fout);

	fout.close();
}


//Displays Score 
int Grid::getScore()
{
	return logic->getScore();	
}

//Checks The Game Over Condition
bool Grid::gameOver()
{
	if(!logic->full(gridValue))
		return false;

	for(int i=0;i<gridSize;i++)
	{
		for(int j=0;j<gridSize-1;j++)
		{
			if(gridValue[i][j] == gridValue[i][j+1])
				return false;
			
			if(gridValue[j][i] == gridValue[j+1][i])
				return false;
		}
	}

	return true;
}