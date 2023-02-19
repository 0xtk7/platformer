#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "player.h"

// Window properties
#define WIDTH 800
#define HEIGHT 600
#define WINDOW_TITLE "gameplay"

// Create window
SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

// Create renderer
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

// Player position
int playerX, playerY = 10;

void update() {
    // Draw player
    Player::drawPlayer(window, renderer, playerX, playerY);

    SDL_RenderClear(renderer);
}

void checkCollision() {
    // Check if player collides with window border
    if (playerX <= 0) {
        playerX = 0;
        Player::velocityX = 0;
    } else if (playerX + Player::player.w >= WIDTH) {
        playerX = WIDTH - Player::player.w;
        Player::velocityX = 0;
    }
    if (playerY <= 0) {
        playerY = 0;
        Player::velocityY = 0;
    } else if (playerY + Player::player.h >= HEIGHT) {
        playerY = HEIGHT - Player::player.h;
        Player::velocityY = 0;
    }
}

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Event event;

    // Return error if window creation was unsucessful
    if (NULL == window) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // Main window loop
    bool running = true;
    while (running) {

        // Check events
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                // Exit on close
                case SDL_QUIT:
                    running = false;    
                break;

                // Keyboard movement
                case SDL_KEYDOWN:
                    std::cout << playerX << std::endl;
                    
                    // Check if a has been pressed
                    if (event.key.keysym.sym == SDLK_a) {
                        playerX -= Player::speed;
                    } else if (event.key.keysym.sym == SDLK_d) {
                        playerX += Player::speed;
                    }
                break;
            }
        }

        printf("X: %d | Y: %d\n", playerX, playerY);

        // Update player velocity
        playerX += (int)Player::velocityX;
        playerY += (int)Player::velocityY;

        checkCollision();
        update();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}