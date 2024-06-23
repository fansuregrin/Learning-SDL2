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
demo13::Texture gModulatedTexture;
demo13::Texture gBackgroundTexture;

int main(int argc, char * argv[]) {
    if (!init("SDL Demo13")) {
        close();
        return 1;
    }

    if (!loadMedia()) {
        close();
        return 1;
    }

    SDL_Event e;
    Uint8 r = 255, g = 255, b = 255, a = 255;
    Uint8 alphaShift = 15, rgbShift = 25;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Press down key %s.",
                    SDL_GetKeyName(e.key.keysym.sym));
                switch (e.key.keysym.sym) {
                    // increase red color on 'q'
                    case SDLK_q:
                    r = (r + rgbShift > 255) ? 255 : r + rgbShift;
                    break;

                    // increase green color on 'w'
                    case SDLK_w:
                    g = (g + rgbShift > 255) ? 255 : g + rgbShift;
                    break;

                    // increase blue color on 'e'
                    case SDLK_e:
                    b = (b + rgbShift > 255) ? 255 : b + rgbShift;
                    break;

                    // decrease red color on 'a'
                    case SDLK_a:
                    r = (r - rgbShift < 0) ? 0 : r - rgbShift;
                    break;

                    // decrease green color on 's'
                    case SDLK_s:
                    g = (g - rgbShift < 0) ? 0 : g - rgbShift;
                    break;

                    // decrease blue color on 'd'
                    case SDLK_d:
                    b = (b - rgbShift < 0) ? 0 : b - rgbShift;
                    break;

                    // increase alpha on 'up'
                    case SDLK_UP:
                    a = (a + alphaShift > 255) ? 255 : a + alphaShift;
                    break;

                    // decrease alpha on 'down'
                    case SDLK_DOWN:
                    a = (a - alphaShift < 0) ? 0 : a - alphaShift;
                }
            }
        }

        // Clear renderer
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        // Render background
        gBackgroundTexture.render(gRenderer, 0, 0);
        // Modulate and render front texture
        gModulatedTexture.setColor(r, g, b);
        gModulatedTexture.setAlpha(a);
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
            "Failed to initialized SDL_image. SDL_image Error: %s.", IMG_GetError());
        return false;
    }

    return true;
}

bool loadMedia() {
    if (!gBackgroundTexture.loadFromFile(gRenderer, "resources/background.png")) {
        return false;
    }
    if (!gModulatedTexture.loadFromFile(gRenderer, "resources/demo13.png")) {
        return false;
    }

    gModulatedTexture.setBlend(SDL_BLENDMODE_BLEND);
    return true;
}

void close() {
    gModulatedTexture.free();
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