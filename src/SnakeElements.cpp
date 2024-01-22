#include "Core.h"
#include "SnakeElements.h"


SnakeBody::SnakeBody(int initx, int inity, int stall)
{
    x = prevx= initx;
    y = prevy = inity;
    this->stall = stall;

    // Create Texture
    surface = IMG_Load((rootpath+imgPath).c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &selfRect.w, &selfRect.h);
}

void SnakeBody::MoveTo(int destx, int desty)
{
    if (stall <= 0)
    {
        prevx = x;
        prevy = y;
        x = destx;
        y = desty;
    }
    stall -= 1;
}

void SnakeBody::Display(Window &win)
{
    selfRect.w = win.GetSquareSize()[0];
    selfRect.h = win.GetSquareSize()[1];
    selfRect.x = x - win.GetSquareSize()[0]/2 - win.GetBufferDimensions()[0];
    selfRect.y = y - win.GetSquareSize()[1]/2 - win.GetBufferDimensions()[1];
    SDL_RenderCopy(renderer, texture, nullptr, &selfRect);
}

Snake::Snake(int x, int y, int segments) {
    for (int s = 0; s < segments; s++) bodySegments.emplace_back(x, y, s+1);
}

void Snake::AddSegment()
{
    std::vector<int> prevposition {bodySegments.back().GetPosition()};
    bodySegments.emplace_back(prevposition[0], prevposition[1], 1);
}

void Snake::Move(int movx, int movy)
{
    movedelayticks -= (SDL_GetTicks64() - prevmovecalltick);
    prevmovecalltick = SDL_GetTicks64();
    if (movedelayticks < maxdelay) return;

    std::vector<int> pos = bodySegments[0].GetPosition();
    currdirection = nextdirection;
    int destx = pos[0] + currdirection[0]*movx;
    int desty = pos[1] + currdirection[1]*movy;

    if ((destx < win.GetBufferDimensions()[0]) || destx > win.GetWinSize()[0] + win.GetBufferDimensions()[0])
    {
        dead = true;
        return;
    }
    if ((desty < win.GetBufferDimensions()[1]) || desty > win.GetWinSize()[1] + win.GetBufferDimensions()[1])
    {
        dead = true;
        return;
    }

    bodySegments[0].MoveTo(destx, desty);

    for (int s = 1; s < bodySegments.size(); s++)
    {
        bodySegments[s].MoveTo(bodySegments[s-1].GetPrevPosition()[0],
                               bodySegments[s-1].GetPrevPosition()[1]);
    }

    movedelayticks = maxdelay;
}

void Snake::SetDirection(int dirx, int diry)
{
    if ((dirx == currdirection[0]*-1) || (diry == currdirection[1]*-1)) return;
    else nextdirection = {dirx, diry};
}

void Snake::Display()
{
    for (SnakeBody segment : bodySegments) segment.Display(win);
}
