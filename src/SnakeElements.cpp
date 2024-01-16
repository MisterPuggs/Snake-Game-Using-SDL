#include "Core.h"
#include "SnakeElements.h"


SnakeBody::SnakeBody(int initx, int inity, int w, int h)
{
    x = prevx= initx;
    y = prevy = inity;
    selfRect.w = w;
    selfRect.h = h;

    // Create Texture
    surface = IMG_Load((rootpath+imgPath).c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &selfRect.w, &selfRect.h);
}

void SnakeBody::MoveTo(int destx, int desty)
{
    if (!stiff)
    {
        prevx = x;
        prevy = y;
        x = destx;
        y = desty;
    }
    stiff = false;
}

void SnakeBody::Display()
{
    selfRect.x = x - selfRect.w/2;
    selfRect.y = y - selfRect.h/2;
    SDL_RenderCopy(renderer, texture, nullptr, &selfRect);
}

Snake::Snake(int x, int y, int sqlength)
{
    rectw = sqlength;
    recth = sqlength;
    bodySegments.emplace_back(x, y, rectw, recth);
}

void Snake::AddSegment()
{
    std::vector<int> prevposition {bodySegments.back().GetPosition()};
    bodySegments.emplace_back(prevposition[0], prevposition[1], rectw, recth);
}

void Snake::Move()
{
    std::vector<int> pos = bodySegments[0].GetPosition();
    bodySegments[0].MoveTo(pos[0] + direction[0]*rectw, pos[1] + direction[1]*recth);
    for (int s = 1; s < bodySegments.size(); s++)
    {
        bodySegments[s].MoveTo(bodySegments[s-1].GetPrevPosition()[0],
                               bodySegments[s-1].GetPrevPosition()[1]);
    }

}

void Snake::SetDirection(int dirx, int diry)
{
    direction = {dirx, diry};
}

void Snake::Display()
{
    for (SnakeBody segment : bodySegments)
    {
        segment.Display();
    }

}