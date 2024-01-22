#include "Core.h"
#include "BasicPlayer.h"



Player::Player(std::vector<int> initpos)
{
    position = {initpos[0], initpos[1]};
    selfRect.w = 50;
    selfRect.h = 50;

    // Create Texture
    surface = IMG_Load((rootpath+imgPath).c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &selfRect.w, &selfRect.h);
}
void Player::UpdatePos(std::vector<int> const &moveby, std::vector<int> const &bounds)
{
    position[0] += ((moveby[0]*speed));
    position[1] += ((moveby[1]*speed));

    position[0] = (bounds[0]+(selfRect.w/2) > position[0]) ? position[0] = bounds[0] : position[0];
    position[0] = (bounds[1]-(selfRect.w/2) < position[0]) ? position[0] = bounds[1]-(selfRect.w) : position[0];
    position[1] = (bounds[2]+(selfRect.h/2) > position[1]) ? position[1] = bounds[2] : position[1];
    position[1] = (bounds[3]-(selfRect.h/2) < position[1]) ? position[1] = bounds[3]-(selfRect.h) : position[1];
}
void Player::Display()
{
    selfRect.x = position[0];
    selfRect.y = position[1];
    SDL_RenderCopy(renderer, texture, nullptr, &selfRect);
    SDL_RenderPresent(renderer);
}