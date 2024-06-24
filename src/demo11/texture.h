#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
}

extern SDL_Renderer* gRenderer;

namespace demo11 {
class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(SDL_Renderer *renderer, const std::string &path);
    void free();
    void render(SDL_Renderer *render, int x, int y, SDL_Rect *clip = nullptr);
    int getWidth();
    int getHeight();
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};
}

#endif // end of _TEXTURE_H