#include "app.h"

namespace demo17 {

App::App(): closed(false), mScreenWidth(640), mScreenHeight(480), mButtonNum(4),
mWindow(nullptr), mRenderer(nullptr), mFont(nullptr) {
    if (!init()) { close(); }

    if (!loadMedia()) { close(); }

    for (int i=0; i<mButtonNum; ++i) {
        mButtons.emplace_back(&mButtonTexture, 80, 40);
    }
    mButtons[0].setPosition(0, 0);
    mButtons[1].setPosition(mScreenWidth-80, 0);
    mButtons[2].setPosition(0, mScreenHeight-40);
    mButtons[3].setPosition(mScreenWidth-80, mScreenHeight-40);
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

    mButtonTexture.setRenderer(mRenderer);

    return true;
}

bool App::loadMedia() {
    if (!mButtonTexture.loadFromFile("resources/button.png")) {
        return false;
    }

    mButtonClips[Button::BUTTON_SPRITE_MOUSE_DOWN] = {0, 0, 80, 40};
    mButtonClips[Button::BUTTON_SPRITE_MOUSE_UP] = {80, 0, 80, 40};
    mButtonClips[Button::BUTTON_SPRITE_MOUSE_OVER_MOTION] = {0, 40, 80, 40};
    mButtonClips[Button::BUTTON_SPRITE_MOUSE_OUT] = {80, 40, 80, 40};

    return true;
}

void App::start() {
    if (closed) return;
    SDL_Event e;
    while (closed == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                closed = true;
            }

            for (auto &button : mButtons) {
                button.handleEvent(&e);
            }
        }

        // Clear renderer
        SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(mRenderer);

        for (const auto &button : mButtons) {
            button.render(mButtonClips);
        }

        // Update screen
        SDL_RenderPresent(mRenderer);
    }
}

}