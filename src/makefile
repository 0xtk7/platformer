CC = g++
CFLAGS = -std=c++11

LIB = -LSDL2/lib -LSDL_image/lib
INCLUDE = -I./SDL2/include/SDL2 -I./SDL_image/include/SDL2

all: 
	$(CC) $(CFLAGS) *.cpp $(LIB) $(INCLUDE) -o platformer -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
