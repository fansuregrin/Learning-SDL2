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
TTF_Font * gFont = nullptr;
demo16::Texture gTextTexture;


int main(int argc, char * argv[]) {
    if (!init("SDL Demo16")) {
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
            } else if (e.type == SDL_KEYDOWN) {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Press down key %s.",
                    SDL_GetKeyName(e.key.keysym.sym));
                switch (e.key.keysym.sym) {

                }
            }
        }

        // Clear renderer
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gTextTexture.render(gRenderer,
            (SCREEN_WIDTH - gTextTexture.getWidth()) / 2,
            (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);

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
            "Failed to create window. SDL_Error: %s.", SDL_GetError());
        return false;
    }

    // create a vsynced renderer for the window
    gRenderer = SDL_CreateRenderer(gWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create renderer. SDL_Error: %s.", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    // initialize PNG loading
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to initialized SDL_image. SDL_image Error: %s.", IMG_GetError());
        return false;
    }

    // initialize SDL_TTF
    if (TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to initialized SDL_ttf. SDL_ttf Error: %s.", TTF_GetError());
        return false;
    }

    return true;
}

bool loadMedia() {
    gFont = TTF_OpenFont("../../assets/fonts/LXGWWenKaiLite-Regular.ttf", 16);
    if (gFont == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to load lxgw-wenkai-lite font. SDL_ttf Error: %s.",
            TTF_GetError());
        return false;
    }

    SDL_Color color = {0, 0, 0};
    if (!gTextTexture.loadFromRenderedText(gRenderer, gFont,
    "The quick brown fox jumps over the lazy dog\n你好，世界！", color)) {
        return false;
    }

    return true;
}

void close() {
    gTextTexture.free();

    if (gFont) {
        TTF_CloseFont(gFont);
        gFont = nullptr;
    }
    if (gRenderer) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = nullptr;
    }
    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}