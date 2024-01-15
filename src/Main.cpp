#define SDL_MAIN_HANDLED
#define rootpath "C:/Users/cew05/OneDrive/Documents/GitHub/Basic-GUI-in-CPP"

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

class Window
{
    private:
        SDL_Window* win = nullptr;
        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
        SDL_Renderer* renderer;
        SDL_Surface* surface = nullptr;
        int winwidth;
        int winheight;

        //Vars for creating a surface and Rect
        std::string imgpath = "/Resources/PlaceholderImages/GreenBackground500x500.png";
        SDL_Texture* texture;
        SDL_Rect selfRect {};

    public:
        explicit Window(const char* title = "New Window", int width = 500, int height = 500)
        {
            if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
                printf("error initializing SDL: %s\n", SDL_GetError());
            }

            win = SDL_CreateWindow(title, // creates a window
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   width, height, 0);

            renderer = SDL_CreateRenderer(win, -1, render_flags);
            winwidth = width;
            winheight = height;

            selfRect.w = winwidth;
            selfRect.h = winheight;
            selfRect.x = selfRect.y = 0;

            surface = IMG_Load((rootpath + imgpath).c_str());
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            SDL_QueryTexture(texture, nullptr, nullptr, &selfRect.w, &selfRect.h);
        }
        void Display()
        {
            SDL_RenderCopy(renderer, texture, nullptr, &selfRect);
            SDL_RenderPresent(renderer);
        }

        SDL_Window* WinObject() { return win; }
        SDL_Renderer* RendObject() { return renderer; }
        SDL_Surface* SurfObject() { return surface; }
        std::vector<int> GetWinSize() { return {winwidth, winheight}; }
};

class Player
{
    private:
        // Visuals Variables
        SDL_Rect selfRect {};
        SDL_Texture* texture;
        std::string imgPath = "/Resources/PlaceholderImages/BluePlayerSquare.png";

        //
        int speed = 20;
        std::vector<int> position {};


    public:
        Player(std::vector<int> initpos, SDL_Surface* surface, SDL_Renderer* renderer)
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
        void UpdatePos(std::vector<int> const &moveby, std::vector<int> const &bounds)
        {
            position[0] += ((moveby[0]*speed));
            position[1] += ((moveby[1]*speed));

            position[0] = (bounds[0]+(selfRect.w/2) > position[0]) ? position[0] = bounds[0] : position[0];
            position[0] = (bounds[1]-(selfRect.w/2) < position[0]) ? position[0] = bounds[1]-(selfRect.w) : position[0];
            position[1] = (bounds[2]+(selfRect.h/2) > position[1]) ? position[1] = bounds[2] : position[1];
            position[1] = (bounds[3]-(selfRect.h/2) < position[1]) ? position[1] = bounds[3]-(selfRect.h) : position[1];
        }
        void Display(SDL_Renderer* renderer)
        {
            selfRect.x = position[0];
            selfRect.y = position[1];
            SDL_RenderCopy(renderer, texture, nullptr, &selfRect);
            SDL_RenderPresent(renderer);
        }
        [[maybe_unused]] std::vector<int> GetPos() { return {selfRect.x, selfRect.y}; }
        [[maybe_unused]] void SetRectDimensions() { selfRect.w = 50; selfRect.h = 50; }
};

int main()
{
    Window win("Game", 500, 500);
    Player player({win.GetWinSize()[0]/2, win.GetWinSize()[1]/2},
                  win.SurfObject(), win.RendObject());

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
        SDL_RenderClear(win.RendObject());
        win.Display();
        player.UpdatePos(dir, {0, 500, 0, 500});
        player.Display(win.RendObject());
        SDL_Delay(1000/60);
    }




    return 0;
}