#include <SDL.h>
#include <SDL_image.h>

#include "player.h"

namespace Player {

    // Player properties
    SDL_Rect player;
    SDL_Texture *playerTexture;
    float velocityX, velocityY = 0.0f;
    float speed = 3.0f;
    float maxSpeed = 5.0f;
    const float jumpForce = -100.0f;
    
    // Draw player hitbox
    void drawPlayer(SDL_Window *window, SDL_Renderer *renderer, int x, int y, int w, int h, const char* sprite) {
        
        SDL_Surface *playerSurface = IMG_Load(sprite);
        playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);

        SDL_FreeSurface(playerSurface);

        // Player dimensions
        player.x = x;
        player.y = y;
        player.w = w;
        player.h = h;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &player);
    }
}
