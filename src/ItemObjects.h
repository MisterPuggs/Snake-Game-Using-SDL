#pragma once
#include "SnakeElements.h"

class ItemBasic {
    private:
        int x, y;
        bool edible = true;
        SDL_Rect selfrect {};
        SDL_Color itemcol;

    public:
        ItemBasic(int w, int h, int x, int y, SDL_Color col);
        void Display();
        void CheckSnake(Snake &snake);
        void Move(Snake &snake);
};
