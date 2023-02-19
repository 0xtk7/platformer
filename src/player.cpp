// Player properties
#include <SDL.h>
#include "player.h"

namespace Player {
    SDL_Rect player;
    float velocityX, velocityY = 0.0f;
    float speed = 3.0f;
    float maxSpeed = 5.0f;
    const float jumpForce = -100.0f;
    
    // Draw player
    void drawPlayer(SDL_Window *window, SDL_Renderer *renderer, int x, int y) {
        
        SDL_RenderClear(renderer);

        player.x = x;
        player.y = y;
        player.w = 50;
        player.h = 100;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &player);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);

    }
}