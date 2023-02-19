#include <SDL.h>

#ifndef PLAYER_H
#define PLAYER_H

namespace Player {
    extern SDL_Rect player;
    extern float velocityX, velocityY;
    extern float speed;
    void drawPlayer(SDL_Window *window, SDL_Renderer *renderer, int x, int y);
}

#endif
