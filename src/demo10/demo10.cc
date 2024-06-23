#include <string>
extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
}
#include "texture.h"

bool init();
bool loadMedia();
void close();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window * gWindow = nullptr;
SDL_Renderer * gRenderer = nullptr;
demo10::Texture gFooTexture;
demo10::Texture gBackgroundTexture;

int main(int argc, char * argv[]) {
    if (!init()) {
        close();
        return 1;
    }

    if (!loadMedia()) {
        close();
        return 1;
    }

    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear renderer
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gBackgroundTexture.render(gRenderer, 0, 0);
        gFooTexture.render(gRenderer, 230, 150);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    close();
    return 0;
}

bool init() {
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
            "Failed to initialize SDL. SDL_Error: %s.", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Demo10", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create window. SDL_Error: %s.", SDL_GetError());
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create renderer. SDL_Error: %s.", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to initialized SDL_image. SDL_Error: %s.", IMG_GetError());
        return false;
    }

    return true;
}

bool loadMedia() {
    if (!gFooTexture.loadFromFile(gRenderer, "resources/foo.png")) {
        return false;
    }
    if (!gBackgroundTexture.loadFromFile(gRenderer, "resources/background.png")) {
        return false;
    }
    return true;
}

void close() {
    gFooTexture.free();
    gBackgroundTexture.free();

    if (gRenderer) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = nullptr;
    }
    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }

    IMG_Quit();
    SDL_Quit();
}