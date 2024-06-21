#include <cstdio>
#include <string>

extern "C" {
#include <SDL2/SDL.h>
}

enum KeyPressSurface {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window * gWindow = nullptr;
SDL_Surface * gScreenSurface = nullptr;
SDL_Surface * gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface * gCurrSurface = nullptr;

// 启动 SDL 并创建窗口
bool init();
// 加载媒体文件
bool loadMedia();
SDL_Surface* loadSurface(const std::string &path);
// 释放媒体资源并关闭 SDL
void close();

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
    gCurrSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                fprintf(stdout, "Press %s down\n", SDL_GetKeyName(e.key.keysym.sym));
                switch (e.key.keysym.sym) {
                    case SDLK_DOWN:
                    gCurrSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                    break;

                    case SDLK_UP:
                    gCurrSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                    break;

                    case SDLK_LEFT:
                    gCurrSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                    break;

                    case SDLK_RIGHT:
                    gCurrSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                    break;

                    default:
                    gCurrSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }                
            }
        }
        SDL_BlitSurface(gCurrSurface, nullptr, gScreenSurface, nullptr);
        SDL_UpdateWindowSurface(gWindow);
    }

    close();
    return 0;
}

bool init() {
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
            "Failed to initialize SDL. SDL_Error: %s", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Demo4", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create window. SDL_Error: %s", SDL_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

bool loadMedia() {
    // load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("resources/default.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load default image.");
        return false;
    }
    // load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("resources/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load up image.");
        return false;
    }
    // load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("resources/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load down image.");
        return false;
    }
    // load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("resources/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load left image.");
        return false;
    }
    // load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("resources/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load right image.");
        return false;
    }

    return true;
}

SDL_Surface* loadSurface(const std::string &path) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot load image %s! SDL_Error: %s",
            path.c_str(), SDL_GetError());
    }
    return loadedSurface;
}

void close() {
    for (int i=0; i<KEY_PRESS_SURFACE_TOTAL; ++i) {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
    }

    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }

    SDL_Quit();
}