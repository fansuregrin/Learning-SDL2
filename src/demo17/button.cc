#include "button.h"

namespace demo17 {
Button::Button(Texture* texture, int width, int height) {
    mTexture = texture;
    mPosition.x = 0;
    mPosition.y = 0;
    mWidth = width;
    mHeight = height;
    mCurrSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
}

void Button::handleEvent(SDL_Event *e) {
    if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || 
    e->type == SDL_MOUSEMOTION) {
        // get current mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);
        // check if mouse is inside the button
        bool inside = true;
        if (x < mPosition.x) {
            inside = false;
        } else if (x > mPosition.x + mWidth) {
            inside = false;
        } else if (y < mPosition.y) {
            inside = false;
        } else if (y > mPosition.y + mHeight) {
            inside = false;
        }

        if (inside) {
            switch (e->type) {
                case SDL_MOUSEBUTTONDOWN:
                mCurrSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

                case SDL_MOUSEBUTTONUP:
                mCurrSprite = BUTTON_SPRITE_MOUSE_UP;
                break;

                case SDL_MOUSEMOTION:
                mCurrSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            }
        } else {
            mCurrSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
    }
}

void Button::render(SDL_Rect* clips) const {
    mTexture->render(mPosition.x, mPosition.y, &clips[mCurrSprite]);
}

}