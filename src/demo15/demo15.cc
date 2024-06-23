#include <string>
extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
}
#include "texture.h"

bool init(const std::string &title);
bool loadMedia();
void close();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int WALKING_FRAMES = 4;
SDL_Window * gWindow = nullptr;
SDL_Renderer * gRenderer = nullptr;
demo15::Texture gArrowTexture;


int main(int argc, char * argv[]) {
    if (!init("SDL Demo15")) {
        close();
        return 1;
    }

    if (!loadMedia()) {
        close();
        return 1;
    }

    SDL_Event e;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    double degrees = 0.0;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Press down key %s.",
                    SDL_GetKeyName(e.key.keysym.sym));
                switch (e.key.keysym.sym) {
                    case SDLK_a:
                    degrees -= 30;
                    break;

                    case SDLK_d:
                    degrees += 30;
                    break;

                    case SDLK_q:
                    flipType = SDL_FLIP_HORIZONTAL;
                    break;

                    case SDLK_w:
                    flipType = SDL_FLIP_NONE;
                    break;

                    case SDLK_e:
                    flipType = SDL_FLIP_VERTICAL;
                    break;
                }
            }
        }

        // Clear renderer
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gArrowTexture.render(gRenderer, (SCREEN_WIDTH-gArrowTexture.getWidth())/2,
            (SCREEN_HEIGHT-gArrowTexture.getHeight())/2, nullptr, degrees,
            nullptr, flipType);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    close();
    return 0;
}

bool init(const std::string &title) {
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
            "Failed to initialize SDL. SDL Error: %s.", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create window. SDL Error: %s.", SDL_GetError());
        return false;
    }

    // create a vsynced renderer for the window
    gRenderer = SDL_CreateRenderer(gWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create renderer. SDL Error: %s.", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to initialized SDL_image. SDL_image Error: %s.", IMG_GetError());
        return false;
    }

    return true;
}

bool loadMedia() {
    if (!gArrowTexture.loadFromFile(gRenderer, "resources/arrow.png")) {
        return false;
    }

    return true;
}

void close() {
    gArrowTexture.free();

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