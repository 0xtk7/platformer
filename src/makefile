CC = g++
CFLAGS = -std=c++11 -Wall

SRC = main.cpp

LIB = -LSDL2/lib -LSDL_image/lib
INCLUDE = -ISDL2/include/SDL2 -ISDL_image/include/SDL2

all:
	$(CC) $(CFLAGS) $(SRC) $(LIB) $(INCLUDE) -o platformer -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
