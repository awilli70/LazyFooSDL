#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_video.h>
#include <iostream>
#include <print>
#include <cstdlib>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main (int argc, char *argv[]) {
    SDL_Window *window = nullptr;
    SDL_Surface *screenSurface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        println(std::cerr, "SDL could not initialize! SDL_Error: {}", SDL_GetError());
    }

    window = SDL_CreateWindow("TicTacToe",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        println(std::cerr, "Window could not be created! SDL_Error: {}", SDL_GetError());
    }

    // Make the Screen White
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);

    // Keep the window up
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
