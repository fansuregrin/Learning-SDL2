#include <string>
extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
}

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window * gWindow = nullptr;
SDL_Renderer * gRenderer = nullptr;
SDL_Texture * gTexture = nullptr;

// 启动 SDL 并创建窗口
bool init();
// 加载媒体文件
bool loadMedia();
SDL_Texture* loadTexture(const std::string &path);
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

        // Clear renderer
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        // Render a red filled rectangle
        SDL_Rect fillRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4,
            SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xff);
        SDL_RenderFillRect(gRenderer, &fillRect);
        
        // Render a green outlined rectangle
        SDL_Rect outlineRect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6,
            SCREEN_WIDTH*2/3, SCREEN_HEIGHT*2/3};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0xff);
        SDL_RenderDrawRect(gRenderer, &outlineRect);

        // Render a horizontal line
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xff, 0xff);
        SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

        // Render a vertical line with black dots
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
        for (int i=0; i<SCREEN_HEIGHT; i+=4) {
            SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH/2, i);
        }

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

    gWindow = SDL_CreateWindow("SDL Demo8", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    return true;
}

SDL_Texture* loadTexture(const std::string &path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot load image %s! SDL_Error: %s.",
            path.c_str(), SDL_GetError());
        return nullptr;
    }
    
    // Create texture from surface pixels
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create texture from %s! SDL_Error: %s.", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

void close() {
    if (gTexture) {
        SDL_DestroyTexture(gTexture);
        gTexture = nullptr;
    }
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