#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

// Window properties
#define WIDTH 800
#define HEIGHT 600
#define WINDOW_TITLE "gameplay"

SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Texture *texture;

void renderImage(SDL_Window* window, const char* imgPath) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    surface = IMG_Load(imgPath); 
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
  
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create window
    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    // Return error if window creation was unsucessful
    if (NULL == window) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    // Main window loop
    while (1) {
        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                break;
            }
        }

        renderImage(window, "img/red.png");
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}