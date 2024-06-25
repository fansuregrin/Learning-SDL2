#include "app.h"

namespace demo18 {

App::App(): closed(false), mScreenWidth(640), mScreenHeight(480),
mWindow(nullptr), mRenderer(nullptr), mFont(nullptr), mCurrTexture(nullptr) {
    if (!init()) { close(); }

    if (!loadMedia()) { close(); }
}

App::~App() {
    close();
}

void App::close() {
    if (mFont) {
        TTF_CloseFont(mFont);
        mFont = nullptr;
    }
    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
    if (mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    closed = true;
}

bool App::init() {
    #if defined(DEBUG)
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    #endif

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
            "Failed to initialize SDL. SDL Error: %s.", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(mTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, mScreenWidth, mScreenHeight,
        SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create window. SDL Error: %s.", SDL_GetError());
        return false;
    }

    // create a vsynced renderer for the window
    mRenderer = SDL_CreateRenderer(mWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create renderer. SDL Error: %s.", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
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

    for (int i=0; i<KEY_PRESS_TEXTURE_TOTAL; ++i) {
        mTextures[i].setRenderer(mRenderer);
    }
    mCurrTexture = &mTextures[KEY_PRESS_TEXTURE_DEFAULT];

    return true;
}

bool App::loadMedia() {
    if (
    mTextures[KEY_PRESS_TEXTURE_DEFAULT].loadFromFile("resources/default.png") &&
    mTextures[KEY_PRESS_TEXTURE_DOWN].loadFromFile("resources/down.png") &&
    mTextures[KEY_PRESS_TEXTURE_UP].loadFromFile("resources/up.png") &&
    mTextures[KEY_PRESS_TEXTURE_LEFT].loadFromFile("resources/left.png") &&
    mTextures[KEY_PRESS_TEXTURE_RIGHT].loadFromFile("resources/right.png")
    ) {
        return true;
    }

    return false;
}

void App::start() {
    if (closed) return;
    SDL_Event e;
    while (closed == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                closed = true;
            }
        }

        const Uint8* currKeyStates = SDL_GetKeyboardState(nullptr);
        if (currKeyStates[SDL_SCANCODE_DOWN]) {
            mCurrTexture = &mTextures[KEY_PRESS_TEXTURE_DOWN];
        } else if (currKeyStates[SDL_SCANCODE_UP]) {
            mCurrTexture = &mTextures[KEY_PRESS_TEXTURE_UP];
        } else if (currKeyStates[SDL_SCANCODE_LEFT]) {
            mCurrTexture = &mTextures[KEY_PRESS_TEXTURE_LEFT];
        } else if (currKeyStates[SDL_SCANCODE_RIGHT]) {
            mCurrTexture = &mTextures[KEY_PRESS_TEXTURE_RIGHT];
        } else {
            mCurrTexture = &mTextures[KEY_PRESS_TEXTURE_DEFAULT];
        }

        // Clear renderer
        SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(mRenderer);

        mCurrTexture->render(0, 0);

        // Update screen
        SDL_RenderPresent(mRenderer);
    }
}

}