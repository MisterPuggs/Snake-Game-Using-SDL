#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"

class Player
{
    private:
        SDL_Rect selfRect {};
        const char* imgPath = "Images/BluePlayerSquare.png";
        int speed = 50;
        SDL_Texture* texture;

    public:
        Player(int initx, int inity, SDL_Surface* &surface, SDL_Renderer* &renderer)
        {
            selfRect.x = initx;
            selfRect.y = inity;
            selfRect.w = 50;
            selfRect.h = 50;

            // Create Texture
            surface = IMG_Load(imgPath);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            SDL_QueryTexture(texture, nullptr, nullptr, &selfRect.w, &selfRect.h);
        }
        void UpdatePos(std::vector<int> const &moveby)
        {
            selfRect.x = moveby[0]*speed + selfRect.w/2;
            selfRect.y = moveby[1]*speed + selfRect.h/2;
        }
        void Display(SDL_Renderer* &renderer)
        {
            SDL_RenderCopy(renderer, texture, nullptr, &selfRect);
            SDL_RenderPresent(renderer);
        }
        std::vector<int> GetPos() { return {selfRect.x, selfRect.y}; }
        void SetRectDimensions() { selfRect.w = 50; selfRect.h = 50; }
        SDL_Texture* GetTexture() { return texture;}
};

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       500, 500, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    //Global Renderers and Surface
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    SDL_Surface* surface;

    Player player(SDL_GetWindowSurface(win)->w/2, SDL_GetWindowSurface(win)->h/2,
                  surface, rend);

    bool running = true;
    while(running)
    {
        SDL_Event event;

        // Manage Events
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_W:
                            player.UpdatePos({0,-1});
                        case SDL_SCANCODE_A:
                            player.UpdatePos({-1,0});
                        case SDL_SCANCODE_S:
                            player.UpdatePos({0,1});
                        case SDL_SCANCODE_D:
                            player.UpdatePos({1,0});
                        default:
                            break;
                    }
            }

            SDL_RenderClear(rend);
            player.Display(rend);
        }
    }




    return 0;
}