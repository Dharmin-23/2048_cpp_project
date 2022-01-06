#OBJS specifies which files to compile as part of the project
#OBJS =  main.cpp Game.hpp Game.cpp TextureManager.hpp TextureManager.cpp GameObject.hpp GameObject.cpp
OBJS =  Main.cpp Grid.cpp Window.cpp Image.cpp Text.cpp Game.cpp LoadScreen.cpp Button.cpp GameScreen.cpp GameAI.cpp HelpScreen.cpp Music.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = exe

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
