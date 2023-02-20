#include <iostream>
#include <SDL.h>
#include <cmath>

#include "player.h"

// Window properties
#define WIDTH 800
#define HEIGHT 600
#define WINDOW_TITLE "gameplay"

#define gravity 0.4f
#define friction 0.6f

// Create window
SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

// Create renderer
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

// Player spawn position
int playerX = WIDTH / 3; 
int playerY = HEIGHT;

int playerW = 50;
int playerH = 100;

// Base sprite
const char *playerSprite = "img/red.png";

void update() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    Player::drawPlayer(window, renderer, playerX, playerY, playerW, playerH, playerSprite);
}

void checkCollision() {
    // Check if player collides with window border
    if (playerX <= 0) {
        playerX = 0;
        Player::velocityX = 0;
    } else if (playerX + playerW >= WIDTH) {
        playerX = WIDTH - playerW;
        Player::velocityX = 0;
    }
    if (playerY <= 0) {
        playerY = 0;
        Player::velocityY = 0;
    } else if (playerY + playerH >= HEIGHT) {
        playerY = HEIGHT - playerH;
        Player::velocityY = 0;
    }
}

void render() {
    // Set background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, Player::playerTexture, NULL, &Player::player);

    SDL_RenderPresent(renderer);
}

int main(int argc, char** argv) {
    
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Event event;

    // Return error if window creation was unsucessful
    if (NULL == window) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // State of keys
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    Uint64 startTime, frameTime, fps;


    // Main window loop
    bool running = true;
    while (running) {

        startTime = SDL_GetTicks();

        // Check if player is on ground
        bool onGround = (playerY + playerH >= HEIGHT);

        // Check events
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                // Exit on close
                case SDL_QUIT:
                    running = false;    
                break;

            }
        }

        // Check if movement keys have been pressed
        if (keyboardState[SDL_SCANCODE_A]) {

            Player::velocityX = -Player::speed;
        } else if (keyboardState[SDL_SCANCODE_D]) {

            Player::velocityX = Player::speed;
        } 

        // Jumping & crouching            
        if (onGround) {

            // Jump left
            if (keyboardState[SDL_SCANCODE_A] && keyboardState[SDL_SCANCODE_SPACE]) {

                Player::velocityY += Player::jumpForce;
                Player::velocityX = -Player::speed;

            } 
            
            // Jump right
            else if (keyboardState[SDL_SCANCODE_D] && keyboardState[SDL_SCANCODE_SPACE]) {
            
                Player::velocityY += Player::jumpForce;
                Player::velocityX = Player::speed;
            }

            // Jump straight up 
            else if (keyboardState[SDL_SCANCODE_SPACE]) {

                Player::velocityX = 0.0f;
                Player::velocityY = 0.0f; 

                Player::velocityY += Player::jumpForce;

            }

            // Crouching
            else if (keyboardState[SDL_SCANCODE_LCTRL]) {
                playerY = 550;
                // Half player speed & height
                Player::speed = 1.5f;
                playerH = 50; 
                playerSprite = "img/blue.png";
            }

            // Reset player height & speed after crouching
            else if (!keyboardState[SDL_SCANCODE_LCTRL]) {
                Player::speed = 3.0f;
                playerH = 100;   
                playerSprite = "img/red.png";                
            }
        }

        // Display player coordinates
        printf("X: %d | Y: %d | vX: %f | vY: %f | FPS: %d\n", playerX, playerY, Player::velocityX, Player::velocityY, fps);

        // Update player velocity
        playerX += (int)Player::velocityX;

        // Gravity
        Player::velocityY += (gravity + Player::weight);
        playerY += (int)Player::velocityY;

        // Friction
        Player::velocityX *= friction;
        Player::velocityY *= friction;
        
        // Cap max vertical velocity
        if (Player::velocityY > Player::speed) Player::velocityY = Player::speed;
        if (Player::velocityY < -Player::speed) Player::velocityY = -Player::speed;

        checkCollision();
        update();
        render();

        frameTime = SDL_GetTicks() - startTime;
        fps = (frameTime > 0) ? 1000.0f / frameTime : 0.0f;
        
        SDL_Delay(5);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}