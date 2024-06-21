#include <cstdio>

extern "C" {
#include <SDL2/SDL.h>
}

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char * argv[]) {
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("SDL Demo1", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        fprintf(stderr, "Failed to create window. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));
    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}