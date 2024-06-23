#include <string>
extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
}

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window * gWindow = nullptr;
SDL_Surface * gScreenSurface = nullptr;
SDL_Surface * gStretchedSurface = nullptr;

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
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            SDL_Rect stretchRect;
            stretchRect.x = 0;
            stretchRect.y = 0;
            stretchRect.h = SCREEN_HEIGHT;
            stretchRect.w = SCREEN_WIDTH;
            SDL_BlitScaled(gStretchedSurface, nullptr, gScreenSurface, &stretchRect);
            SDL_UpdateWindowSurface(gWindow); 
        }
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

    gWindow = SDL_CreateWindow("SDL Demo6", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create window. SDL_Error: %s.", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to initialized SDL_image. SDL_image Error: %s.", IMG_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

bool loadMedia() {
    gStretchedSurface = loadSurface("resources/demo6.png");
    if (gStretchedSurface == nullptr) {
        return false;
    }

    return true;
}

SDL_Surface* loadSurface(const std::string &path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Cannot load image %s! SDL_image Error: %s.",
            path.c_str(), IMG_GetError());
        return nullptr;
    }
    
    // Convert surface to screen format
    SDL_Surface *optimizedSurface = SDL_ConvertSurface(loadedSurface,
        gScreenSurface->format, 0);
    if (optimizedSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to optimize image %s! SDL_Error: %s.", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_FreeSurface(loadedSurface);
    return optimizedSurface;
}

void close() {
    SDL_FreeSurface(gStretchedSurface);
    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }

    IMG_Quit();
    SDL_Quit();
}