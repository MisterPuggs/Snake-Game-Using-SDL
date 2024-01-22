#include "Core.h"
#include "SnakeElements.h"
#include "ItemObjects.h"

Window win("Game", 32*16.5, 32*16.5, 32, 32);
Snake player((8*win.GetSquareSize()[0]), (8*win.GetSquareSize()[1]), 5);
SDL_Color foodcol = {155, 0, 0, 255};
std::vector<ItemBasic> food {ItemBasic(20,20,
                                       (std::rand() % 16 + 1)*win.GetSquareSize()[0],
                                       (std::rand() % 16 + 1)*win.GetSquareSize()[1],
                                       foodcol)};

bool running_game = false, running_menu = true;

void GameKeyEvents()
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
}

void MenuLoop()
{
    while (running) {
        SDL_Event event;
        bool click = false;
        int mousex, mousey;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running=false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    click = true;
                    SDL_GetMouseState(&mousex, &mousey);
                    break;

                case SDL_MOUSEBUTTONUP:
                    click = false;
                    break;

                default:
                    break;
            }
        }

        win.CheckerDisplay(16, 16);

        SDL_Rect menubuttonrect {};
        std::string fontpath = "Resources/Fonts/CookieCrisp/CookieCrisp-L36ly.ttf";
        TTF_Font* textfont = TTF_OpenFont("Sans.ttf" , 24);
        SDL_Color white {255, 255, 255, 255};
        std::string labels[2] {"play", "Quit"};

        int bufferx = win.GetWinSize()[0] / 5;
        int buffery = win.GetWinSize()[1] / 5;
        menubuttonrect.w = win.GetWinSize()[0] - 2 * bufferx;
        menubuttonrect.h = buffery;
        for (int i = 0; i < 2; i++) {
            menubuttonrect.y = buffery + (i * 2 * buffery);
            menubuttonrect.x = bufferx;

            SDL_SetRenderDrawColor(renderer, 70, 210, 20, 255);
            SDL_RenderFillRect(renderer, &menubuttonrect);
            SDL_SetRenderDrawColor(renderer, 50, 0, 50, 255);
            SDL_RenderDrawRect(renderer, &menubuttonrect);

            surface = TTF_RenderText_Solid(textfont, labels[i].c_str(), white);
            SDL_Texture* label = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_RenderCopy(renderer, label, nullptr, &menubuttonrect);
            SDL_FreeSurface(surface);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        if (click && mousex >= bufferx && mousex <= bufferx+menubuttonrect.w)
        {
            if (mousey >= buffery && mousey <= buffery + menubuttonrect.h)
            {
                running_game = true;
                running_menu = false;
                break;
            }
            if (mousey >= menubuttonrect.y && mousey <= menubuttonrect.y + menubuttonrect.h)
            {
                running=false;
                running_game = false;
                running_menu = false;
            }
        }

        Window::Render();
        SDL_Delay(1000/60);
    }
    running_menu = false;
}

void GameLoop()
{
    while (running)
    {
        GameKeyEvents();

        win.CheckerDisplay(16, 16);

        player.Move(win.GetSquareSize()[0], win.GetSquareSize()[1]);
        player.Display();

        for (ItemBasic &item : food)
        {
            item.CheckSnake(player);
            item.Display();
        }

        Window::Render();
        SDL_Delay(1000/60);

        if (player.GetDead()) break;
    }
    running_game = false;
    running_menu = true;
}

int main()
{

    while(running)
    {
        if (running_menu) MenuLoop();
        if (running_game) GameLoop();
    }
    return 0;
}