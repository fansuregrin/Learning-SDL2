#ifndef _BUTTON_H
#define _BUTTON_H

#include <SDL2/SDL.h>
#include "texture.h"

namespace demo17 {

class Button {
public:
    enum ButtonSprite {
        BUTTON_SPRITE_MOUSE_OUT = 0,
        BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
        BUTTON_SPRITE_MOUSE_DOWN = 2,
        BUTTON_SPRITE_MOUSE_UP = 3,
        BUTTON_SPRITE_MOUSE_TOTAL = 4
    };

    Button(Texture* texture, int width, int height);

    void setPosition(int x, int y);
    void handleEvent(SDL_Event *e);
    void render(SDL_Rect* clips) const;
private:
    Texture* mTexture;
    SDL_Point mPosition;  // top-left position
    ButtonSprite mCurrSprite;  // current button sprite
    int mWidth, mHeight;
};

}

#endif // end of _BUTTON_H