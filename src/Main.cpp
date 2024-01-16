#include "Core.h"
#include "SnakeElements.h"

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
        Player(std::vector<int> initpos)
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
        void Display()
        {
            selfRect.x = position[0];
            selfRect.y = position[1];
            SDL_RenderCopy(renderer, texture, nullptr, &selfRect);
            SDL_RenderPresent(renderer);
        }
        [[maybe_unused]] std::vector<int> GetPos() { return {selfRect.x, selfRect.y}; }
        [[maybe_unused]] void SetRectDimensions() { selfRect.w = 50; selfRect.h = 50; }
};

int squarelength = 32;

int main()
{
    Window win("Game", 16*32, 16*32);
    Snake player((8*32)-16, (8*32)-16, 30);

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
                            player.SetDirection(0, -1);
                            break;
                        case SDL_SCANCODE_A:
                            player.SetDirection(-1, 0);
                            break;
                        case SDL_SCANCODE_S:
                            player.SetDirection(0, 1);
                            break;
                        case SDL_SCANCODE_D:
                            player.SetDirection(1, 0);
                            break;
                        case SDL_SCANCODE_0:
                            player.AddSegment();
                            break;
                        default:
                            break;

                    }
            }

        }

        SDL_RenderClear(renderer);

        win.CheckerDisplay(32, 32, 16, 16);
        player.Move();
        player.Display();

        SDL_RenderPresent(renderer);
        SDL_Delay(500);

    }




    return 0;
}