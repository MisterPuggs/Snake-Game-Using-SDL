#define SDL_MAIN_HANDLED
#define rootpath "C:/Users/cew05/OneDrive/Documents/GitHub/Basic-GUI-in-CPP"

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_timer.h"



class Player
{
    private:
        SDL_Rect selfRect {};
        std::string imgPath = "/Resources/PlaceholderImages/BluePlayerSquare.png";
        int speed = 20;
        SDL_Texture* texture;

    public:
        Player(int initx, int inity, SDL_Surface* &surface, SDL_Renderer* &renderer)
        {
            selfRect.x = initx;
            selfRect.y = inity;
            selfRect.w /= 6;
            selfRect.h /= 6;

            // Create Texture
            surface = IMG_Load((rootpath+imgPath).c_str());
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            SDL_QueryTexture(texture, nullptr, nullptr, &selfRect.w, &selfRect.h);
        }
        void UpdatePos(std::vector<int> const &moveby, std::vector<int> const &bounds)
        {
            selfRect.x += ((moveby[0]*speed));
            selfRect.y += ((moveby[1]*speed));
            selfRect.x = (bounds[0] > selfRect.x) ? selfRect.x = bounds[0] : selfRect.x;
            selfRect.x = (bounds[1] < selfRect.x) ? selfRect.x = bounds[1] : selfRect.x;
            selfRect.y = (bounds[2] > selfRect.y) ? selfRect.y = bounds[2] : selfRect.y;
            selfRect.y = (bounds[3] < selfRect.y) ? selfRect.y = bounds[3] : selfRect.y;
        }
        void Display(SDL_Renderer* &renderer)
        {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, nullptr, &selfRect);
            SDL_RenderPresent(renderer);
        }
        std::vector<int> GetPos() { return {selfRect.x, selfRect.y}; }
        void SetRectDimensions() { selfRect.w = 50; selfRect.h = 50; }
};

int main()
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
        std::vector<int> dir {0, 0};

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
                            dir = {dir[0], dir[1]-1};
                            break;
                        case SDL_SCANCODE_A:
                            dir = {dir[0]-1, dir[1]};
                            break;
                        case SDL_SCANCODE_S:
                            dir = {dir[0], dir[1]+1};
                            break;
                        case SDL_SCANCODE_D:
                            dir = {dir[0]+1, dir[1]};
                            break;
                        default:
                            break;

                    }
            }

        }
        player.UpdatePos(dir, {0, 500, 0, 500});
        player.Display(rend);
        std::cout << player.GetPos()[0] << "x " << player.GetPos()[1] << "y\n";
        SDL_Delay(1000/60);
    }




    return 0;
}