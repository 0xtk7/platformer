#include <SDL.h>

#ifndef PLAYER_H
#define PLAYER_H

namespace Player {
    extern SDL_Rect player;
    extern SDL_Texture *playerTexture;
    extern float velocityX, velocityY, speed;
    extern int health, ammo;
    extern const float jumpForce;

    void drawPlayer(SDL_Window *window, SDL_Renderer *renderer, int x, int y, int w, int h, const char* sprite);
}

#endif
