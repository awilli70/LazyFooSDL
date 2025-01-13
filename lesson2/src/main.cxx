#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <iostream>
#include <print>
#include <cstdlib>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Stinky Globals >:(
namespace {
// Rendering Window
SDL_Window *gWindow = nullptr;
// Surface contained by the Window
SDL_Surface *gScreenSurface = nullptr;
// Image to be rendered
SDL_Surface *gHelloWorld = nullptr;
}

bool init();
bool loadMedia();
void close();

int main (int argc, char *argv[]) {
    if (!init()) {
        return EXIT_FAILURE;
    }
    if (!loadMedia()) {
        close();
        return EXIT_FAILURE;
    }


    // Keep the window up
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        // Event Handler
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        // Apply the image and update
        SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
        SDL_UpdateWindowSurface(gWindow);
    }

    close();
    return EXIT_SUCCESS;
}

// Initialize SDL, Create the window, and grab the window surface
bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        println(std::cerr, "SDL could not initialize! SDL_Error: {}", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("Lesson 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        println(std::cerr, "Window could not be created! SDL_Error: {}", SDL_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

// Grab RGB bitmap and load it into the helloworld surface
bool loadMedia()
{
    auto fname = "resources/rgb.bmp";
    gHelloWorld = SDL_LoadBMP(fname);
    if (gHelloWorld == nullptr) {
        println(std::cerr, "Unable to load image {}! SDL_Error: {}", fname, SDL_GetError());
        return false;
    }
    return true;
}

// Cleanup allocated memory
void close()
{
    // Deallocate surface
    if (gHelloWorld != nullptr) {
        SDL_FreeSurface(gHelloWorld);
        gHelloWorld = nullptr;
    }

    // Destroy Window
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
