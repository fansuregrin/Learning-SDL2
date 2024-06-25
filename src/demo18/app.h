#ifndef _APP_H
#define _APP_H

#include <vector>
#include <string>
extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
}
#include "texture.h"

namespace demo18 {
class App {
public:
    App();
    ~App();

    void start();
protected:
    enum KeyPressTexture {
        KEY_PRESS_TEXTURE_DEFAULT,
        KEY_PRESS_TEXTURE_UP,
        KEY_PRESS_TEXTURE_DOWN,
        KEY_PRESS_TEXTURE_LEFT,
        KEY_PRESS_TEXTURE_RIGHT,
        KEY_PRESS_TEXTURE_TOTAL
    };
private:

    bool loadMedia();
    bool init();
    void close();

    std::string mTitle;
    bool closed;
    int mScreenWidth;
    int mScreenHeight;
    SDL_Window * mWindow;
    SDL_Renderer * mRenderer;
    TTF_Font * mFont;
    Texture mTextures[KEY_PRESS_TEXTURE_TOTAL];
    Texture* mCurrTexture;
};

}

#endif // end of _APP_H