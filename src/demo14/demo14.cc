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
SDL_Rect gSpriteClips[WALKING_FRAMES];
demo14::Texture gSpriteSheetTexture;
demo14::Texture gBackgroundTexture;

int main(int argc, char * argv[]) {
    if (!init("SDL Demo14")) {
        close();
        return 1;
    }

    if (!loadMedia()) {
        close();
        return 1;
    }

    SDL_Event e;
    // current frame
    int frame = 0;
    // how many frames to refresh the status and position of the astronaut
    int refreshRate = 5;
    int pos = 0, move = 10;
    bool quit = false, pause = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Press down key %s.",
                    SDL_GetKeyName(e.key.keysym.sym));
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE:
                    pause = !pause;
                    break;
                }
            }
        }

        // Clear renderer
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        // Render background
        gBackgroundTexture.render(gRenderer, 0, 0);
        // Render the astronaut
        SDL_Rect * currClip = &gSpriteClips[frame/refreshRate];
        gSpriteSheetTexture.render(gRenderer, pos, 305, currClip);

        // Update screen
        SDL_RenderPresent(gRenderer);

        if (pause) continue;
        // go to next frame
        ++frame;
        if (frame / refreshRate >= WALKING_FRAMES) {
            frame = 0;
        }
        if (frame % refreshRate == 0) {
            pos = (pos + move > SCREEN_WIDTH) ? 0 : pos + move;
        }
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

    // create a vsynced renderer for the window
    gRenderer = SDL_CreateRenderer(gWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    if (!gBackgroundTexture.loadFromFile(gRenderer, "resources/castle_backround.png")) {
        return false;
    }
    if (!gSpriteSheetTexture.loadFromFile(gRenderer, "resources/astronaut-walk-cycle.png")) {
        return false;
    }

    gSpriteClips[0] = {0,  0, 38, 62};
    gSpriteClips[1] = {38, 0, 38, 62};
    gSpriteClips[2] = {76, 0, 38, 62};
    gSpriteClips[3] = {115, 0, 38, 62};

    return true;
}

void close() {
    gSpriteSheetTexture.free();
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