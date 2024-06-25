#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
}

namespace demo18 {

class Texture {
public:
    Texture();
    Texture(SDL_Renderer* renderer);
    ~Texture();

    void setRenderer(SDL_Renderer *renderer);

    bool loadFromFile(const std::string &path);
    
    bool loadFromRenderedText(TTF_Font *font,
        const std::string &text, SDL_Color color);
    
    void free();
    void render(int x, int y, SDL_Rect *clip = nullptr,
        double angle = 0.0, SDL_Point *center = nullptr,
        SDL_RendererFlip flip = SDL_FLIP_NONE);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlend(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    int getWidth();
    int getHeight();
private:
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

}

#endif // end of _TEXTURE_H