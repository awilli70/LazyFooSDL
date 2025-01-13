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

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_NONE,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_MAX
};


// Stinky Globals >:(
namespace {
// Rendering Window
SDL_Window *gWindow = nullptr;
// Surface contained by the Window
SDL_Surface *gScreenSurface = nullptr;
// Image to be rendered
SDL_Surface *gCurrSurface = nullptr;
// Available Surfaces
SDL_Surface *gKeySurfaces[KEY_PRESS_SURFACE_MAX] = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};
// Enum2Str
std::string dir_to_string[KEY_PRESS_SURFACE_MAX] = {
    "None",
    "Up",
    "Down",
    "Left",
    "Right",
};
}

bool init();
bool loadMedia();
void close();
SDL_Surface *loadSurface(std::string);
void keyPressHandler(SDL_Event &e);

int main (int argc, char *argv[]) {
    if (!init()) {
        return EXIT_FAILURE;
    }
    if (!loadMedia()) {
        close();
        return EXIT_FAILURE;
    }



    // Loop flag
    bool quit = false;

    gCurrSurface = gKeySurfaces[KEY_PRESS_SURFACE_NONE];

    SDL_Event e;
    while (!quit) {
        // Event Handler
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    keyPressHandler(e);
                default:
                    break;
            }
        }

        // Apply the image and update
        SDL_BlitSurface(gCurrSurface, nullptr, gScreenSurface, nullptr);
        SDL_UpdateWindowSurface(gWindow);
    }

    close();
    return EXIT_SUCCESS;
}

void keyPressHandler(SDL_Event &e) {
    switch (e.key.keysym.sym) {
        case SDLK_UP:
            gCurrSurface = gKeySurfaces[KEY_PRESS_SURFACE_UP];
            break;
        case SDLK_DOWN:
            gCurrSurface = gKeySurfaces[KEY_PRESS_SURFACE_DOWN];
            break;
        case SDLK_LEFT:
            gCurrSurface = gKeySurfaces[KEY_PRESS_SURFACE_LEFT];
            break;
        case SDLK_RIGHT:
            gCurrSurface = gKeySurfaces[KEY_PRESS_SURFACE_RIGHT];
            break;
        default:
            gCurrSurface = gKeySurfaces[KEY_PRESS_SURFACE_NONE];
            break;
    }
    return;
}

// Initialize SDL, Create the window, and grab the window surface
bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        println(std::cerr, "SDL could not initialize! SDL_Error: {}", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("Lesson 4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        println(std::cerr, "Window could not be created! SDL_Error: {}", SDL_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

SDL_Surface *loadSurface(std::string path)
{
    SDL_Surface *s = SDL_LoadBMP(path.c_str());
    if (s == nullptr) {
        println(std::cerr, "Unable to load image {}! SDL_Error: {}", path, SDL_GetError());
    }
    return s;
}

// Grab RGB bitmap and load it into the helloworld surface
bool loadMedia()
{
    std::string fprefix = "resources/";
    std::string media_path_arr[KEY_PRESS_SURFACE_MAX] {
        [KEY_PRESS_SURFACE_NONE] = "base.bmp",
        [KEY_PRESS_SURFACE_UP] = "up.bmp",
        [KEY_PRESS_SURFACE_DOWN] = "down.bmp",
        [KEY_PRESS_SURFACE_LEFT] = "left.bmp",
        [KEY_PRESS_SURFACE_RIGHT] = "right.bmp",
    };

    for (auto i = 0; i < KEY_PRESS_SURFACE_MAX; i++) {
        gKeySurfaces[i] = loadSurface(fprefix + media_path_arr[i]);
        if (gKeySurfaces[i] == nullptr) {
            return false;
        }
    }

    return true;
}

// Cleanup allocated memory
void close()
{
    // Deallocate surface
    for (auto s : gKeySurfaces) {
        if (s != nullptr) {
            SDL_FreeSurface(s);
            s = nullptr;
        }
    }

    // Destroy Window
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
