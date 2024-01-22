#include "Core.h"
#include "ItemObjects.h"

ItemBasic::ItemBasic(int w, int h, int x, int y, SDL_Color col)
{
    this->x = x;
    this->y = y;
    selfrect.w = w;
    selfrect.h = h;
    itemcol = col;
}

void ItemBasic::Display()
{
    selfrect.x = x - selfrect.w/2 - win.GetBufferDimensions()[0];
    selfrect.y = y - selfrect.h/2 - win.GetBufferDimensions()[1];

    SDL_SetRenderDrawColor(renderer, itemcol.r, itemcol.g, itemcol.b, itemcol.a);
    SDL_RenderDrawRect(renderer, &selfrect);
    SDL_RenderFillRect(renderer, &selfrect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void ItemBasic::CheckSnake(Snake &snake)
{
    std::vector<int> snakepos = snake.GetSegments()[0].GetPosition();
    if (snakepos[0] == x && snakepos[1] == y)
    {
        snake.AddSegment();
        Move(snake);
    }
}

void ItemBasic::Move(Snake &snake)
{
    std::vector<std::vector<int>> usedpositions {};
    for (SnakeBody segment : snake.GetSegments())
    {
        usedpositions.push_back({segment.GetPosition()[0], segment.GetPosition()[1]});
    }
    bool valid = true;
    int newx, newy;
    while (true)
    {
        newx = (std::rand() % win.GetGridDimensions()[1] + 1) * win.GetSquareSize()[0];
        newy = (std::rand() % win.GetGridDimensions()[0] + 1) * win.GetSquareSize()[1];
        for (std::vector<int> pos : usedpositions)
        {
            if (pos[0] == newx && pos[1] == newy) valid = false;
        }
        if (valid) break;
    }
    x = newx;
    y = newy;
}