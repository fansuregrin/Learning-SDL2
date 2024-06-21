#include <cstdio>

extern "C" {
#include <SDL2/SDL.h>
}

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window *gWindow = nullptr;
SDL_Surface *gScreenSurface = nullptr;
SDL_Surface *gHelloWorld = nullptr;

// 启动 SDL 并创建窗口
bool init();
// 加载媒体文件
bool loadMedia();
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
        }

        SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
        SDL_UpdateWindowSurface(gWindow);
    }

    close();
    return 0;
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL. SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Demo3", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        fprintf(stderr, "Failed to create window. SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

bool loadMedia() {
    const char *filepath = "resources/helloworld.bmp";
    gHelloWorld = SDL_LoadBMP(filepath);
    if (gHelloWorld == nullptr) {
        fprintf(stderr, "Cannot load %s! SDL_Error: %s\n", filepath, SDL_GetError());
        return false;
    }
    return true;
}

void close() {
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = nullptr;

    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }

    SDL_Quit();
}