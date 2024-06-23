#ifndef DMEO10_TEXTURE_H
#define DEMO10_TEXTURE_H

#include <string>
extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
}

namespace demo16 {

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(SDL_Renderer *renderer, const std::string &path);
    bool loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font,
        const std::string &text, SDL_Color color);
    void free();
    void render(SDL_Renderer *render, int x, int y, SDL_Rect *clip = nullptr,
        double angle = 0.0, SDL_Point *center = nullptr,
        SDL_RendererFlip flip = SDL_FLIP_NONE);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlend(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    int getWidth();
    int getHeight();
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

}

#endif // end of DEMO10_TEXTURE_H