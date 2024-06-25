#ifndef _APP_H
#define _APP_H

#include <vector>
#include <string>
#include "texture.h"
#include "button.h"

namespace demo17 {
class App {
public:
    App();
    ~App();

    void start();
private:
    bool loadMedia();
    bool init();
    void close();

    std::string mTitle;
    bool closed;
    int mScreenWidth;
    int mScreenHeight;
    int mButtonNum;
    SDL_Window * mWindow;
    SDL_Renderer * mRenderer;
    TTF_Font * mFont;
    Texture mButtonTexture;
    std::vector<Button> mButtons;
    SDL_Rect mButtonClips[Button::BUTTON_SPRITE_MOUSE_TOTAL];
};

}

#endif // end of _APP_H