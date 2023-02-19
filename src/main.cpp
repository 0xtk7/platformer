#include <iostream>
#include <SDL.h>
#include <cmath>
#include "player.h"

// Window properties
#define WIDTH 800
#define HEIGHT 600
#define WINDOW_TITLE "gameplay"

#define gravity 0.1f
#define friction 0.96f

// Create window
SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

// Create renderer
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

// Player position
int playerX = WIDTH / 2; 
int playerY = HEIGHT / 2;

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
    // Clear terminal  
    std::system("cls");

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Event event;

    // Return error if window creation was unsucessful
    if (NULL == window) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // State of keys
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

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
                    
                    // Check if movement keys have been pressed
                    if (event.key.keysym.sym == SDLK_a) {
                        Player::velocityX = -Player::speed;

                    } else if (event.key.keysym.sym == SDLK_d) {
                        Player::velocityX = Player::speed;

                    } else if (event.key.keysym.sym == SDLK_SPACE) {

                        // Check if player is on ground
                        bool onGround = (playerY + Player::player.h >= HEIGHT);

                    
                        if (onGround) {

                            // Jump left
                            if (keyboardState[SDL_SCANCODE_A] && keyboardState[SDL_SCANCODE_SPACE]) {
                           
                                Player::velocityY = 0.0f; 

                                Player::velocityY += Player::jumpForce;
                                Player::velocityX -= Player::speed;
                            } 
                            
                            // Jump right
                            else if (keyboardState[SDL_SCANCODE_D] && keyboardState[SDL_SCANCODE_SPACE]) {
                                
                                Player::velocityY = 0.0f; 

                                Player::velocityY += Player::jumpForce;
                                Player::velocityX += Player::speed;
                            }

                            // Jump straight up 
                            else {
                                
                                Player::velocityX = 0.0f;
                                Player::velocityY = 0.0f; 

                                Player::velocityY += Player::jumpForce;
                            }
                        }
                    }
                break;
            }
        }

        // Display player coordinates
        printf("X: %d | Y: %d\n", playerX, playerY);

        // Update player velocity
        playerX += (int)Player::velocityX;

        // Gravity
        Player::velocityY += gravity;
        playerY += (int)Player::velocityY;

        // Friction
        Player::velocityX *= friction;
        Player::velocityY *= friction;

        // Cap max velocity
        if (Player::velocityX > Player::maxSpeed) Player::velocityX = Player::maxSpeed;
        if (Player::velocityX < -Player::maxSpeed) Player::velocityX = -Player::maxSpeed;
        if (Player::velocityY > Player::maxSpeed) Player::velocityY = Player::maxSpeed;
        if (Player::velocityY < -Player::maxSpeed) Player::velocityY = -Player::maxSpeed;

        checkCollision();
        update();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}