#include "texture.h"

namespace demo16 {

Texture::Texture(): mTexture(nullptr), mWidth(0), mHeight(0) {}

Texture::~Texture() { free(); }

bool Texture::loadFromFile(SDL_Renderer *renderer, const std::string &path) {
    free();

    // load an image into a surface
    SDL_Surface * loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to load %s. SDL_image Error: %s.", path.c_str(), IMG_GetError());
        return false;
    }

    // set the color key (transparent pixel)
    if (SDL_SetColorKey(loadedSurface, SDL_TRUE,
    SDL_MapRGB(loadedSurface->format, 0x00, 0xff, 0xff)) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to set color key. SDL Error: %s.", SDL_GetError());
        SDL_FreeSurface(loadedSurface);
        return false;
    }
    
    // create a texture
    mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (mTexture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create a texture from the surface. SDL Error: %s.",
            SDL_GetError());
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);

    return true;
}

bool Texture::loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font,
const std::string &text, SDL_Color color) {
    free();

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (textSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to render text surface. SDL_ttf Error: %s.", TTF_GetError());
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (mTexture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to create a texture from rendered text. SDL Error: %s.",
            SDL_GetError());
        SDL_FreeSurface(textSurface);
        return false;
    }

    mWidth = textSurface->w;
    mHeight = textSurface->h;
    SDL_FreeSurface(textSurface);
    return true;
}

void Texture::free() {
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = mHeight = 0;
    }
}

void Texture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip,
double angle, SDL_Point *center, SDL_RendererFlip flip) {
    SDL_Rect area = {x, y, mWidth, mHeight};
    if (clip) {
        area.h = clip->h;
        area.w = clip->w;
    }
    SDL_RenderCopyEx(renderer, mTexture, clip, &area, angle, center, flip);
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