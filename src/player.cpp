// Player properties
#include <SDL.h>
#include <SDL_image.h>
#include "player.h"

namespace Player {
    SDL_Rect player;
    SDL_Texture *playerTexture;
    float velocityX, velocityY = 0.0f;
    float speed = 1.5f;
    float weight = 0.5f;
    const float jumpForce = -100.0f;
    int health, ammo;
    
    // Draw player
    void drawPlayer(SDL_Window *window, SDL_Renderer *renderer, int x, int y, int w, int h, const char* sprite) {
        
        SDL_Surface *playerSurface = IMG_Load(sprite);
        playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);

        SDL_FreeSurface(playerSurface);

        player.x = x;
        player.y = y;
        player.w = w;
        player.h = h;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &player);
    }
}