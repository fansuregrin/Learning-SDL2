#include "texture.h"

namespace demo14 {

Texture::Texture(): mTexture(nullptr), mWidth(0), mHeight(0) {}

Texture::~Texture() { free(); }

bool Texture::loadFromFile(SDL_Renderer *renderer, const std::string &path) {
    // load an image into a surface
    SDL_Surface * loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to load %s. SDL_Error: %s.", path.c_str(), SDL_GetError());
        return false;
    }

    // set the color key (transparent pixel)
    if (SDL_SetColorKey(loadedSurface, SDL_TRUE,
    SDL_MapRGB(loadedSurface->format, 0x00, 0xff, 0xff)) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to set color key. SDL_Error: %s.", SDL_GetError());
        SDL_FreeSurface(loadedSurface);
        return false;
    }
    
    // create a texture
    mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (mTexture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create a texture from the surface. SDL_Error: %s.",
            SDL_GetError());
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);

    return true;
}

void Texture::free() {
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = mHeight = 0;
    }
}

void Texture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip) {
    SDL_Rect area = {x, y, mWidth, mHeight};
    if (clip) {
        area.h = clip->h;
        area.w = clip->w;
    }
    SDL_RenderCopy(renderer, mTexture, clip, &area);
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    // newRed = oldRed * (red / 255)
    // newGreen = oldGreen * (green / 255)
    // newBlue = oldBlue * (blue / 255)
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlend(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

int Texture::getWidth() { return mWidth; }

int Texture::getHeight() { return mHeight; }

}