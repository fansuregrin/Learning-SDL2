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
SDL_Window * gWindow = nullptr;
SDL_Renderer * gRenderer = nullptr;
demo12::Texture gModulatedTexture;

int main(int argc, char * argv[]) {
    if (!init("SDL Demo12")) {
        close();
        return 1;
    }

    if (!loadMedia()) {
        close();
        return 1;
    }

    SDL_Event e;
    Uint8 r = 255, g = 255, b = 255;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Press down key %s.",
                    SDL_GetKeyName(e.key.keysym.sym));
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                    r += 32;
                    break;

                    case SDLK_w:
                    g += 32;
                    break;

                    case SDLK_e:
                    b += 32;
                    break;

                    case SDLK_a:
                    r -= 32;
                    break;

                    case SDLK_s:
                    g -= 32;
                    break;

                    case SDLK_d:
                    b -= 32;
                    break;
                }
            }
        }

        // Clear renderer
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        // Modulate and render texture
        gModulatedTexture.setColor(r, g, b);
        gModulatedTexture.render(gRenderer, 0, 0);

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
            "Failed to initialize SDL. SDL_Error: %s.", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
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
            "Failed to initialized SDL_image. SDL_Error: %s.", SDL_GetError());
        return false;
    }

    return true;
}

bool loadMedia() {
    if (!gModulatedTexture.loadFromFile(gRenderer, "resources/demo12.png")) {
        return false;
    }
    return true;
}

void close() {
    gModulatedTexture.free();

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